// SoccerRecord.h

#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <vector>

#include "PlayerEntry.h"

class SoccerRecord
{
public:
    void read_file(const std::string& file_name);
    void add_entry(const PlayerEntry& e);
    bool empty() const { return m_entries_.empty(); }
    bool search(const PlayerEntry& e, const std::string& keyword);
    void display_current_entry() const;
    void edit_entry(const PlayerEntry& new_data);
    void next();
    void previous();
    void new_season(const int& year);
    bool print(const std::string& file = "Soccer.txt"); //default value is used for saving when quitting program
    bool print_main(const std::string& file);
    bool print_search(const std::string& file);
    void category(const std::string& category);
    


    using Key = std::pair<std::string, std::string>; //Last name and First name
    using Search_Map = std::map<Key, std::map<Key, PlayerEntry>::iterator>; //map of iterators pointing to the entries
    //that match the search

    std::map<Key, PlayerEntry> m_entries_;
    Search_Map s_entries_;
    //  std::map<Key, PlayerEntry>::iterator itr_current_entry_;
    Search_Map::iterator s_itr_current_entry_;
    int season_;

    int fc = 0;
    int fp = 0;
    int fu = 0;
private:
    void categorize();
    std::vector<PlayerEntry> categories_[6];
};

inline void SoccerRecord::add_entry(const PlayerEntry& e) {
    m_entries_.insert({ e.name_, e });
}

inline void SoccerRecord::display_current_entry() const
{
    if (s_entries_.empty())
        return;
    std::cout << s_itr_current_entry_->second->second << std::endl;
    // std::cout << m_entries_.begin()->second << std::endl;
}
