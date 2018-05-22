#ifndef ICT_PERISHABLE_H__
#define ICT_PERISHABLE_H__
#include <iostream>
#include <iomanip> 
#include <cstring>
#include <string>
#include <fstream>
#include "Date.h"
#include "Item.h"
#include "POS.h"
#include "PosIO.h"
#include "NonPerishable.h"
namespace ict {
	class Perishable : public NonPerishable {
	private:
		Date m_expiry;
	protected:
		char signature() const;
	public:
		Perishable();
		std::fstream& save(std::fstream& file)const;
		std::fstream& load(std::fstream& file);
		std::ostream& write(std::ostream& os, bool linear)const;
		std::istream& read(std::istream& istr);
	};
}






#endif
