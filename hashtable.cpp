/*
* hashtable.cpp
*
* Implementations for HashTable
*
* @authors Juan Arias & Nick Tibbott
*/

#include <climits>

/*
* Default constructor
*/
template <class T>
HashTable<T>::IndexState::IndexState() :key(INT_MIN), occupied(false) {
}

/*
* Return true if index in HashTable occupied, else false
*/
template <class T>
bool HashTable<T>::IndexState::isOccupied() const {
	return occupied;
}

/*
* Returns the item at the index
*/
template <class T>
T& HashTable<T>::IndexState::getItem() {
	return item;
}

/*
* Return the key at the index
*/
template <class T>
int HashTable<T>::IndexState::getKey() const {
	return key;
}

/*
* Sets given item as the stored item in the index of the HashTable
*/
template <class T>
void HashTable<T>::IndexState::setItem(int key, const T& item) {
	this->key = key;
	this->item = item;
	occupied = true;
}


/*
* Hash function for lookup in table
*/
template <class T>
int HashTable<T>::hash(int key) const {
	return key % tableSz;
}

/*
* Gets the quadratic probe of the hash based on iteration i
*/
template <class T>
int HashTable<T>::quadraticProbe(int hash, int i) const {
	return (hash + i * i) % tableSz;
}

/*
* Deallocates all dynamic memory
*/
template <class T>
void HashTable<T>::clear() {
	delete[] table;
}

/*
* Constructs a HashTable with optional size
*/
template <class T>
HashTable<T>::HashTable(int size) :table(new IndexState[size]), tableSz(size) {
}

/*
* Deallocates all dynamic memory on destruction
*/
template <class T>
HashTable<T>::~HashTable() {
	clear();
}

/*
* Add new T item mapped with given key
*/
template <class T>
void HashTable<T>::add(int key, const T& item) {
	int hash(this->hash(key));
	for (int i(0); table[hash].isOccupied(); ++i) {
		hash = quadraticProbe(hash, i);
	}
	table[hash].setItem(key, item);
}

/*
* Get T item mapped to given key
*/
template <class T>
T& HashTable<T>::get(int key) const {
	int hash(this->hash(key));
	IndexState* iState = &table[hash];
	for (int i(0); iState->isOccupied() && iState->getKey() != key; ++i) {
		hash = quadraticProbe(hash, i);
		iState = &table[hash];
	}
	return iState->getItem();
}

/*
*
*/
template <class T>
bool HashTable<T>::has(int key) const {
	int hash(this->hash(key));
	IndexState* iState = &table[hash];
	bool hasKey;
	for (int i(0); !(hasKey = iState->getKey() == key) && iState->isOccupied(); ++i) {
		hash = quadraticProbe(hash, i);
		iState = &table[hash];
	}
	return hasKey;
}

/*
* Returns iterator at first Item in table
*/
template<class T>
T* HashTable<T>::begin() {
	return &table[0].getItem();
}

/*
* Returns iterator at last Item in table
*/
template<class T>
T* HashTable<T>::end() {
	return &table[tableSz - 1].getItem();
}

/*
* Returns const iterator at first Item in table
*/
template<class T>
const T* HashTable<T>::begin() const {
	return &table[0].getItem();
}

/*
* Returns const iterator at last Item in table
*/
template<class T>
const T* HashTable<T>::end() const {
	return &table[tableSz - 1].getItem();
}
