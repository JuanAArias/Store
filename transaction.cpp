/*
* transaction.h
*
* @authors Juan Arias & Nick Tibbott
*
* Implementations for Transaction and TransactionFactory
*
*/

#include "store.h"
#include "transaction.h"

/*
* Static function to ensure map is initialized before
* TransactionFactories self register
*/
map<char, TransactionFactory*>& Transaction::getMap() {
	static map<char, TransactionFactory*> factoryMap;
	return factoryMap;
}

/*
* Protected constructor for subclasses to set store pointer
*/
Transaction::Transaction(Store* store, const string& fileName)
	:Command(store, fileName) {
}

/*
* Static function for TransactionFactories to self register with
* char representing their type
*/
void Transaction::registerType(char type, TransactionFactory* factory) {
	Transaction::getMap().emplace(type, factory);
}

/*
* Create and return the right Transaction from the type and line of info
*/
Transaction* Transaction::create(Store* store, const ItemType* itemType,
	                    const string& fileName, char type, const string& line) {
	Transaction* trans = nullptr;
	if (Transaction::getMap().count(type)) {
		TransactionFactory* factory = Transaction::getMap().at(type);
		trans = factory->create(store, itemType, fileName, line);
	}
	return trans;
}

/*
* Virtual destructor
*/
Transaction::~Transaction() {
}
