// SoccerRecord.cpp

#include "SoccerRecord.h"

void SoccerRecord::read_file(const std::string& file_name)
{
    std::ifstream in(file_name);
    if (!in) // no file -- one will be created when write_file is called
        return;

    in >> season_;
    in.get(); // \n
    int num_entries;
    in >> num_entries;
    in.get(); // \n
    for (int i = 0; i < num_entries; i++) {
        PlayerEntry new_entry;
        in >> new_entry;
        // m_entries[new_entry.name] = new_entry;
        m_entries_.insert(m_entries_.end(),
            { new_entry.name_, new_entry });
    }
    categorize();
}

bool SoccerRecord::search(const PlayerEntry& e, const std::string& keyword) {

    s_entries_.clear();

    if (!keyword.empty()) {
        for (auto it = m_entries_.begin(); it != m_entries_.end(); it++) {

            if (it->second.lname_.find(keyword) != std::string::npos ||
                it->second.fname_.find(keyword) != std::string::npos) {
                s_entries_.insert({ it->second.name_, it });

            }
        }
    }
    else if (!e.lname_.empty() || !e.fname_.empty()) {
        auto itr = m_entries_.lower_bound({ e.lname_, e.fname_ });
        while ((itr != m_entries_.end()) && (itr->first.first == e.lname_)) {
            if (itr->second == e) {
                s_entries_.insert({ itr->second.name_, itr });

            }
            itr++;
        }
    }
    else {

        for (auto it = m_entries_.begin(); it != m_entries_.end(); it++) {
            if (it->second == e) {
                s_entries_.insert({ it->second.name_, it });

            }
        }
    }

    if (!s_entries_.empty()) {
        s_itr_current_entry_ = s_entries_.begin();
        return true;
    }
    else {
        s_itr_current_entry_ = s_entries_.end();
        return false;
    }
}

void SoccerRecord::edit_entry(const PlayerEntry& new_data) {

    s_itr_current_entry_->second->second.update(new_data);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SoccerRecord::next() {

    if (s_entries_.empty()) { return; }
    s_itr_current_entry_++;
    if (s_itr_current_entry_ == s_entries_.end()) { s_itr_current_entry_ = s_entries_.begin(); }

}

void SoccerRecord::previous() {

    if (s_entries_.empty()) return;
    if (s_itr_current_entry_ == s_entries_.begin()) { s_itr_current_entry_ = s_entries_.end(); }
    s_itr_current_entry_--;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SoccerRecord::new_season(const int& year) {

    m_entries_.clear();
    s_entries_.clear();
    s_itr_current_entry_ = s_entries_.end();
    season_ = year;
    std::ofstream out("Soccer.txt");
    out.close();
}

bool SoccerRecord::print(const std::string& file) {

    std::ofstream out(file);
    if (!out) return false;

    out << season_ << '\n';
    out << m_entries_.size();

    for (auto itr = m_entries_.begin(); itr != m_entries_.end(); itr++) {
        out << '\n' << itr->second;
    }
    return true;
}

bool SoccerRecord::print_main(const std::string& file) {
    std::ofstream out(file);
    if (!out) return false;

    out << season_ << '\n';
    out << m_entries_.size();

    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < categories_[i].size(); j++) {
            out << '\n' << categories_[i][j];
        }
    }
}

bool SoccerRecord::print_search(const std::string& file) {

    std::ofstream out(file);
    if (!out) return false;

    out << season_ << '\n';
    out << s_entries_.size();

    for (auto itr = s_entries_.begin(); itr != s_entries_.end(); ++itr) {
        out << '\n' << itr->second->second;
    }
    return true;

}

void SoccerRecord::category(const std::string& category) {
    int count = 0;
    int paid = 0;
    int unpaid = 0;



    for (auto itr = m_entries_.begin(); itr != m_entries_.end(); itr++) {
        if (itr->second.category_ == category) {
            count++;
            if (itr->second.status_ == "paid") {
                paid++;
            }
            else {
                unpaid++;
            }
        }

    }

    std::cout << category << ": " << count << " players, " << paid << " paid, " << unpaid << " not paid\n";

    fc += count;
    fp += paid;
    fu += unpaid;


}

void SoccerRecord::categorize() {

    for (auto itr = m_entries_.begin(); itr != m_entries_.end(); itr++) {

        if (itr->second.category_ == "U6") { categories_[0].push_back(itr->second); }
        else if (itr->second.category_ == "U8") { categories_[1].push_back(itr->second); }
        if (itr->second.category_ == "U10") { categories_[2].push_back(itr->second); }
        if (itr->second.category_ == "U12") { categories_[3].push_back(itr->second); }
        if (itr->second.category_ == "U14") { categories_[4].push_back(itr->second); }
        if (itr->second.category_ == "U17") { categories_[5].push_back(itr->second); }

    }
}
