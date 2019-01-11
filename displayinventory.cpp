/*
* displayinventory.cpp
*
* @authors Juan Arias & Nick Tibbott
* Implementations for DisplayHistory & DisplayHistoryFactory
*
*/

#include "store.h"
#include "displayinventory.h"

/*
* Constructs a DisplayInvenotry with given Store
*/
DisplayInventory::DisplayInventory(Store* store) :Transaction(store){	
}

/*
* Execute the command
*/
void DisplayInventory::execute() const {
	store->displayInventory();
}


/*
* Creates and returns the right Transaction from the vector of string
*/
Transaction* DisplayInventoryFactory::create(Store* store,
   const ItemType* itemType, const string& fileName, const string& line) const {
	return new DisplayInventory(store);
}

/*
* Default constructor to self register in Transaction class
*/
DisplayInventoryFactory::DisplayInventoryFactory() {
	Transaction::registerType('I', this);
}

/*
* Anonymous global for self registering
*/
namespace {
	DisplayInventoryFactory inventoryFactory;
}
