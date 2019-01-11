/*
* classic.h
*
* @authors Juan Arias & Nick Tibbott
*
*/

#ifndef CLASSIC_H
#define CLASSIC_H

#include <sstream>
#include <string>
#include "movie.h"

using namespace std;

/*
 * A subclass of Movie for Classic Movies
 */
class Classic: public Movie {

	/* Only ClassicFactory can call private constructor */
	friend class ClassicFactory;

private:

    /* Major actor in the film */
    const string majorActor;

    /* Film's release month */
    const int releaseMonth;

    /*
     * Constructs a classic Movie from a title, director, release year,
     * major actor, and release month
     */
    Classic(const string& title, const string& director, int releaseYear,
            const string& majorActor, int releaseMonth);

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
* Factory for creating Classic Movies
*/
class ClassicFactory: public MovieFactory {

public:

	/*
	* Constructor to self register in MovieType class
	*/
	ClassicFactory();

	/*
	* Creates and returns the right Movie from the vector of string
	*/
	Movie* create(const vector<string>& tokens) const override;

};
#endif //CLASSIC_H
