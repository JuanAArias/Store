/*
* media.h
*
* @authors Juan Arias & Nick Tibbott
*
*/

#ifndef DVD_H
#define DVD_H

#include "media.h"

/*
* Represents the DVD Media type
*/
class DVD: public Media {

public:
	
	/*
	* Constructor to register self in Media class and map to "D" for retrieval
	*/
	explicit DVD(const string& type);

};
#endif  /* DVD_H */