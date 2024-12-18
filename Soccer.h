// Soccer.cpp

#include "Soccer.h"

using namespace std;

void Soccer::run()
{
    entry_list_.read_file(cs_file_name);
    bool done = false;
    while (!done) {
        if (!search_) { display_entry_and_menu(search_fail_, category_); }
        else { display_entry_and_search(); }
        cout << "choice: ";
        char command;
        cin >> command;
        cin.get(); // new line char
        if (!search_)execute(command, done);
        else execute_search(command, done);
        cout << endl;
    }
}

void Soccer::display_entry_and_search() const {
    string long_separator(50, '-');
    string short_separator(8, '-');

    system(clear_command);

    entry_list_.display_current_entry();

    cout << long_separator << endl
        << "   next back edit\n"
        << "   print main quit\n"
        << short_separator << endl;
}


void Soccer::execute_search(char command, bool& done)
{
    switch (command) {
    case 'n': {
        entry_list_.next();

        break;
    }
    case 'b': {
        entry_list_.previous();
        break;
    }
    case 'e': {
        PlayerEntry input = input_entry();
        entry_list_.edit_entry(input);

        cout << endl;
        break;
    }
    case 'p': {
        string file;
        cout << "Filename: ";
        getline(cin, file);
        entry_list_.print_search(file);

        break;
    }
    case 'm': {
        search_ = false;
        break;
    }
    case 'q': {
        if (entry_list_.print()) { done = true; }
        break;

    }

    }
}

void Soccer::display_entry_and_menu(bool& fail, bool& cat) {
    string long_separator(50, '-');
    string short_separator(8, '-');

    system(clear_command);

    //    entry_list_.display_current_entry();
    if (fail) {
        cout << "Search Failed\n";
        fail = false;
    }

    if (category_) {
        print_categories();
        category_ = false;
    }

    cout << long_separator << endl
        << "   new_season add user_search\n"
        << "   print display_statistics quit\n"
        << short_separator << endl;
}

void Soccer::execute(char command, bool& done)
{
    switch (command) {
    case 'n': {
        int year;
        char answer;
        cout << "New year: ";
        cin >> year;
        cout << endl << "Confirm you want to start a new season(Y/N)?\n";
        cin >> answer;
        if (answer == 'Y' || answer == 'y') {
            entry_list_.new_season(year);
        }
        break;
    }
    case 'a': {
        PlayerEntry entry = input_entry();
        entry_list_.add_entry(entry);

        break;
    }
    case 'u': {
        string keyword;
        PlayerEntry entry = input_entry(keyword);
        if (!entry_list_.search(entry, keyword)) {
            search_fail_ = true;
            search_ = false;
        }
        else {
            search_ = true;
            search_fail_ = false;
        }


        break;
    }
    case 'p': {
        string file;
        cout << "Filename: ";
        cin >> file;
        entry_list_.print_main(file);
        break;
    }
    case 'd': {
        //categories

        category_ = true;
        // need to do these for each category
        break;
        break;

    }
    case 'q': {
        if (entry_list_.print()) { done = true; }
        break;
    }

    }

}

const PlayerEntry Soccer::input_entry() {

    string status, lname, fname;
    string b;
    int birth;

    cout << "Last name: ";
    getline(cin, lname);

    cout << "First name: ";
    getline(cin, fname);

    cout << "Birth year: ";
    getline(cin, b);
    if (b.empty()) { birth = -1; }
    else birth = stoi(b);
    int age = entry_list_.season_ - birth;

    cout << "Status(paid/not paid): ";
    getline(cin, status);


    return PlayerEntry(lname, fname, age, status, birth);
}

const PlayerEntry Soccer::input_entry(std::string& keyword) {

    string status, lname, fname;
    string b;
    int birth;

    cout << "Last name: ";
    getline(cin, lname);

    cout << "First name: ";
    getline(cin, fname);

    cout << "Birth year: ";
    getline(cin, b);
    if (b.empty()) { birth = -1; }
    else birth = stoi(b);
    int age = entry_list_.season_ - birth;

    cout << "Status(paid/not paid): ";
    getline(cin, status);
    cout << "Keyword:";
    getline(cin, keyword);

    return PlayerEntry(lname, fname, age, status, birth);
}

void Soccer::print_categories() {
    entry_list_.category("U6");
    entry_list_.category("U8");
    entry_list_.category("U10");
    entry_list_.category("U12");
    entry_list_.category("U14");
    entry_list_.category("U17");
    cout << "All categories: " << entry_list_.fc << " players, " << entry_list_.fp << " paid, " << entry_list_.fu << " not paid\n";

    entry_list_.fc = 0;
    entry_list_.fp = 0;
    entry_list_.fu = 0;
}
