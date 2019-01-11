/*
* item.cpp
*
* @authors Juan Arias & Nick Tibbott
*
* Implementations for Item abstract class
*
*/

#include "item.h"

/*
* Friend function
* Output stream operator overload
*/
ostream& operator<<(ostream& os, const Item& item) {
	item.display(os);
	return os;
}


/*
* Friend function
* Output stream operator overload
*/
ostream& operator<<(ostream& os, const ItemType& itemType) {
	os << itemType.type;
	return os;
}

/*
* Static function to ensure map is initialized before subclasses self register
*/
map<string, ItemType*>& ItemType::getMap() {
	static map<string, ItemType*> typeMap;
	return typeMap;
}

/*
* Static function for subclasses to self register with a given name in string
*/
void ItemType::registerItemType(const string& type, ItemType* itemType) {
	ItemType::getMap().emplace(type, itemType);
}

/*
* Constructs ItemType with given type name as string
*/
ItemType::ItemType(const string& type) :type(type) {
}

/*
* Static function for client to get ItemType from its name in string
*/
const ItemType* ItemType::getItemType(const string& type) {
	return ItemType::getMap().count(type) ? ItemType::getMap().at(type) : nullptr;
}

/*
* Less than operator overload to allow sorting in map containers
*/
bool ItemType::operator<(const ItemType& other) const {
	return this->type < other.type;
}

/*
*
*/
bool ItemCompare::operator() (const Item* item1, const Item* item2) const {
	return *item1 < *item2;
}

/*
* Virtual destructor
*/
Item::~Item() {
}
