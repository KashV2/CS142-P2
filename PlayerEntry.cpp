//PlayerEntry.cpp

#include "PlayerEntry.h"

std::istream& operator>>(std::istream& in, PlayerEntry& e) {
	in >> e.lname_ >> e.fname_ >> e.birth_yr_ >> e.category_;
	in.ignore();
	getline(in, e.status_);
	e.name_ = std::make_pair(e.lname_, e.fname_);
	return in;
}

bool operator==(const PlayerEntry& e, const PlayerEntry& search) {
	if (!search.lname_.empty() && (e.lname_ != search.lname_)) { return false; }

	if (!search.fname_.empty() && (e.fname_ != search.fname_)) { return false; }

	//if (!search.category_.empty() &&(e.category_ != search.category_)) { return false; }

	if (!search.status_.empty() && (e.status_ != search.status_)) { return false; }

	if ((search.birth_yr_ != -1) && (e.birth_yr_ != search.birth_yr_)) { return false; }

	return true;
}

void PlayerEntry::update(const PlayerEntry& new_data) {
	if (!new_data.lname_.empty()) { lname_ = new_data.lname_; }
	if (!new_data.fname_.empty()) { fname_ = new_data.fname_; }
	if (!new_data.category_.empty()) { category_ = new_data.category_; }
	if (!new_data.status_.empty()) { status_ = new_data.status_; }
	if (new_data.birth_yr_ != -1) { birth_yr_ = new_data.birth_yr_; }
}

const std::string PlayerEntry::category(int category) {
	if (category < 6) { return std::string("U6"); }
	else if (category < 8) { return std::string("U8"); }
	else if (category < 10) { return std::string("U10"); }
	else if (category < 12) { return std::string("U12"); }
	else if (category < 14) { return std::string("U14"); }
	else return std::string("U17");
}
