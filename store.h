/*
* store.h
*
* @authors Juan Arias & Nick Tibbot
*
*/

#ifndef STORE_H
#define STORE_H

#include <queue>
#include <sstream>
#include <fstream>
#include "customer.h"
#include "hashtable.h"
#include "department.h"
#include "transaction.h"

using namespace std;

/*
* Interface for client to process all Store related info from text files
*
* Once all files have been read through the public interface, the client can
* call processCommands() to simulate all information from the files
*
* If the client doesnt call processCommands(), the Store will automatically
* process them at destruction
*
* 
*/
class Store {

	/* Only built in Commands can call a set of private methods */
	friend class AddCustomer;
	friend class RemoveCustomer;
	friend class AddItem;

private:
	
	/*
	* Static function to get next available ID number
	*/
	static long nextID();
	
	/* Unique ID for each Store */
	const long ID;
	
	/* Name of Store */
	const string name;
	
	/* Map each Department according to ItemType */
	map<const ItemType*, Department*> departmentMap;
	
	/* HashTable of Customers for constant retrieval */
	HashTable<Customer*> customerTable;
	
	/* Queue to process each command in order */
	queue<Command*> commandQ;
	
	/* Queue to display each error in order */
	queue<Command*> errorQ;

	/* Queue to deallocate any additional memory */
	queue<Command*> deallocationQ;
	
	/*
	* Deallocates all dynamic memory in Departments
	*/
	void clearDepartments();

	/*
	* Returns true if customerID in customerTable, else false
	*/
	bool isCustomer(long customerID) const;
	
	
	/*
	* Processes an AddCustomer Command with the given customerID & name
	*/
	void addCustomer(long customerID, const string& name);

	/*
	* Processes an AddItem Command stored in a line of string for
	* a given ItemType & Media type
	*/
	void addItem(const ItemType* itemType, const Media* media,
		         const string& fileName, const string& line);

	/*
*	 Removes Customer from customerTable
	*/
	void removeCustomer(long customerID);

	/*
	* Proccess all Commands in a given queue
	*/
	static void processQ(queue<Command*>* q);

public:

	/*
	* Processes a BorrowItem Command stored in a line of string
	* for a given ItemType
	*/
	void lendItem(const ItemType* itemType, const string& fileName,
		          const string& line);

	/*
	* Processes a ReturnItem Command stored in a line of string
	* for a given ItemType
	*/
	void returnItem(const ItemType* itemType, const string& fileName,
					const string& line);

	/*
	* Processes a DisplayHistory Command for a Customer
	* with the given customerID
	*/
	void displayHistory(const string& fileName, long customerID);

	/*
	* Processes a DisplayInventory Command
	*/
	void displayInventory() const;

	/*
	* Processes a DisplayError Command for a given line of string in a file
	*/
	void displayError(const string& fileName, const string& line) const;

	/*
	* Static function to convert a string to a vector of strings 
	* with a delimeter (default is comma)
	*/
	static vector<string>* toTokens(const string &line, char delimiter = ',');

	/*
	 * Static function to trim a string of whitespace
	 */
	static string trim(const string& str);
	
	/*
	* Constructs store with a given name
	*/
	explicit Store(const string& name);
	
	/*
	* Destructor to deallocate all dynamic memory
	*/
	virtual ~Store();

	/*
	* Return name of Store
	*/
	const string& getName() const;
	
	/*
	* Reads a file with the given name and creates Commands for
	* each Customer to add
	*/
	bool readCustomers(const string& fileName);
	
	/*
	* Reads a file with the given name & itemType and creates Commands
	* for each Item to add
	* Media type defaults to DVD
	*/
	bool readItems(const string& fileName, const string& itemType,
		           const string& mediaType = "D");
	
	/*
	* Reads a file with the given name & itemType and creates
	* Commands for each Transaction
	*/
	bool readTransactions(const string& fileName, const string& itemType);
	
	/*
	* Processes all Commands added from read files
	*/
	void processCommands();
	
};
#endif  /* STORE_H */
