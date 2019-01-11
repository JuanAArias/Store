/*
* item.h
*
* @authors Juan Arias & Nick Tibbott
*
*/

#ifndef ITEM_H
#define ITEM_H

#include <vector>
#include <iostream>
#include <string>
#include <map>

using namespace std;

/*
* Extensibility for different kinds of Item subclasses
*/
class Item {

	/*
	* Friend function
	* Output stream operator overload
	*/
	friend ostream& operator<<(ostream& os, const Item& item);

private:

protected:

	/*
	* Display the Items details
	*/
	virtual void display(ostream& os) const = 0;


public:

	/*
	* Virtual destructor
	*/
	virtual ~Item();

	/*
	* Returns the most specific type identifier of the Movie
	*/
	virtual char getType() const = 0;

	/*
	* Returns the key that uniquely identifies an Item
	*/
    virtual string getKey() const = 0;
	
	/*
	* Less than operator overload for sorting in map containers
	*/
    virtual bool operator<(const Item& other) const = 0;
	
};


/*
 * Extensibility to define self registering ItemTypes that should manage their own factories for specific Items
 */
class ItemType {

	/*
	* Friend function
	* Output stream operator overload
	*/
	friend ostream& operator<<(ostream& os, const ItemType& itemType);

private:

	/*
	* Static function to ensure map is initialized before subclasses self register
	*/
	static map<string, ItemType*>& getMap();

	/* Name of type as string */
	const string type;

protected:

	/*
	* Static function for subclasses to self register with a given name in string
	*/
	static void registerItemType(const string& type, ItemType* itemType);

	/*
	* Constructs ItemType with given type name as string
	*/
	explicit ItemType(const string& type);

public:

	/*
	* Static function for client to get ItemType from its name in string
	*/
	static const ItemType* getItemType(const string& type);

	/*
	* Create & return the right Item from the info in the given vector
	*/
	virtual Item* create(const vector<string>& tokens) const = 0;

	/*
	* Less than operator overload to allow sorting in map containers
	*/
	bool operator<(const ItemType& other) const;

};

/*
*
*/
struct ItemCompare {
	
	/*
	*
	*/
	bool operator() (const Item* item1,const Item* item2) const;
};
#endif  /* ITEM_H */
