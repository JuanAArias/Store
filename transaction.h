/*
* transaction.h
*
* @authors Juan Arias & Nick Tibbott
*
*/

#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include <vector>
#include <map>
#include "command.h"

using namespace std;


class Transaction;

/*
 * Abstract class for TransactionFactories to have a common interface for
 * creating Transactions
 */
class TransactionFactory {

	/* Only Transaction can use factories */
	friend class Transaction;

private:

	/*
	 * Creates a Transaction from a given string
	 */
	virtual Transaction* create(Store* store, const ItemType* itemType,
						  const string& fileName, const string& line) const = 0;

};


/*
* Abstract class for extensibility with Transactions to be created
* using self registering factories
*/
class Transaction: public Command {

private:

	/*
	* Static function to ensure map is initialized before
	* TransactionFactories self register
	*/
	static map<char, TransactionFactory*>& getMap();

protected:

	/*
	* Protected constructor for subclasses to set store pointer
	*/
	explicit Transaction(Store* store, const string& fileName = "");

public:

	/*
	* Static function for TransactionFactories to self register
	* with char representing their type
	*/
	static void registerType(char type, TransactionFactory* factory);

	/*
	* Create and return the right Transaction from the type and line of info
	*/
	static Transaction* create(Store* store, const ItemType* itemType,
						 const string& fileName, char type, const string& line);

	/*
	* Virtual destructor
	*/
	virtual ~Transaction();

};
#endif  /* TRANSACTION_H */
