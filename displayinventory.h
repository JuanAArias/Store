/*
* displayinventory.h
*
* @authors Juan Arias & Nick Tibbott
*
*/

#ifndef DISPLAYINVENTORY_H
#define DISPLAYINVENTORY_H

#include "transaction.h"

using namespace std;

/*
* Command for Store to display inventory
*/
class DisplayInventory: public Transaction {

	/* Allows factory to call private constructor */
	friend class DisplayInventoryFactory;

private:

	/*
	* Constructs a DisplayInvenotry with given Store
	*/
	explicit DisplayInventory(Store* store);

public:

	/*
	* Execute Command
	*/
	void execute() const override;

};


/*
* Factory for creating DisplayInventory Transactions
*/
class DisplayInventoryFactory: public TransactionFactory {

private:

	/*
	* Creates and returns the right Transaction from the vector of string
	*/
	Transaction* create(Store* store, const ItemType* itemType,
		             const string& fileName, const string& line) const override;

public:

	/*
	 * Default constructor to self register in Transaction class
	 */
	DisplayInventoryFactory();

};
#endif  /* DISPLAYINVENTORY_H */
