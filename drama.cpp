/*
* drama.cpp
*
* @author Juan Arias & Nick Tibbott
*
*/

#include <sstream>
#include "drama.h"

/*
* Constructor from a title, director and release year
*/
Drama::Drama(const string& title, const string& director, int releaseYear)
	:Movie(title, director, releaseYear) {
}

/*
	* Display the Items details
	*/
void Drama::display(ostream& os) const {
	Movie::display(os);
	os << this->releaseYear;
}

/*
* Returns the most specific type identifier of the item
*/
char Drama::getType() const {
	return 'D';
}

/*
* Return the item key
*/
string Drama::getKey() const {
    stringstream ss;
    ss << "D " << director << ", " << title;
    return ss.str();
}


/*
* Constructor to self register in MovieType class
*/
DramaFactory::DramaFactory() {
	MovieType::registerType('D', this);
}

/*
* Creates and returns the right Movie from the vector of string
*/
Movie* DramaFactory::create(const vector<string>& tokens) const {
	return new Drama(tokens[2], tokens[1], std::stoi(tokens[3]));
}

/*
* Anonymous global for self registering
*/
namespace {
	DramaFactory dramaFactory;
}
