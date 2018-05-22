#ifndef ICT_NONPERISHABLE_H__
#define ICT_NONPERISHABLE_H__
#include <iostream>
#include <fstream>
#include "Date.h"
#include "Item.h"
#include "POS.h"
#include "PosIO.h"
#include <cstring>
namespace ict{
	class NonPerishable : public Item {
	private:
		char *m_err;
	protected:
		bool ok() const;
		void error(const char* message);
		virtual char signature() const;
	public:
		std::fstream& save(std::fstream& file)const;
		std::fstream& load(std::fstream& file);
		std::ostream& write(std::ostream& ostr, bool linear)const;
		std::istream& read(std::istream& is);
		virtual ~NonPerishable();
	};
}








#endif