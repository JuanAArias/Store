/*
* comedy.cpp
*
* @author Juan Arias & Nick Tibbott
*
*/

#include <sstream>
#include "comedy.h"

/*
* Constructs a comedy Movie from a title, director and release year
*/
Comedy::Comedy(const string& title, const string& director, int releaseYear)
	:Movie(title, director, releaseYear) {
}

/*
* Display the Items details
*/
void Comedy::display(ostream& os) const {
	Movie::display(os);
	os << releaseYear;
}

/*
* Returns the most specific type identifier of the item
*/
char Comedy::getType() const {
	return 'F';
}

/*
* Return the item key
*/
string Comedy::getKey() const {
    stringstream ss;
    ss << "F " << title << ", " << releaseYear;
    return ss.str();
}

/*
* Constructor to self register in MovieType class
*/
ComedyFactory::ComedyFactory() {
	MovieType::registerType('F', this);
}

/*
* Creates and returns the right Movie from the vector of string
*/
Movie* ComedyFactory::create(const vector<string>& tokens) const {
	return new Comedy(tokens[2], tokens[1], std::stoi(tokens[3]));
}

/*
* Anonymous global for self registering
*/
namespace {
	ComedyFactory comedyFactory;
}