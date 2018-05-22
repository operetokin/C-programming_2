#define _CRT_SECURE_NO_WARNINGS  
// Lib includes
#include <iostream>
#include <cstring>
#include "PosIO.h"
#include <fstream>
// inlcude Item and POS header files
#include "POS.h"
#include "Item.h"
using namespace std;
namespace ict{
  // class Item implementaion
		Item::Item() {
			m_price = 0;
			m_quantity = 0;
			m_name = nullptr;
		}

		Item::Item(const char sku[MAX_SKU_LEN],const char *Name, double price, bool tax) {
			strcpy(m_sku, sku);
			//m_sku[strlen(sku) + 1] = '\0';
			m_name = new char[strlen(Name) + 1];
			strcpy(m_name, Name);
			//m_name[strlen(Name)] = '\0';
			m_quantity = 0;
			m_price = price;
			m_taxed = tax;
		}
		//copy constructor and operator=
		Item::Item(const Item& other) {
			strcpy(m_sku, other.m_sku);
			//m_sku[strlen(other.m_sku) + 1] = '\0';
			m_name = new char[strlen(other.m_name) + 1];
			strcpy(m_name, other.m_name);
			//m_name[strlen(other.m_name)] = '\0';
			m_quantity = other.m_quantity;
			m_price = other.m_price;
			m_taxed = other.m_taxed;
		}

		Item& Item::operator=(const Item& other) {
			if (!other.m_price == 0 && !other.m_quantity == 0) {
				strcpy(m_sku, other.m_sku);
				//m_sku[strlen(other.m_sku) + 1] = '\0';
				m_name = new char[strlen(other.m_name) + 1];
				strcpy(m_name, other.m_name);
				//m_name[strlen(other.m_name)] = '\0';
				m_quantity = other.m_quantity;
				m_price = other.m_price;
				m_taxed = other.m_taxed;
			}
			return *this;
		}

		Item::~Item()  {
			delete[] m_name;
		}
		/*Implement the copy constructor and the operator= 
		so that the Item referenced in the parameter is copied from and assigned 
		to another Item safely and without any memory leak.
		Also, implement a virtual destructor to ensure that
		any memory allocated for m_name is freed when the Item is destroyed.
			
			In operator=, if the current object is being set to another Item 
			that is in a safe empty state, the copy assignment operation is to be ignored.
*/
		void Item::sku(const char sku[]) {
			strcpy(m_sku, sku);
		}
		void Item::price(double price) {
			m_price = price;
		}
		void Item::name(const char *name) {
			m_name = new char[strlen(name)+1];
			strcpy(m_name, name);
		}
		void Item::taxed(bool tax) {
			m_taxed = tax;
		}
		void Item::quantity(int quantity) {
			m_quantity = quantity;
		}

		const char* Item::sku() const{
			return m_sku;
		}
		double Item::price() const{
			return m_price;
		}
		const char* Item::name() const{
			return m_name;
		}
		bool Item::taxed() const{
			return m_taxed;
		}
		int Item::quantity() const{
			return m_quantity;
		}

		double Item::cost() const{
			double costs = m_price;
			if (m_taxed == true)
				costs = m_price * (1 + TAX);
			return costs;
		}

		bool Item::isEmpty() const{
			return (m_price == 0 && m_quantity == 0);
		}

		//operator==: receives the address of an unmodifiable character string and returns a bool. 
		/*This operator compares the character string at the received address to the Item’s SKU,
			if they are the same, it will return true;
		otherwise false.Note that this operator cannot modify the owner.*/
		bool Item::operator==(const char* s2) const
		{
			return !strcmp(m_sku, s2);
		}
		//operetor+= : receives an integer and returns an integer. 
		//	This operator adds the received value to the Item’s quantity on hand and returns the sum.
		int Item::operator+=(int quantity) { 
			m_quantity += quantity;
			return m_quantity;
		}

		//operator-= : receives an integer and returns an integer. 
		//	This operator reduces the Item’s quantity on hand by the received value 
		//	and returns the quantity on hand after reduction.
		int Item::operator-=(int quantity) {
			m_quantity -= quantity;
			return m_quantity;
		}



		//non-member operator +=
		/*receives a modifiable reference to a double as the left operand
			and an unmodifiable reference to an Item as the right operand and returns a double value.
			This operator multiplies the cost of the Item by the quantity of the Item
			and then adds that value to the left operand and returns the result.
			Essentially, this operator adds the total cost of the referenced Item 
			to the left operand and then returns it.*/
		// 
		double operator+=(double& d, const Item& I) {
			d += (I.cost()) * (I.quantity());
			return d;
		}
		// operator << and operator >>


		std::ostream& operator<<(std::ostream& ostream, const Item &I)
		{
			I.write(ostream, true);
			return ostream;
		}

		std::istream& operator >> (std::istream& istream, Item &I)
		{
			I.read(istream);
			
			return istream;
		}
}