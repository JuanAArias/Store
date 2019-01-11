/*
* comedy.h
*
* @authors Juan Arias & Nick Tibbott
*
*/
#ifndef COMEDY_H
#define COMEDY_H

#include "movie.h"

using namespace std;

/*
 * A subclass of Movie for Comedy Movies
 */
class Comedy: public Movie {

	/* Only ComedyFactory can call private constructor */
	friend class ComedyFactory;

private:

    /*
     * Constructs a comedy Movie from a title, director and release year
     */
    Comedy(const string& title, const string& director, int releaseYear);

protected:

	/*
	* Display the Items details
	*/
	virtual void display(ostream& os) const override;

public:

	/*
	* Returns the most specific type identifier of the item
	*/
	char getType() const;

    /*
     * Return the item key
     */
    string getKey() const override;

};

/*
* Factory for creating Comedy Movies
*/
class ComedyFactory : public MovieFactory {

public:

	/*
	* Constructor to self register in MovieType class
	*/
	ComedyFactory();

	/*
	* Creates and returns the right Movie from the vector of string
	*/
	Movie* create(const vector<string>& tokens) const override;
};

#endif //COMEDY_H
