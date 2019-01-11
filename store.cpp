/*
* store.cpp
*
* @authors Juan Arias & Nick Tibbot
*
* Implemntations for Store class
*
*/

#include "store.h"

/*
* Static function to get next available ID number
*/
long Store::nextID() {
	static int next = 0;
	return next++;
}


/*
* Deallocates all dynamic memory in Departments
*/
void Store::clearDepartments() {
	for (auto& pair : this->departmentMap) {
		delete pair.second;
	}
}

/*
* Processes a BorrowItem Command stored in a line of string for a given ItemType
*/
void Store::lendItem(const ItemType* itemType, const string& fileName,
	                 const string& line) {
	const long customerID(stol(line.substr(2, 4)));
	const Media* media = Media::getMedia(line.substr(7, 1));
	Department* dept = departmentMap.at(itemType);
	const Item* item = media ? dept->getItem(media, line.substr(9)) : nullptr;
	if (isCustomer(customerID) && item && dept->lendItem(media, item)) {
		Customer* cust = customerTable.get(customerID);
		cust->borrowItem(item);
		cust->addTransaction(line);
	} else {
		errorQ.push(new DisplayError(this, fileName, line));
	}

}

/*
* Processes a ReturnItem Command stored in a line of string for a given ItemType
*/
void Store::returnItem(const ItemType* itemType, const string& fileName,
	                   const string& line) {
	const long customerID(stol(line.substr(2, 4)));
	const Media* media = Media::getMedia(line.substr(7, 1));
	Department* dept = departmentMap.at(itemType);
	const Item* item = media ? dept->getItem(media, line.substr(9)) : nullptr;
	if (isCustomer(customerID) && item && dept->returnItem(media, item)) {
		Customer* cust = customerTable.get(customerID);
		cust->returnItem(item);
		cust->addTransaction(line);
	} else {
		errorQ.push(new DisplayError(this, fileName, line));
	}
}

/*
* Processes an AddCustomer Command with the given customerID & name
*/
void Store::addCustomer(long customerID, const string& name) {
	customerTable.add(customerID, new Customer(customerID, name));
}

/*
* Processes an AddItem Command stored in a line of string for 
* given ItemType & Media type
*/
void Store::addItem(const ItemType* itemType, const Media* media,
	                const string& fileName, const string& line) {
	vector<string>* tokens = Store::toTokens(line);
	int stockAmount(stoi(tokens->at(1)));
	tokens->erase(tokens->begin()+1, tokens->begin()+2);
	Item* item = itemType->create(*tokens);
	delete tokens;
	if (item) {
		if (!departmentMap.count(itemType)){
			departmentMap.emplace(itemType, new Department());
		}
		departmentMap.at(itemType)->addItem(media, item, stockAmount);
	} else {
		errorQ.push(new DisplayError(this, fileName, line));
	}
}

/*
* Processes a DisplayHistory Command for a Customer with the given customerID
*/
void Store::displayHistory(const string& fileName, long customerID) {
	if (isCustomer(customerID)) {
		const Customer* cust = customerTable.get(customerID);
		cust->displayHistory();
	} else {
		stringstream ss;
		ss << "H " << to_string(customerID);
		errorQ.push(new DisplayError(this, fileName, ss.str()));
	}
}

/*
* Processes a DisplayInventory Command
*/
void Store::displayInventory() const {
	for (const auto& pair : departmentMap) {
		cout << *pair.first << " inventory:\n" << *pair.second;
	}
}

/*
* Processes a DisplayError Command for a given line of string
*/
void Store::displayError(const string& fileName, const string &line) const {
    cout << "ERROR in " << fileName << ": \"" << line << "\"\n\n";
}

/*
* Returns true if customerID in customerTable, else false
*/
bool Store::isCustomer(long customerID) const {
	return customerTable.has(customerID);
}


/*
* Removes Customer from customerTable
*/
void Store::removeCustomer(long customerID) {
	delete customerTable.get(customerID);
}

/*
* Proccess all Commands in a given queue
*/
void Store::processQ(queue<Command*>* q) {
	while (!q->empty()) {
		q->front()->execute();
		delete q->front();
		q->pop();
	}
}

/*
* Return name of Store
*/
const string& Store::getName() const {
    return this->name;
}

/*
* Processes all Commands added from read files
*/
void Store::processCommands() {
	processQ(&commandQ);
	processQ(&errorQ);
}

/*
* Static function to convert a string to a vector of strings
* with a delimeter (default is comma)
*/
vector<string>* Store::toTokens(const string &line, char delimiter) {
    vector<string>* tokens = new vector<string>;
    // current position in the line
    size_t pos = 0;
    // copy of line since we need to modify it
    string lineCopy = line;
    // current token in the line
    string token;
    // find position of next delimiter
    while ((pos = lineCopy.find(delimiter)) != string::npos) {
        token = lineCopy.substr(0, pos);
        token = Store::trim(token);
        tokens->push_back(token);
        lineCopy.erase(0, pos + 1);
    }
    token = lineCopy;
    token = Store::trim(token);
    tokens->push_back(token);
    return tokens;
}

/*
 * Static function to trim a string of whitespace
 */
string Store::trim(const string &str) {
    size_t first = str.find_first_not_of(' ');
    if (string::npos == first) {
        return str;
    }
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

/*
* Constructs store with a given name
*/
Store::Store(const string& name) :ID(Store::nextID()), name(name) {
}

/*
* Destructor to deallocate all dynamic memory
*/
Store::~Store() {
	processCommands();
	processQ(&deallocationQ);
	clearDepartments();
}

/*
* Reads a file with the given name and creates Commands for each Customer to add
*/
bool Store::readCustomers(const string &fileName) {
    ifstream infile(fileName);
	if (!infile.is_open()) {
		return false;
	}
	string line;
	while (getline(infile, line)) {
		const long customerID = stol(line.substr(0, 4));
		commandQ.push(new AddCustomer(this, customerID, line.substr(5)));
		deallocationQ.push(new RemoveCustomer(this, customerID));
	}
    return true;
}

/*
* Reads a file with the given name & itemType and creates Commands
* for each Item to add
* Media type defaults to DVD
*/
bool Store::readItems(const string& fileName, const string& itemType,
	                  const string& mediaType) {
	ifstream infile(fileName);
	if (!infile.is_open()) {
		return false;
	}
	const ItemType* itemTypePtr = ItemType::getItemType(itemType);
	string line;
	while (getline(infile, line)) {
		const Media* media = Media::getMedia(mediaType);
		if (itemTypePtr && media) {
			commandQ.push(new AddItem(this, itemTypePtr, media, fileName,line));
		} else {
			errorQ.push(new DisplayError(this, fileName, line));
		}
	}
	return true;
}

/*
* Reads a file with the given name & itemType and
* creates Commands for each Transaction
*/
bool Store::readTransactions(const string& fileName, const string& itemType) {
	ifstream infile(fileName);
	if (!infile.is_open()) {
		return false;
	}
	const ItemType* itemTypePtr = ItemType::getItemType(itemType);
	string line;
	while (getline(infile, line)) {
		char type = line[0];
		Transaction* trans = Transaction::create(this, itemTypePtr, fileName,
			                                     type, line);
		if (itemTypePtr && trans) {
			commandQ.push(trans);
		} else {
			errorQ.push(new DisplayError(this, fileName, line));
			delete trans;
		}
	}
	return true;
}