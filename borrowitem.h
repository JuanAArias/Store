/*
* borrowitem.h
*
* @authors Juan Arias & Nick Tibbott
*
*/

#ifndef BORROWITEM_H
#define BORROWITEM_H

#include "transaction.h"
#include "item.h"

using namespace std;

/*
* Command for Store to allow a given Customer to borrow a given Item
*/
class BorrowItem: public Transaction {

	/* Allows factory to call private constructor */
	friend class BorrowItemFactory;

private:
	
	/* Store must know ItemType in order to lend an Item */
	const ItemType* itemType;
	
	/* Item info */
	const string line;
	
	/*
	* Private constructor ensures only factory can create
	* Constructs BorrowItem with given store, itemType
	* & Item info in line of string
	*/
	BorrowItem(Store* store, const ItemType* itemType,
		       const string& fileName, const string& line);
	
public:
	
	/*
	* Executes the Command
	*/
	void execute() const override;
	
};


/*
* Factory for creating BorrowInventory Transactions
*/
class BorrowItemFactory: public TransactionFactory {

private:

	/*
	* Creates and returns the right Transaction from the vector of string
	*/
	Transaction* create(Store* store, const ItemType* itemType,
		             const string& fileName, const string& line) const override;

public:

	/*
	 * Default constructor to self register in Transaction
	 */
	BorrowItemFactory();

};
#endif  /* BORROWITEM_H */
