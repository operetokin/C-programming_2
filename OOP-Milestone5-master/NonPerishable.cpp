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
#include "NonPerishable.h"
namespace ict {
	bool NonPerishable::ok() const {
		if (m_err == nullptr)
			return (true);
		if (m_err[0] == '\0')
			return (true);
		return false;
	}

	void NonPerishable::error(const char* message) {
		m_err = new char[strlen(message) + 1];
		strcpy(m_err, message);
	}

	NonPerishable::~NonPerishable(){
		//delete[] m_err;
	}
	 char NonPerishable::signature() const {
		 char n = 'N';
		 return n;
	}


	std::fstream& NonPerishable::save(std::fstream& file) const{
		if (file.is_open()) {
			file << signature() << "," << sku() << "," << name() << "," << price() << "," << taxed() << "," << quantity();
		}
		else
			std::cout << "File is not open!" << std::endl;
		return file;
	}

	std::fstream& NonPerishable::load(std::fstream& file) {
		error("");
		int i = 0;
		double d = 0;
		bool b = true;
		// str[MAX_SKU_LEN];
		std::string str2;
		std::string str1;
		//str[0] = '\0';
		if (file.is_open()) {
			//file.ignore(2, ',');
			//file.getline(str, 5, ',');
			std::getline(file, str1, ',');
			sku(str1.c_str());
			//sku(str);
			//file.ignore();
			std::getline(file, str2, ',');
			name(str2.c_str());
			file >> d;
			price(d);
			file.ignore();
			file >> b;
			taxed(b);
			file.ignore();
			file >> i;
			quantity(i);
		}
		else
			std::cout << "file is not open" << std::endl;
		return file;
	}

	std::ostream& NonPerishable::write(std::ostream& ostr, bool linear) const {
		char T = ' ';
		if (taxed() == true) T = 'T';
		if (!ok()) {
			ostr << m_err;
		}
		else
		{
			if (linear == true) {
				ostr << std::setw(7) << std::left << sku() << '|' << std::setw(20) << std::left << name() << '|' << std::setw(7) << std::right << price() <<
					'|' << ' ' << T << signature() << '|' << std::setw(4) << quantity() <<
					'|' << std::setw(3) << " ";
				ostr << std::fixed << std::setprecision(2)<< std::setw(6) << cost()*quantity() << '|';
			}
			else if (linear == false) {
				if (taxed() == true)
					ostr << "Name:" << std::endl << name() << std::endl << "Sku: " << sku() << 
					std::endl << "Price: " << price() << std::endl << "Price after tax: " << 
					std::fixed << std::setprecision(2) << cost() << std::endl <<
					"Quantity: " << quantity() << std::endl << "Total Cost: " <<
					std::fixed << std::setprecision(2) << cost()*quantity() << std::endl;
				if (taxed() == false)
					ostr << "Name:" << std::endl << name() << std::endl << "Sku: " << sku() << 
					std::endl << "Price: " << price() << std::endl << "Price after tax: " << "N/A" <<
					std::endl << "Quantity: " << quantity() << std::endl << "Total Cost: " <<
					std::fixed << std::setprecision(2) << cost()*quantity() << std::endl;
			}
		}
		return ostr;
	}

	std::istream& NonPerishable::read(std::istream& is) {
		error("\0");
		int Num = 0;
		double Price = 0;
		char ch = '\0';
		char str[20] = {};
		std::cout << "Item Entry:" << std::endl;
		std::cout << "Sku: ";
		is >> str;
		sku(str);
		//
		std::cout << "Name:"  << std::endl;
		is >> str;
		name(str);

		std::cout << "Price: ";
		is >> Price;
		if (is.fail()) {
			error("Invalid Price Entry");
			return is;
		}
		else 
			price(Price);

		std::cout << "Taxed: ";
		is >> ch;
		if (ch == 'y' || ch == 'Y')
			taxed(true);
		else if (ch == 'n' || ch == 'N')
			taxed(false);
		else {
			error("Invalid Taxed Entry, (y)es or (n)o");
			is.setstate(std::ios::failbit);
			return is;
		}
			
		std::cout << "Quantity: ";
		is >> Num;
		if (is.fail()) {
			error("Invalid Quantity Entry");
			return is;
		}
		else
			quantity(Num);
		return is;
	}

}









