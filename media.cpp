/*
* media.h
*
* @authors Juan Arias & Nick Tibbott
*
*/
#include "media.h"

/*
* Friend function
* Output stream operator overload
*/
ostream& operator<<(ostream& os, const Media& media) {
	os << media.type;
	return os;
}

/*
* Static function to ensure map is initialized when subclasses self register
*@return static map holding all self registered subclasses
*/
map<string, Media *>& Media::getMap() {
    static map<string, Media*> typeMap;
    return typeMap;
}

/*
* Static function for subclasses to self register
* @param type The name of the type of Media
* @param media The instance of the subclass to self register
*/
void Media::registerType(const string& type, Media* media) {
    Media::getMap().emplace(type, media);
}

/*
 * constructs Media from a given string
 */
Media::Media(const string& type): type(type) {
}

/*
* Static function for client to retrieve a Media subclass
* according to its name as a string
* @param type The name of the type of Media
*/
const Media* Media::getMedia(const string& type) {
    auto map = Media::getMap();
    if(map.find(type) != map.end())
    {
        if (map.at(type) != nullptr)
            return map.at(type);
        else
            return nullptr;
    } else{
        return nullptr;
    }
        // return Media::getMap().count(type) ? Media::getMap().at(type) : nullptr;
}

/*
 * Less than operator overload to allow sorting in map containers
 */
bool Media::operator<(const Media& other) const {
    return this->type < other.type;
}
