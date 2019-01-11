/*
* movie.cpp
*
* @authors Juan Arias & Nick Tibbott
*
*/

#include "movie.h"

/*
* Display the Items details
*/
void Movie::display(ostream& os) const {
	os << getKey() << "\n\t\t" << this->director << " " << 
		   this->title << " ";
}

/*
* constructs a Movie with a given title, director, and release year
*/
Movie::Movie(const string& title, const string& director, int releaseYear)
	:title(title), director(director), releaseYear(releaseYear) {
}

/*
* Less than operator overload for sorting in map containers
* Special sorting for Movies, sorts by greater than on Movie type (f > c),
* then sorts on less than for movieKey (A < B)
*/
bool Movie::operator<(const Item& other) const {
	if (getType() != other.getType()) {
		return getType() > other.getType();
	}
	return getKey() < other.getKey();
}


/*
* Static function to ensure map is initialized before subclasses self register
*/
map<char, MovieFactory*>& MovieType::getMap() {
	static map<char, MovieFactory*> factoryMap;
	return factoryMap;
}

/*
* Static functions for MovieFactory subclasses to self register
* with char representation
*/
void MovieType::registerType(char type, MovieFactory* factory) {
	MovieType::getMap().emplace(type, factory);
}

/*
* Constructor to self register in ItemType class
*/
MovieType::MovieType(const string& type) :ItemType(type) {
	ItemType::registerItemType(type, this);
}

/*
* Create and return the right Item from the vector of string
*/
Item* MovieType::create(const vector<string>& tokens) const {
	char type = tokens[0][0];
	Item* item = nullptr;
	if (MovieType::getMap().count(type)) {
		MovieFactory* factory = MovieType::getMap().at(type);
		item = factory->create(tokens);
	}
	return item;
}

/*
* Anonymous for self registering
*/
namespace {
	MovieType movieType("Movie");
}
