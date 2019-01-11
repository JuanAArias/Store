//
// Created by Nick T on 11/28/18.
//

#include <cassert>
#include "department.h"

/*
* Friend function
* Output stream operator overload
*/
ostream& operator<<(ostream& os, const Department& dept) {
	for (const auto& pair : dept.inventoryMap) {
		cout << "\t" << *pair.first << " media:\n" << *pair.second;
	}
	return os;
}

/*
* Deallocates all dynamic memory
*/
void Department::clear() {
	for (const auto& pair : this->inventoryMap) {
		delete pair.second;
	}
}

/*
* Destructor to deallocate all dynamic memory
*/
Department::~Department() {
	this->clear();
}

/*
* Adds the given Item of the given Media type into Inventory, optional stock amount
*/
void Department::addItem(const Media* media, Item* item, int stockAmount) {
	if (!inventoryMap.count(media)) {
		inventoryMap.emplace(media, new Inventory());
	}
	Inventory* inv = inventoryMap.at(media);
	inv->addItem(item, stockAmount);
}

/*
* Lends the given Item of the given Media type
* @return true if Item can be lent (in-stock)
*/
bool Department::lendItem(const Media* media, const Item* item) {
	Inventory* inv = inventoryMap.at(media);
	return inv->lendItem(item);
}

/*
* The given Item of the given Media type is "returned" back into Inventory
*/
bool Department::returnItem(const Media* media, const Item* item) {
	Inventory* inv = inventoryMap.at(media);
	return inv->returnItem(item);
}

/*
* Returns the given Item of the given Media type and itemKey
*/
const Item* Department::getItem(const Media* media, const string& itemKey) const {
	const Inventory* inv = inventoryMap.at(media);
	return inv->getItem(itemKey);
}


