/*
* inventory.cpp
*
* @authors Juan Arias & Nick Tibbott
*
* Implementations for Inventory and Stock classes
*
*/

#include "inventory.h"

/*
* Friend function
* Output stream operator overload
*/
ostream& operator<<(ostream& os, const Inventory& inv) {
	for (const auto& pair : inv.itemStock) {
		const auto* stock = pair.second;
		cout << "\t\t" << *pair.first << "\n\t\t" << stock->amountInStore() <<
			" in store, " << stock->amountBorrowed() << " borrowed\n" << endl;
	}
	return os;
}

/*
* Construct a Stock with a given in-store amount
*/
Inventory::Stock::Stock(int inStore) :inStore(inStore), borrowed(0) {
}

/*
* Greater than operator overload
* returns true if in-store amount is greater than count,
* else false
*/
bool Inventory::Stock::operator>(int count) const {
	return this->inStore > count;
}

/*
* Prefix increment operator overload
* increments in-store amount and decrements borrowed amount
*/
Inventory::Stock& Inventory::Stock::operator++() {
	++this->inStore;
	--this->borrowed;
	return *this;
}

/*
* Prefix decrement operator overload
* decrements in-store amount and increments borrowed amount
*/
Inventory::Stock& Inventory::Stock::operator--() {
	--this->inStore;
	++this->borrowed;
	return *this;
}

/*
* Returns the amount currently in-store
*/
int Inventory::Stock::amountInStore() const {
	return this->inStore;
}

/*
* Returns the amount currently borrowed
*/
int Inventory::Stock::amountBorrowed() const {
	return this->borrowed;
}

/*
* Increases the total Stock by the given amount
*/
void Inventory::Stock::increase(int amount) {
	this->inStore += amount;
}


/*
* Deallocates all dynamic memory
*/
void Inventory::clear() {
	for (auto& pair : this->itemStock) {
		delete pair.first;
		delete pair.second;
	}
}

/*
* Returns true if given Item has in-store amount greater than zero
*/
bool Inventory::inStock(const Item* item) const {
	bool inStock(this->itemStock.count(item));
	if (inStock) {
		const Stock* stock = this->itemStock.at(item);
		inStock = *stock > 0;
	}
	return inStock;
}

/*
* Destructor to deallocate all dynamic memory
*/
Inventory::~Inventory() {
	this->clear();
}

/*
* Adds the given Item and Stock
*/
void Inventory::addItem(Item* item, int stockAmount) {
	this->itemMap.emplace(item->getKey(), item);
	this->itemStock.emplace(item,  new Stock(stockAmount));
}

/*
* Lends the given Item by decreasing in-store amount &
* increasing borrowed amount
* @ return true if Item can be lent (in-stock)
*/
bool Inventory::lendItem(const Item* item) {
	bool canLend(false);
	if (inStock(item)) {
		Stock* stock = itemStock.at(item);
		--(*stock);
		canLend = true;
	}
	return canLend;
}

/*
* Returns the given item by increasing in-store amount &
* decreasing borrowed amount
*/
bool Inventory::returnItem(const Item* item) {
	bool canReturn(false);
	Stock* stock = itemStock.at(item);
	if (itemStock.count(item) && stock->amountBorrowed() > 0) {
		++(*stock);
		canReturn = true;
	}
	return canReturn;
}

/*
* Returns the Item with the given key
*/
const Item* Inventory::getItem(const string& itemKey) const {
	const Item* item = nullptr;
	if (itemMap.count(itemKey)) {
		item = itemMap.at(itemKey);
	}
	return item;
}

