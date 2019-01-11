/*
* borrowitem.cpp
*
* @authors Juan Arias & Nick Tibbott
*
* Implementations for BorrowItem and BorrowItemFactory
*
*/

#include "borrowitem.h"
#include "store.h"

/*
* Private constructor ensures only factory can create
* Constructs BorrowItem with given store, itemType & Item info in line of string
*/
BorrowItem::BorrowItem(Store* store, const ItemType* itemType,
	                   const string& fileName, const string& line)
	:Transaction(store, fileName), itemType(itemType), line(line) {
}

/*
* Executes the Command
*/
void BorrowItem::execute() const {
	store->lendItem(itemType, fileName, line);
}


/*
* Creates and returns the right Transaction from the vector of string
*/
Transaction* BorrowItemFactory::create(Store* store, const ItemType* itemType,
					         const string& fileName, const string& line) const {
	return new BorrowItem(store, itemType, fileName, line);
}

/*
* Default constructor to self register in Transaction
*/
BorrowItemFactory::BorrowItemFactory() {
	Transaction::registerType('B', this);
}

/*
* Anonymous global for self registering
*/
namespace {
	BorrowItemFactory borrowFactory;
}

