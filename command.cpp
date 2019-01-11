/*
* command.cpp
*
* @authors Juan Arias & Nick Tibbott
*
* Built in Command subclass implemntations
*
*/

#include "store.h"
#include "command.h"

/*
* Protected constructor for subclasses to set store pointer
*/
Command::Command(Store* store, const string& fileName)
	:store(store), fileName(fileName) {
}

/*
* Virtual destructor
*/
Command::~Command() {
}


/*
* Constructs an AddCustomer object with a given store and line
*/
AddCustomer::AddCustomer(Store* store, long customerID, const string& name)
	:Command(store), customerID(customerID), name(name) {
}

/*
* Execute the command
*/
void AddCustomer::execute() const {
	store->addCustomer(customerID, name);
}


/*
* Constructs an AddCustomer object with a given store and line
*/
RemoveCustomer::RemoveCustomer(Store* store, long customerID)
	:Command(store), customerID(customerID) {
}

/*
* Execute the command
*/
void RemoveCustomer::execute() const {
	store->removeCustomer(customerID);
}


/*
* Constructs an AddItem object with a given store, itemType, media and line
*/
AddItem::AddItem(Store* store, const ItemType* itemType, const Media* media,
	const string& fileName, const string& line)
	:Command(store, fileName), itemType(itemType), media(media), line(line) {
}

/*
* Execute the command
*/
void AddItem::execute() const {
	store->addItem(itemType, media, fileName, line);
}


/*
* Constructs a DisplayError object with a given store and error line
*/
DisplayError::DisplayError(Store* store, const string& fileName,
						   const string& line)
	:Command(store, fileName), line(line) {
}

/*
* Execute the command
*/
void DisplayError::execute() const {
	store->displayError(fileName, line);
}
