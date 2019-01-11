/*
* media.h
*
* @authors Juan Arias & Nick Tibbott
*
*/

#ifndef MEDIA_H
#define MEDIA_H

#include <string>
#include <map>

using namespace std;

/*
* Allows extension many types of Media that a Store could have
*/
class Media {

	/*
	* Friend function
	* Output stream operator overload
	*/
	friend ostream& operator<<(ostream& os, const Media& media);

private:

	/*
	* Static function to ensure map is initialized when subclasses self register
	*@return static map holding all self registered subclasses
	*/
	static map<string, Media*>& getMap();

	/* type of media */
	const string type;

protected:
	
	/*
	* Static function for subclasses to self register
	* @param type The name of the type of Media
	* @param media The instance of the subclass to self register
	*/
	static void registerType(const string& type, Media* media);

	/*
	 * constructs Media from a given string
	 */
	explicit Media(const string& type);

public:

	/*
	* Static function for client to retrieve a Media subclass
	* according to its name as a string
	* @param type The name of the type of Media
	*/
	static const Media* getMedia(const string& type);


	/*
	 * Less than operator overload to allow sorting in map containers
	*/
	bool operator<(const Media& other) const;
	
};
#endif  /* MEDIA_H */