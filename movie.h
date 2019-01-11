/*
* movie.h
*
* @authors Juan Arias & Nick Tibbott
*
*/

#ifndef MOVIE_H
#define MOVIE_H

#include <map>
#include "item.h"

using namespace std;

/*
* Abstract class for types of Movies to inherit common fields
*/
class Movie: public Item {

protected:

	/* All Movies have a title */
    const string title;
	
	/* All Movies have a director name */
   	const string director;
	
	/* All Movies have a release year */
    const int releaseYear;

	/*
	* Display the Items details
	*/
	virtual void display(ostream& os) const override;

    /*
     * constructs a Movie with a given title, director, and release year
     */
    Movie(const string& title, const string& director, int releaseYear);

public:

	/*
	* Less than operator overload for sorting in map containers
	* Special sorting for Movies, sorts by greater than on Movie type (f > c),
	* then sorts on less than for movieKey (A < B)
	*/
	bool operator<(const Item& other) const;

};


/*
* Abstract class for MovieFactories to have a common interface for creating Movies
*/
class MovieFactory {

public:

	/*
	* Creates and returns the right Movie from the vector of string
	*/
	virtual Movie* create(const vector<string>& tokens) const = 0;
};


/*
* Represents the ItemType for Movies and creates Movie Items through self registering factories
*/
class MovieType: public ItemType {

private:

	/*
	* Static function to ensure map is initialized before subclasses self register
	*/
	static map<char, MovieFactory*>& getMap();

public:

	/*
	* Static functions for MovieFactory subclasses to self register with char representation
	*/
	static void registerType(char type, MovieFactory* factory);

	/*
	* Constructor to self register in ItemType class with given type name
	*/
	explicit MovieType(const string& type);

	/*
	* Create and return the right Item from the vector of string
	*/
	Item* create(const vector<string>& tokens) const override;
};

#endif  /* MOVIE_H */
