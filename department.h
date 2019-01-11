/*
* department.h
*
* @authors Juan Arias & Nick Tibbott
*
*/

#ifndef DEPARTMENT_H
#define DEPARTMENT_H

#include "media.h"
#include "inventory.h"

using namespace std;

/*
* Holds Inventories according to Media types
*/
class Department {

	/*
	* Friend function
	* Output stream operator overload
	*/
	friend ostream& operator<<(ostream& os, const Department& dept);
	

private:
    
	/* Map each Inventory according to a Media type */
	map<const Media*, Inventory*> inventoryMap;

	/*
	* Deallocates all dynamic memory
	*/
	void clear();

public:
	
	/*
	* Destructor to deallocate all dynamic memory
	*/
	virtual ~Department();
	
	/*
	* Adds the given Item of the given Media type into Inventory, optional stock amount
	*/
	void addItem(const Media* media, Item* item, int stockAmount);

	/*
	* Lends the given Item of the given Media type
	* @return true if Item can be lent (in-stock)
	*/
	bool lendItem(const Media* media, const Item* item);

	/*
	* The given Item of the given Media type is "returned" back into Inventory
	*/
	bool returnItem(const Media* media, const Item* item);

	/*
	* Returns the given Item of the given Media type and itemKey
	*/
	const Item* getItem(const Media* media, const string& itemKey) const;

};
#endif  /* DEPARTMENT_H */
