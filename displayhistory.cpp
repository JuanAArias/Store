/*
* displayhistory.cpp
*
* @authors Juan Arias & Nick Tibbott
*
* Implementations for DisplayHistory & DisplayHistoryFactory
*
*/

#include "store.h"
#include "displayhistory.h"

/*
* Constructs a DisplayHistory object with a given Store and customer ID
*/
DisplayHistory::DisplayHistory(Store* store, const string& fileName,
							  long customerID)
	:Transaction(store, fileName), customerID(customerID) {
}

/*
* Executes the instruction
*/
void DisplayHistory::execute() const {
	store->displayHistory(fileName, customerID);
}

/*
* Creates and returns the right Transaction from the vector of string
*/
Transaction* DisplayHistoryFactory::create(Store* store,
   const ItemType* itemType, const string& fileName, const string& line) const {
	return new DisplayHistory(store, fileName, stol(line.substr(2)));
}

/*
* Default constructor to self register in Transaction class
*/
DisplayHistoryFactory::DisplayHistoryFactory() {
	Transaction::registerType('H', this);
}

/*
* Anonymous global for self registering
*/
namespace {
	DisplayHistoryFactory historyFactory;
}
