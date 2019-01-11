/*
* customer.cpp
*
* @authors Juan Arias & Nick Tibbott
*
*/

#include "customer.h"

/*
	* Constructs a Customer with given ID number & name
	*/
Customer::Customer(long ID, const string &name): ID(ID), name(name) {
}

/*
* Destructor to display any remaining Items borrowed
*/
Customer::~Customer() {
	displayBorrowedItems();
}

/*
* Returns the ID of Customer
*/
long Customer::getID() const {
    return this->ID;
}

/*
* Returns the name of Customer
*/
const string& Customer::getName() const {
    return this->name;
}

/*
* Adds given transaction string to history vector
*/
bool Customer::addTransaction(const string &transaction) {
    this->history.push_back(transaction);
    return true;
}

/*
* Displays history of all transactions
*/
void Customer::displayHistory() const {
	cout << ID << " " << name << " history:" << endl; 
    for(const auto& transaction : history){
        cout << "\t" << transaction << endl;
    }
	cout << endl;
}

/*
* Adds given Item to vector of currently borrowed Items
*/
void Customer::borrowItem(const Item *item) {
	int count(1);
	if (borrowedItems.count(item)) {
		count += borrowedItems.at(item);
	}
    borrowedItems[item] = count;
}

/*
* Returns true if currently borrowing given Item
*/
bool Customer::isBorrowing(const Item *item) const {
	return borrowedItems.count(item) && borrowedItems.at(item) > 0;
}

/*
* Displays all currently borrowed Items
*/
void Customer::displayBorrowedItems() const {
	if (!borrowedItems.empty()) {
		cout << ID << " " << name << " is still borrowing:\n";
		for (const auto& pair : borrowedItems) {
			cout << "\t\t" << pair.second << " cop" <<
				 (pair.second == 1 ? "y" : "ies") << " of\n\t\t" << *pair.first
				 << endl << endl;
		}
	}
}

/*
* Removes given Item from vector of currently borrowed Items
*/
void Customer::returnItem(const Item *item) {
	if (isBorrowing(item)) {
		int count = borrowedItems.at(item);
		if (count > 1) {
			borrowedItems[item] = --count;
		} else {
			borrowedItems.erase(item);
		}
	}
}
