/*
* dvd.cpp
*
* @authors Juan Arias & Nick Tibbott
*
*/

#include "dvd.h"

/*
* Constructor to register self in Media class and map to "D" for retrieval
*/
DVD::DVD(const string& type): Media(type) {
    Media::registerType(type, this);
}

/* Create global variable */
namespace {
    DVD dvd("D");
}
