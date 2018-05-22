#ifndef POS_APP_H
#define POS_APP_H
#define _CRT_SECURE_NO_WARNINGS
// lib includes
#include <iomanip> 
#include <iostream>
#include <sstream>
#include <cstring>
#include <string>
#include <fstream>
#include "Date.h"
#include "Item.h"
#include "POS.h"
#include "PosIO.h"
#include "Error.h"
#include "NonPerishable.h"
#include "Perishable.h"
namespace ict {
	class PosApp {
	private:
		char m_filename[128];
		char m_billfname[128];
		Item* m_items[MAX_NO_ITEMS];
		int m_noOfItems;
		int menu();
		void deallocateItems();
		void loadRecs();
		void saveRecs();
		int searchItems(const char* sku)const;
		void updateQty();
		void addItem(bool isPerishable);
		void listItems()const;
		void truncateBillFile();
		void showBill();
		void addToBill(Item& I);
		void POS();
	public:
		PosApp(const char* filename, const char* billfname);
		void run();
		PosApp(PosApp &) = delete;
		PosApp& operator= (PosApp &) = delete;
	};
}
#endif