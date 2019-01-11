/*
* displayhistory.h
*
* @authors Juan Arias & Nick Tibbott
*
*/

#ifndef DISPLAYHISTORY_H
#define DISPLAYHISTORY_H

#include "transaction.h"

/*
* Holds a customer's ID so we can print their history at a specified time
* Subclass of Transaction
*/
class DisplayHistory: public Transaction {

	/* Allows factory to call private constructor */
	friend class DisplayHistoryFactory;

private:

	/* Customer ID number*/
	const long customerID;

	/*
	 * Constructs a DisplayHistory object with a given Store and customer ID
	 */
	DisplayHistory(Store* store, const string& fileName, long customerID);

public:

	/*
	 * Execute the Transaction
	 */
	void execute() const override;

};


/*
* Factory for creating DisplayHistory Transactions
*/
class DisplayHistoryFactory: public TransactionFactory {

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
	DisplayHistoryFactory();

};
#endif  /* DISPLAYHISTORY_H */