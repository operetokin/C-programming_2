#ifndef ICT_ITEM_H__
#define ICT_ITEM_H__

// inlcude PosIO and POS header files
#include "PosIO.h"
#include "POS.h"
#include <fstream>
#include <iostream>

namespace ict {
	class Item : public PosIO {
	private:
		/*m_sku:  C - style null - terminated character array, MAX_SKU_LEN + 1 characters long
		This character array holds the SKU(barcode) of the items as a string.*/
		char m_sku[MAX_SKU_LEN + 1];
		/* : Character pointer*/
		/*This character pointer points to a dynamically allocated string that holds the Item’s name*/
		char *m_name;
		/*m_price : Double
		This variable holds the Item’s Price*/
		double m_price;
		/*m_taxed : Boolean
		This variable is true if this item is taxed, false otherwise*/
		bool m_taxed;
		/*m_quantity : Integer
		This variable holds the Item’s on - hand(current) quantity.*/
		int m_quantity;
	public:
		Item();
		Item(const char sku[MAX_SKU_LEN],const char *Name, double price, bool tax=true);
		Item(const Item &other);
		Item& operator=(const Item& other);

		void sku(const char sku[]);
		void price(double price);
		void name(const char *name);
		void taxed(bool tax);
		void quantity(int quantity);

		const char* sku()const;
		double price()const;
		const char* name()const;
		bool taxed()const;
		int quantity()const;
		double cost()const;
		bool isEmpty()const;
		virtual ~Item();
		bool operator==(const char*) const;
		int operator+=(int quantity);
		int operator-=(int quantity);
		/*std::fstream& save(std::fstream& file)const;
		std::fstream& load(std::fstream& file);
		std::ostream& write(std::ostream& os, bool linear)const;
		std::istream& read(std::istream& is);*/
		virtual std::fstream& save(std::fstream& file)const = 0;
		virtual std::fstream& load(std::fstream& file) = 0;
		virtual std::ostream& write(std::ostream& os, bool linear)const = 0;
		virtual std::istream& read(std::istream& is) = 0;
	// end class Item
};
  // operator += 
  double operator+=(double& d, const Item& I);
  // operator << and operator >>
  std::ostream& operator<<(std::ostream& ostream, const Item &I);
  std::istream& operator>> (std::istream& istream, Item &I);
}


#endif