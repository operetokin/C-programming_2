
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include "util.h"
using namespace std;

class Item {
	string name, installer, remover, sequenceNumber, description;
public:
	Item() {}
	Item(vector<string>& line) {
		switch (line.size()) {
		case 5:
			description = line[4];
			[[fallthrough]]

		case 4:
			if (validSequenceNumber(line[3]))
				sequenceNumber = line[3];
			else
				throw string("sequence number not understood ==>") + line[3] + "<==";
			
			if (validTaskName(line[2]))
				remover = line[2];
			else
			throw string("remover task name not understood ==>") + line[2] + "<==";
			
			if (validTaskName(line[1]))
				installer = line[1];
			else
				throw string("installer task name not understood ==>") + line[1] + "<==";
			
			if (validItemName(line[0]))
				name = line[0];
			else 
				throw string("item name not understood ==>") + line[0] + "<==";

			break;

		default:
			throw string("expected 4 or 5 fields, found ") + to_string(line.size());
		}
	
	}

	void print() {
		cout << "|name|installer|remover|sequenceNumber|description| = "
			<< "|" << name
			<< "|" << installer
			<< "|" << remover
			<< "|" << sequenceNumber
			<< "|" << description
			<< "|\n";
	}

	void graph(fstream& gv) {

		gv << '"' << "ITEM\n" << name << '"'
			<< "->"
			<< '"' << "INSTALLER\n" << installer << '"'
			<< "[color=green];\n";

		gv << '"' << "ITEM\n" << name << '"'
			<< "->"
			<< '"' << "REMOVER\n" << remover << '"'
			<< "[color=red];\n";
	}
};

class ItemManager {
	vector<Item> itemList;
public:
	ItemManager(vector < vector<string> > & csvItemData) {
		for (auto& line : csvItemData) {
			try {
				itemList.push_back(Item(line));
			}
			catch (const string & e) {
				cerr << "Problem: " << e << "\n";
			}
		}
	}
	void print() {
		for (auto& item : itemList)
			item.print();
	}

	void graph(string& filename) {
		fstream gv(filename + ".gv", ios::out | ios::trunc);
		if (gv.is_open()) {
			gv << "digraph itemGraph {\n";

			for (auto& item: itemList)
				item.graph(gv);

			gv << "}\n";
			gv.close();

			string cmd = "\"C:\\Program Files (x86)\\Graphviz2.38\\bin\\dot.exe\" -Tpng " + filename + ".gv" + " > " + filename + ".gv.png";
			cout << cmd << "\n";

			system(cmd.c_str());

			/*vector<string> dotLocations{
				"/usr/bin/dot",                                       // default UNIX
				"/usr/local/bin/dot",                                 // sometimes a UNIX package is installed in /usr/local
				"C:/\"Program Files (x86)\"/Graphviz2.38/bin/dot.exe" // a known DOS location for graphviz 2.38 (current package as of Nov 25, 2017)
			};

			string dot;
			for (auto& e : dotLocations) {
				auto fileexist = [](string file) {fstream f(file, ios::in); return f.is_open();};
				if (fileexist(e)) {
					dot = move(e);
					break;
				}
			}

			if (dot.empty()) {
				cerr << R"foo(ERROR: Graphviz program "dot" not found!  Package "graphviz" is not installed.    )foo";
			}
			else {
				string cmd = dot;

				cmd += " -Tpng -O " + filename + ".gv"; // -O flag - automatically generate the output file name with the proper suffix determined by -T image type flag 

				cout << "Running command -->" << cmd << "<--\n";
				int result = system(cmd.c_str());
				cout << "It returned '" << result << (result ? "' (command failed)\n" : "' (command passed)\n");
			}*/
		}
	}
};

//int main(int argc, char* argv[])
//{
//	if (argc != 3) {
//		cerr << "Usage: " << argv[0] << " item-csv-file    item-csv-separator-char\n";
//		return 1;
//	}
//
//	string filename = argv[1];
//	char sep = argv[2][0];
//	vector<vector<string> > csvItemData;
//
//
//	try {
//		csvRead(filename, sep, csvItemData);
//		csvPrint(csvItemData);
//
//		ItemManager im(csvItemData);
//		im.print();
//		im.graph(filename);
//	}
//	catch (const string& e) {
//		cerr << "it threw! - " << e << "\n";
//	}
//}
