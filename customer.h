/*
* customer.h
*
* @authors Juan Arias & Nick Tibbot
*
*/

#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <iostream>
#include "item.h"

using namespace std;

/*
* A Customer for a Store that has a given ID number & name,
* can borrow and return Items,
* keeps track of transaction history and currently borrowed Items
*/
class Customer {

private:
	
	/* ID of Customer */
	const long ID;
	
	/* Name of Customer */
	const string name;
	
	/* Holds the history of transactions */
	vector<string> history;
	
	/* Holds all currently borrowed Items */
	map<const Item*, int, ItemCompare> borrowedItems;

public:

	/*
	* Constructs a Customer with given ID number & name
	*/
	Customer(long ID, const string& name);

	/*
	* Destructor to display any remaining Items borrowed
	*/
	virtual ~Customer();
	
	/*
	* Returns the ID of Customer
	*/
	long getID() const;
	
	/*
	* Returns the name of Customer
	*/
	const string& getName() const;
	
	/*
	* Adds given transaction string to history vector
	*/
	bool addTransaction(const string& transaction);
	
	/*
	* Displays history of all transactions
	*/
	void displayHistory() const;
	
	/*
	* Adds given Item to vector of currently borrowed Items
	*/
	void borrowItem(const Item* item);
	
	/*
	* Returns true if currently borrowing given Item
	*/
	bool isBorrowing(const Item* item) const;
	
	/*
	* Displays all currently borrowed Items
	*/
	void displayBorrowedItems() const;
	
	/*
	* Removes given Item from vector of currently borrowed Items
	*/
	void returnItem(const Item* item);
	
};
#endif  /* CUSTOMER_H */
