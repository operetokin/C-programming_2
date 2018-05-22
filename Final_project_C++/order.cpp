#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
#include "util.h"

class Order {
	string customer, product;
	vector<string> itemList;
public:
	Order() {};
	Order(vector<string> line)
	{
		if (line.size() < 3)
			throw string("expected at least 3 fields, found ") + to_string(line.size());

		if (validCustomerName(line[0]))
			customer = line[0];
		else
			throw string("customer name not understood -->") + line[0] + "<--";

		if (validProductName(line[1]))
			product = line[1];
		else
			throw string("product name not understood -->") + line[1] + "<--";

		for (size_t i = 2; i < line.size(); i++) {
			if (line[i].empty()) //skip null fields
				continue;

			if (validItemName(line[i]))
				itemList.push_back(line[i]);
			else
				throw string("item name not understood -->") + line[i] + "<--";
		}
	}

	void print()
	{
		cout << "|customer|product|item 1|item 2|...| = "
			<< "|" << customer
			<< "|" << product;
		for (auto& item : itemList)
			cout << "|" << item;
		cout << "|\n";
	}

	void graph(fstream& gv) {
		for (auto& item : itemList)
			gv << '"' << customer << "\n" << product << '"'
			<< "->"
			<< '"' << item << '"'
			<< "[color=blue];\n";
	}
};	// Order

class OrderManager {
	vector<Order> orderList;
public:
	OrderManager() {}
	OrderManager(vector< vector<string> > & csvOrderData) {
		for (auto& line : csvOrderData) {
			try {
				orderList.push_back(Order(line));
			}
			catch (const string& e) {
				cerr << "Problem: " << e << "\n";
			}
		}
	}

	void print() {
		for (auto& order : orderList)
			order.print();
	}

	void graph(string& filename) {
		fstream gv(filename + ".gv", ios::out | ios::trunc);
		if (gv.is_open()) {
			gv << "digraph orderGraph {\n";

			for (auto& order : orderList)
				order.graph(gv);

			gv << "}\n";
			gv.close();

			string cmd = "\"C:\\Program Files (x86)\\Graphviz2.38\\bin\\dot.exe\" -Tpng " + filename + ".gv" + " > " + filename + ".gv.png";
			cout << cmd << "\n";

			system(cmd.c_str());

			//vector<string>dotLocations{
			//	"/usr/bin/dot",                                       // default UNIX
			//	"/usr/local/bin/dot",                                 // sometimes a UNIX package is installed in /usr/local
			//	"C:\\Program Files (x86)\\Graphviz2.38\bin\\dot.exe" // a known DOS location for graphviz 2.38 (current package as of Nov 25, 2017)
			//};

			//string dot;
			//for (auto& e : dotLocations) {
			//	auto fileexist = [](string file) {fstream f(file, ios::in); return f.is_open();};
			//	if (fileexist(e)) {
			//		dot = move(e);
			//		break;
			//	}
			//}

			//if (dot.empty()) {
			//	cerr << R"foo(Graphviz program "dot" not found! Package "graphviz" is not instaled.)foo";
			//}
			//else {
			//	string cmd = dot;
			//	cmd += " -Tpng -O " + filename + ".gv";  //-O flag - automatically generate the output file name with the proper suffix determinated by -T image type flag
			//	cout << "Running command -->" << cmd << "<--\n";
			//	int result = system(cmd.c_str());
			//	cout << "It returned '" << result << (result ? "' (command failed)\n" : "' (command passed)\n");
			//}
		}
	}

};
//
//int main(int argc, char* argv[]) {
//	if (argc != 3) {
//		cerr << "Usage: " << argv[0] << " order-csv-file order-csv-separator-char\n";
//		return 1;
//	}
//
//	string filename = argv[1];
//	char sep = argv[2][0];
//	vector< vector<string> >csvOrderData;
//
//	try {
//		csvRead(filename, sep, csvOrderData);
//		csvPrint(csvOrderData);
//
//		OrderManager om(csvOrderData);
//		om.print();
//		om.graph(filename);
//	}
//	catch (const string& e) {
//		cerr << "It threw! - " << e << "\n";
//	}
//
//	system("pause");
//}