//
// Created by Nick T on 11/28/18.
//

#ifndef HASHTABLE_H
#define HASHTABLE_H

/*
* Uses hashing to store and retrieve a templated type with constant complexity
*/
template <class T>
class HashTable {

private:

	/*
	* Represents state of an index in HashTable for collision resolutions
	*/
	class IndexState {

	private:

		/* Key of item */
		int key;

		/* The item in the index of the HashTable */
		T item;
		
		/* Indiciates if index already occupied */
		bool occupied;

	public:

		/*
		* Default constructor
		*/
		IndexState();

		/*
		* Return true if index in HashTable occupied, else false
		*/
		bool isOccupied() const;

		/*
		* Returns the item at the index
		*/
		T& getItem();

		/*
		* Return the key at the index
		*/
		int getKey() const;


		/*
		* Sets given item as the stored item in the index of the HashTable
		*/
		void setItem(int key, const T& item);
	};

	/* Default table size*/
	static const int DEFAULT = 29;

	/* Array of T pointers with IndexStates */
	IndexState* table;

	/* Size of table */
	int tableSz;

	/*
	* Hash function for lookup in table
	*/
	int hash(int key) const;

	/*
	* Gets the quadratic probe of the hash based on iteration i
	*/
	int quadraticProbe(int hash, int i) const;


	/*
	* Deallocates all dynamic memory
	*/
	void clear();

public:

	/*
	* Constructs a HashTable with optional size
	*/
	explicit HashTable(int size = DEFAULT);

	/*
	* Deallocates all dynamic memory on destruction
	*/
	virtual ~HashTable();

	/*
	* Add new T item mapped with given key
	*/
	void add(int key, const T& item);

	/*
	* Get T item mapped to given key
	*/
	T& get(int key) const;

	/*
	*
	*/
	bool has(int key) const;

	/*
	* Returns iterator at first Item in table
	*/
	T* begin();

	/*
	* Returns iterator at last Item in table
	*/
	T* end();

	/*
	* Returns const iterator at first Item in table
	*/
	const T* begin() const;

	/*
	* Returns const iterator at last Item in table
	*/
	const T* end() const;

};
#include "hashtable.cpp"
#endif  //HASHTABLE_H
