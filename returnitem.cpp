/*
* returnitem.cpp
*
* @authors Juan Arias & Nick Tibbott
*
* Implementations for ReturnItem & ReturnItemFactory
*
*/

#include "store.h"
#include "returnitem.h"

/*
* Constructs a ReturnItem  object from a given Store,
* ItemType, and string
*/
ReturnItem::ReturnItem(Store* store, const ItemType* itemType,
					   const string& fileName, const string& line)
	:Transaction(store, fileName), itemType(itemType), line(line) {
}

/*
* Executes the instruction
*/
void ReturnItem::execute() const {
	store->returnItem(itemType, fileName, line);
}

/*
* Creates and returns the right Transaction from the vector of string
*/
Transaction* ReturnItemFactory::create(Store* store, const ItemType* itemType,
	                         const string& fileName, const string& line) const {
	return new ReturnItem(store, itemType, fileName, line);
}

/*
* Default constructor to self register in Transaction class
*/
ReturnItemFactory::ReturnItemFactory() {
	Transaction::registerType('R', this);
}

/*
* Anonymous global for self registering
*/
namespace {
	ReturnItemFactory returnFactory;
}
