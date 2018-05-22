#define _CRT_SECURE_NO_WARNINGS
// lib includes
#include "Date.h"
#include "Item.h"
#include "POS.h"
#include "PosIO.h"
#include "Perishable.h"
namespace ict {

	char Perishable::signature() const {
		char P = 'P';
		return P;
		}
	Perishable::Perishable() {
		m_expiry.dateOnly(true);
	}
	std::fstream& Perishable::save(std::fstream& file)const {
		if (file.is_open()) {
			NonPerishable::save(file);
			file << ',' << m_expiry;
			//file << signature() << "," << sku() << "," << name() << "," << price() << "," << taxed() << quantity() << ',' << m_expiry << std::endl;
		}
		else
			std::cout << "File is not open!" << std::endl;
		return file;
	}

	std::fstream& Perishable::load(std::fstream& file) {
		NonPerishable::load(file);
		file.ignore();
		file >> m_expiry;
		return file;
	}

	std::ostream& Perishable::write(std::ostream& os, bool linear)const {
		NonPerishable::write(os, linear);
		if (ok() && linear == false)
			os << "Expiry date: " << m_expiry << std::endl;

		return os;
	}

	std::istream& Perishable::read(std::istream& istr) {
		std::cout << "Perishable ";
		NonPerishable::read(istr);
		if (istr.fail()) {
			return istr;
		}
		std::cout << "Expiry date (YYYY/MM/DD): ";
		istr >> m_expiry;
		if (m_expiry.errCode() == CIN_FAILED) {
			error("Invalid Date Entry");
			istr.setstate(std::ios::failbit);
		}
		else if (m_expiry.errCode() == YEAR_ERROR) {
			error("Invalid Year in Date Entry");
			istr.setstate(std::ios::failbit);
		}
		else if (m_expiry.errCode() == MON_ERROR) {
			error("Invalid Month in Date Entry");
			istr.setstate(std::ios::failbit);
		}
		else if (m_expiry.errCode() == DAY_ERROR) {
			error("Invalid Day in Date Entry");
			istr.setstate(std::ios::failbit);
		}

		return istr;
	}

}
