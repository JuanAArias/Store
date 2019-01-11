/*
* drama.h
*
* @author Juan Arias & Nick Tibbott
*
*/

#ifndef DRAMA_H
#define DRAMA_H

#include "movie.h"

/*
 * A subclass of Movie for Drama Movies
 */
class Drama: public Movie {

	/* Only DramaFactory can call private constructor */
	friend class DramaFactory;

private:

    /*
     * Constructor from a title, director and release year
     */
    Drama(const string& title, const string& director, int releaseYear);

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
* Factory for creating Drama Movies
*/
class DramaFactory: public MovieFactory {

public:

	/*
	* Constructor to self register in MovieType class
	*/
	DramaFactory();

	/*
	* Creates and returns the right Movie from the vector of string
	*/
	Movie* create(const vector<string>& tokens) const override;
};

#endif //DRAMA_H
