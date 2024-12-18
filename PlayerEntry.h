// PlayerEntry.h

#ifndef _PlayerEntry_h_
#define _PlayerEntry_h_

#include <fstream>
#include <iostream>
#include <string>

class PlayerEntry
{
public:

    PlayerEntry() : lname_(""), fname_(""), category_(""), status_(""), birth_yr_(-1)
    {
        name_ = std::make_pair(lname_, fname_);
    }

    PlayerEntry(const std::string& lname, const std::string& fname, const std::string& cat, //category already given
        const std::string& status, int birth) : lname_(lname), fname_(fname), category_(cat), status_(status), birth_yr_(birth)
    {
        name_ = std::make_pair(lname, fname);
    }

    PlayerEntry(const std::string& lname, const std::string& fname, int age, // calculates category by age given by Season - birth_yr_
        const std::string& status, int birth) : lname_(lname), fname_(fname), status_(status), birth_yr_(birth)
    {
        name_ = std::make_pair(lname, fname);
        category_ = category(age);
        
    }

    friend std::istream& operator>>(std::istream& in, PlayerEntry& e);
    friend std::ostream& operator<<(std::ostream& out, const PlayerEntry& e);
    friend bool operator==(const PlayerEntry& e, const PlayerEntry& search);
    void update(const PlayerEntry& new_data);
    const std::string category(int cat);

    using Key = std::pair<std::string, std::string>;
    Key name_;
    std::string lname_, fname_, category_, status_;
    int birth_yr_;
};

inline std::ostream& operator<<(std::ostream& out, const PlayerEntry& e) {
    out << e.lname_ << " " << e.fname_ << " " << e.birth_yr_ << ' ' << e.category_ << '\n' << e.status_;
    return out;
}


#endif
