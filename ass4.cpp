/*
* ass4.cpp
*
* @authors Juan Arias & Nick Tibbott
*
* Sample of how to run Store system
*/


#include "store.h"

/*
* Store reads each file and then processes all info
*/
void runStore() {
	Store store("Blockbuster");
	store.readCustomers("data4customers.txt");
	store.readItems("data4movies.txt", "Movie");
	store.readTransactions("data4commands.txt", "Movie");
	store.processCommands();
}

/*
* Begins running Store system
*/
int main() {
	runStore();
	return 0;
}