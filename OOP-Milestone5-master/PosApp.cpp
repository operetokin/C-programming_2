#define _CRT_SECURE_NO_WARNINGS
#include "PosApp.h"
	namespace ict{
	PosApp::PosApp(const char* filename, const char* billfname) {
		strcpy(m_filename, filename);
		strcpy(m_billfname, billfname);
		m_noOfItems = 0;
		loadRecs();
	}

	int PosApp::menu() {
		int n;
		std::cout << "The Sene-Store" << std::endl
			<< "1- List items" << std::endl
			<< "2- Add Perishable item" << std::endl
			<< "3 - Add Non - Perishable item" << std::endl
			<< "4 - Update item quantity" << std::endl
			<< "5 - Show Item" << std::endl
			<< "6 - POS" << std::endl
			<< "0 - exit program" << std::endl
			<< "> ";
		std::cin >> n;
		std::cout << std::endl;
		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(256, '\n');
			n = -1;
		}
		if (n != 0 && n != 1 && n != 2 && n != 3 && n != 4 && n != 5 && n != 6)
			n = -1;
		return n;
	}

	void PosApp::deallocateItems() {
		for (int i = 0; i < m_noOfItems; i++) {
			delete m_items[i];
		}
		m_noOfItems = 0;
	}

	void PosApp::loadRecs() {
		m_noOfItems = 0;
		char Id = '\0';
		deallocateItems();
		std::fstream myfile(m_filename);
		myfile.open(m_filename, std::ios::in); //?
		myfile.clear();
		if (!myfile.is_open()) {
				myfile.clear();
				myfile.close();
				myfile.open(m_filename, std::ios::out);
				myfile.close();
				return;
		}
		else  {
			//until reading fails loop:
			while (!myfile.eof() && myfile.good())
			{
				Id = myfile.get();
				if (Id == 'P') {
					m_items[m_noOfItems] = new Perishable;

				}
				else if (Id == 'N') {
					m_items[m_noOfItems] = new NonPerishable;

				}
				if (Id == 'P' || Id == 'N') {
					//std::fstream& load(std::fstream& myfile);
					myfile.ignore();
					m_items[m_noOfItems]->load(myfile);
					m_noOfItems++;
				}
			}
		}
		myfile.close();
	}
	
	void PosApp::saveRecs() {
		std::fstream myfile(m_filename);
		myfile.open(m_filename, std::ios::out);
		for (int i = 0; i < m_noOfItems; i++) {
			if(m_items[i]->quantity() > 0)
				m_items[i]->save(myfile);
		}
		myfile.close();
		loadRecs();
	}

	int PosApp::searchItems(const char* sku)const {
		int n = -1;
		for (int i = 0; i < m_noOfItems; i++) {
			if (strcmp(m_items[i]->sku(), sku) == 0) {
				n = i;
				break;
			}
		}
		return n;
	}

	void PosApp::updateQty() {
		//std::string str;
		char str[20] = {};
		int num;
		std::cout << "Please enter the SKU: ";
		std::cin >> str;
		if (searchItems(str) == -1)
			std::cout << "Not found!" <<std::endl;
		else
		{
			m_items[searchItems(str)]->write(std::cout, false);
			std::cout << "Please enter the number of purchased items: ";
			std::cin >> num;
			*m_items[searchItems(str)] += num;
			saveRecs();
			std::cout << "Updated!" << std::endl <<std::endl;
		} 
	}

	void PosApp::addItem(bool isPerishable) {
		if (isPerishable) {
			m_items[m_noOfItems] = new Perishable;
		}
		else {
			m_items[m_noOfItems] = new NonPerishable;
		}
		std::cin >> *m_items[m_noOfItems];
		if (std::cin.fail()) {
			std::cout << *m_items[m_noOfItems];
		}
		else {
			//m_items[m_noOfItems] = I;
			m_noOfItems++;
			std::cout << "Item Added." << std::endl << std::endl;
		}
	}

	void PosApp::listItems()const {
		double total = 0;
		std::cout << " Row | SKU    | Item Name          | Price |TX |Qty |   Total |" << std::endl;
		std::cout << "-----|--------|--------------------|-------|---|----|---------|";
		for (int i = 0; i < m_noOfItems; i++) {
			std::cout << std::endl << std::setw(4) << std::right << i+1 << " | ";
			m_items[i]->write(std::cout, true);
			total += m_items[i]->cost()* m_items[i]->quantity();
		}
		std::cout <<std::endl<< "-----^--------^--------------------^-------^---^----^---------^" << std::endl;
		std::cout << std::setw(45) << "Total Asset $" << "  |" << std::setw(14) << total << std::endl;
		std::cout << "-----------------------------------------------^--------------^" << std::endl << std::endl;
	}

	void PosApp::truncateBillFile() {
		std::fstream myfile(m_billfname);
		myfile.open(m_billfname, std::ios::out, std::ios::trunc);
		myfile.close();
	}

	void PosApp::showBill() {
		Date d;
		double total = 0;
		char Id;
		Item *I;
		std::fstream myfile(m_billfname);
		myfile.open(m_billfname, std::ios::in);
		std::cout << "v--------------------------------------------------------v" << std::endl;
		std::cout << "| " << d << std::setw(39) << std::right << '|' << std::endl;
			while (!myfile.eof())
			{
				myfile.get(Id);
				if (Id == 'P') {
					I = new Perishable;

				}
				else if (Id == 'N') {
					I = new NonPerishable;

				}
				myfile.ignore();
				I->load(myfile);
				I->write(std::cout, true);
				delete I;
			}

		myfile.close();
		truncateBillFile();
	}

	void PosApp::addToBill(Item& I) {
		int temp = 0;
		std::fstream myfile(m_billfname);
		myfile.open(m_billfname, std::ios::out, std::ios::app);
		temp = I.quantity();
		I.quantity(1);
		I.save(myfile);
		I.quantity(temp - 1);
		saveRecs();
	}

	void PosApp::POS() {
		char SKU[MAX_SKU_LEN] = "";
		std::cin.ignore();
		while (true)
		{
			std::cout << "Sku: ";
			std::cin.getline(SKU, 256, '\n');
			if (SKU[0] == '\0') {
				showBill();
				break;
			}
			else {
				if (searchItems(SKU) == -1)
					std::cout << "Not found!" << std::endl;
				else
				{
					std::cout << "v------------------->" << std::endl;
					std::cout << "| " << m_items[searchItems(SKU)]->name() << std::endl;
					std::cout << "^------------------->" << std::endl;
					addToBill(*m_items[searchItems(SKU)]);
				}
			}
		}
	}

	void PosApp::run(){
		char sku_n[MAX_SKU_LEN];
		int n = -1;
		int i = -100;
		while (i != 0) {
			i = menu();
			switch (i) {
			case 1: listItems();
				break;
			case 2: addItem(true);
				break;
			case 3: addItem(false);
				break;
			case 4: updateQty();
				break;
			case 5: std::cout << "Please enter the SKU: ";
				std::cin >> sku_n;
				n = searchItems(sku_n);
				if (n != -1) {
					m_items[n]->write(std::cout, false);
					std::cout << std::endl;
				}
				else std::cout << "Not found!" << std::endl;
				break;
			case 6: POS();
				break;
			case 0: std::cout << "Goodbye!";
				break;
				
			default: std::cout << "===Invalid Selection, try again===";
			}
		}
	}
}
/*
ouputs:
-------------------------------------
update:
Please enter the SKU: 1313
Name:
Paper Tissue
Sku: 1313
Price: 1.22
Price after tax: 1.38
Quantity: 194
Total Cost: 267.45

Please enter the number of purchased items: 12
Updated!

------------------------------
Please enter the SKU: 3434
Not found!

-------------------------------------
add item:
Perishable Item Entry:
Sku: 5656
Name:
Honey
Price: 12.99
Taxed: y
Quantity: 12
Expiry date (YYYY/MM/DD): 1200/10/12
Invalid Year in Date Entry

Perishable Item Entry:
Sku: 5656
Name:
Honey
Price: 12.99
Taxed: y
Quantity: 12
Expiry date (YYYY/MM/DD): 2017/5/15
Item added.

--------------------------------------------
list item:
 Row | SKU    | Item Name          | Price |TX |Qty |   Total |
-----|--------|--------------------|-------|---|----|---------|
   1 | 1234   |Milk                |   3.99|  P|   2|     7.98|
   2 | 3456   |Paper Cups          |   5.99| TN|  38|   257.21|
   3 | 4567   |Butter              |   4.56| TP|   9|    46.38|
   4 | 1212   |Salted Butter       |   5.99|  P| 111|   664.89|
   5 | 1313   |Paper Tissue        |   1.22| TN| 206|   283.99|
   6 | 5656   |Honey               |  12.99| TP|  12|   176.14|
-----^--------^--------------------^-------^---^----^---------^
                               Total Asset: $  |       1436.59|
-----------------------------------------------^--------------^


--------------------------------------
printbill:
v--------------------------------------------------------v
| 2017/04/02, 12:42                                      |
| SKU    | Item Name          | Price |TX |Qty |   Total |
|--------|--------------------|-------|---|----|---------|
| 1212   |Salted Butter       |   5.99|  P|   1|     5.99|
| 1313   |Paper Tissue        |   1.22| TN|   1|     1.38|
| 5656   |Honey               |  12.99| TP|   1|    14.68|
^--------^--------------------^-------^---^----^---------^
|                               Total: $  |         22.05|
^-----------------------------------------^--------------^

-------------------------------------------------------
POS:
Sku: 1212
v------------------->
| Salted Butter
^------------------->
Sku: 1212
v------------------->
| Salted Butter
^------------------->
Sku: 1313
v------------------->
| Paper Tissue
^------------------->
Sku: 1234
v------------------->
| Milk
^------------------->
Sku: 7654
Not found!
Sku: 5656
v------------------->
| Honey
^------------------->
Sku:
v--------------------------------------------------------v
| 2017/04/02, 12:58                                      |
| SKU    | Item Name          | Price |TX |Qty |   Total |
|--------|--------------------|-------|---|----|---------|
| 1212   |Salted Butter       |   5.99|  P|   1|     5.99|
| 1212   |Salted Butter       |   5.99|  P|   1|     5.99|
| 1313   |Paper Tissue        |   1.22| TN|   1|     1.38|
| 1234   |Milk                |   3.99|  P|   1|     3.99|
| 5656   |Honey               |  12.99| TP|   1|    14.68|
^--------^--------------------^-------^---^----^---------^
|                               Total: $  |         32.03|
^-----------------------------------------^--------------^

------------------------------------------------------
run:
The Sene-Store
1- List items
2- Add Perishable item
3- Add Non-Perishable item
4- Update item quantity
5- Show Item
6- POS
0- exit program
> 5

Please enter the SKU: 5656
v-----------------------------------v
Name:
Honey
Sku: 5656
Price: 12.99
Price after tax: 14.68
Quantity: 10
Total Cost: 146.79
Expiry date: 2017/05/15
^-----------------------------------^

The Sene-Store
1- List items
2- Add Perishable item
3- Add Non-Perishable item
4- Update item quantity
5- Show Item
6- POS
0- exit program
> 5

Please enter the SKU: 12345
Not found!

The Sene-Store
1- List items
2- Add Perishable item
3- Add Non-Perishable item
4- Update item quantity
5- Show Item
6- POS
0- exit program
> five

===Invalid Selection, try again===

The Sene-Store
1- List items
2- Add Perishable item
3- Add Non-Perishable item
4- Update item quantity
5- Show Item
6- POS
0- exit program
> 0

Goodbye!

*/