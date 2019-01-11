/*
* command.h
*
* @authors Juan Arias & Nick Tibbott
*
* Command class for extendable Commands and provided basic Commands
*
*/

#ifndef COMMAND_H
#define COMMAND_H

using namespace std;

#include "item.h"
#include "media.h"

/* Forward declaration to avoid circular linkage */
class Store;

/*
* Abstract class for all Commands to have common interface
*/
class Command {

protected:

	/* All Commands will operate on a Store */	
	Store* store;

	/* Name of file with Command */
	const string fileName;

	/*
	* Protected constructor for subclasses to set store pointer
	*/
	explicit Command(Store* store, const string& fileName = "");
	
public:

	/*
	* Virtual destructor
	*/
	virtual ~Command();

	/*
	* Executes the Command
	*/
	virtual void execute() const = 0;
	
};


/*
 * subclass of Command to create a customer
 */
class AddCustomer: public Command {

	/* Only Store can call private constructor */
	friend class Store;

private:

	/* ID for the customer */
	const long customerID;

	/* Name for the customer */
	const string name;

	/*
	* Constructs an AddCustomer object with a given store and line
	*/
	AddCustomer(Store* store, long customerID, const string& name);

public:

	/*
	* Execute the command
	*/
	void execute() const override;

};


/*
* Removes Customer from Store at destruction to deallocate memory
*/
class RemoveCustomer: public Command {

	/* Only Store can call private constructor */
	friend class Store;

private:

	/* ID for the customer */
	const long customerID;

	/*
	* Constructs an AddCustomer object with a given store and line
	*/
	RemoveCustomer(Store* store, long customerID);

public:

	/*
	* Execute the command
	*/
	void execute() const override;
	
};


/*
 * subclass of Command to add an item
 */
class AddItem: public Command {

	/* Only Store can call private constructor */
	friend class Store;

private:

	/* type of item to add */
	const ItemType* itemType;

	/* type of media for the item */
	const Media* media;

	/* line from "data4commands.txt" */
	const string line;

	/*
	* Constructs an AddItem object with a given store, itemType, media and line
	*/
	AddItem(Store* store, const ItemType* itemType, const Media* media,
		    const string& fileName, const string& line);

public:

	/*
	* Execute the command
	*/
	void execute() const override;

};


/*
* Holds error message data to print to the console
* Subclass of Command
*/
class DisplayError: public Command {

	/* Only Store can call private constructor */
	friend class Store;

private:

	/* Line in file with error */
	const string line;

	/*
	* Constructs a DisplayError object with a given store and error line
	*/
	DisplayError(Store* store, const string& fileName, const string& line);

public:

	/*
	* Executes the command
	*/
	void execute() const override;

};
#endif  /* COMMAND_H */
