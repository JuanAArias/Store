/*
* returnitem.h
*
* @authors Juan Arias & Nick Tibbott
*
*/

#ifndef RETURNITEM_H
#define RETURNITEM_H

#include "transaction.h"
#include "item.h"

using namespace std;

/*
 * Holds an ItemType and a string to be display to the console
 */
class ReturnItem: public Transaction {

	/* Allows factory to call private constructor */
	friend class ReturnItemFactory;

private:

	/* ItemType of the Item being returned */
	const ItemType* itemType;

	/* Return description */
	const string line;


	/*
	 * Constructs a ReturnItem  object from a given Store,
	 * ItemType, and string
	 */
	ReturnItem(Store* store, const ItemType* itemType, const string& fileName,
		       const string& line);

public:

	/*
	 * Executes the instruction
	 */
	void execute() const override;

};


/*
* Factory for creating ReturnItem Transactions
*/
class ReturnItemFactory : public TransactionFactory {

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
	ReturnItemFactory();
};

#endif /* RETURNITEM_H */
