/*
* inventory.h
*
* @authors Juan Arias & Nick Tibbott
*
*/

#ifndef INVENTORY_H
#define INVENTORY_H

#include <iostream>
#include "item.h"

using namespace std;

/*
* Represents an Inventory for the Stock of given Items for a certain Media type (see department.h)
*/
class Inventory {

	/*
	* Friend function
	* Output stream operator overload
	*/
	friend ostream& operator<<(ostream& os, const Inventory& inv);

private:

	/*
	* Represents the stock of an Item held in store and keeps track
	* of amount currently borrowed
	*/
	class Stock {

	private:

		/* Amount currently in-store */
		int inStore;

		/* Amount currently borrowed */
		int borrowed;

	public:

		/*
		* Construct a Stock with a given in-store amount
		*/
		explicit Stock(int inStore);

		/*
		* Greater than operator overload
		* returns true if in-store amount is greater than count,
		* else false
		*/
		bool operator>(int count) const;

		/*
		* Prefix increment operator overload
		* increments in-store amount and decrements borrowed amount
		*/
		Stock& operator++();

		/*
		* Prefix decrement operator overload
		* decrements in-store amount and increments borrowed amount
		*/
		Stock& operator--();

		/*
		* Returns the amount currently in-store
		*/
		int amountInStore() const;

		/*
		* Returns the amount currently borrowed
		*/
		int amountBorrowed() const;

		/*
		* Increases the total Stock by the given amount
		*/
		void increase(int amount);

	};

	/* Map each Item to a Stock for tracking amount in-store & amount borrowed*/
    map<const Item*, Stock*, ItemCompare> itemStock;
	
	/* Map each Item from its key for easy retrieval */
    map<const string, Item*> itemMap;
	
	/*
	* Deallocates all dynamic memory
	*/
    void clear();
	
	/*
	* Returns true if given Item has in-store amount greater than zero
	*/
    bool inStock(const Item* item) const;
	
public:

    /*
	* Destructor to deallocate all dynamic memory
	*/
    virtual ~Inventory();
	
	/*
	* Adds the given Item and Stock
	*/
    void addItem(Item* item, int stockAmount);
	
	/*
	* Lends the given Item by decreasing in-store amount &
	* increasing borrowed amount
	* @ return true if Item can be lent (in-stock)
	*/
	bool lendItem(const Item* item);
	
	/*
	* Returns the given item by increasing in-store amount &
	* decreasing borrowed amount
	*/
	bool returnItem(const Item* item);
	
	/*
	* Returns the Item with the given key
	*/
	const Item* getItem(const string& itemKey) const;

};
#endif  /* INVENTORY_H */
