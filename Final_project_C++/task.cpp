
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include "util.h"
using namespace std;

class Task {
	string name, slots = { "1" }, pass, fail; //slots is number of slots
public:
	Task() {}
	Task(vector<string> line) {
		switch (line.size()) {
		case 4:
			if (validTaskName(line[3])) {
			fail = line[3];
			}
			else
				throw string("fail task name not understood ==>") + line[3] + "<==";
			[[fallthrough]]
		case 3:
			if (validTaskName(line[2])) {
				pass = line[2];
			}
			else
				throw string("pass task name not understood ==>") + line[2] + "<==";
			[[fallthrough]]
		case 2:
			if (validSlots(line[1])) {
				slots = line[1];
			}
			else
				throw string("slots not understood ==>") + line[1] + "<==";
			[[fallthrough]]
		case 1:
			if (validTaskName(line[0]))
				name = line[0];
			else
				throw string("Expected task name, found '") + line[0] + "'";
			break;
		default:
			throw string("expected 1, 2, 3, or 4 fields, found ") + to_string(line.size());
			break;
		}
		if (slots.empty())
			slots = "1";
	}
	void print() {
		cout << "|name|slots|pass|fail| = "
			<< "|" << name
			<< "|" << slots
			<< "|" << pass
			<< "|" << fail
			<< "|\n";
	}

	void graph(fstream& gv) {
		if (!pass.empty()) {
			gv << '"' << name << '"';
			gv << "->";
			gv << '"' << pass << '"';
			gv << "[color=\"green\"]";
			gv << ";\n";
		}

		if (!fail.empty()) {
			gv << '"' << name << '"';
			gv << "->";
			gv << '"' << fail << '"';
			gv << "[color=\"red\"]";
			gv << ";\n";
		}

		if (pass.empty() && fail.empty()) {
			gv << '"' << name << '"';
			gv << ";\n";
		}
		/*if (pass.empty() && fail.empty())
			gv << '"' << name << '"' << "\n";

		if (!pass.empty()) {
			gv << '"' << name << '"'
				<< "->"
				<< '"' << pass << '"'
				<< "[color=\"green\"]; \n";
		}
		if (!fail.empty()) {
			gv << '"' << name << '"'
				<< "->"
				<< '"' << pass << '"'
				<< "[color=\"red\"]; \n";
		}*/

		/*	cout << "|name|slots|pass|fail| = "
				<< "|" << name
				<< "|" << slots
				<< "|" << pass
				<< "|" << fail
				<< "|\n";
		}*/
	}
	};

	class TaskManager {
		vector<Task> taskList;
	public:
		TaskManager(vector < vector<string> > & csvTaskData) {
			for (auto& line : csvTaskData) {
				try {
					taskList.push_back(move(Task(line)));
				}
				catch (const string & e) {
					cerr << "Problem: " << e << "\n";
				}
			}
		}
		void print() {
			for (auto& t : taskList)
				t.print();
		}

		void graph(string& filename) {
			fstream gv(filename + ".gv", ios::out | ios::trunc);
			if (gv.is_open()) {
				gv << "digraph taskGraph {\n";

				for (auto& t : taskList)
					t.graph(gv);

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

	int main(int argc, char* argv[])
	{
		if (argc != 3) {
			cerr << "Usage: " << argv[0] << " task-csv-file    task-csv-separator-char\n";
			return 1;
		}

		string filename = argv[1];
		char sep = argv[2][0];
		vector<vector<string> > csvTaskData;


		try {
			csvRead(filename, sep, csvTaskData);
			csvPrint(csvTaskData);

			TaskManager tm(csvTaskData);
			tm.print();
			tm.graph(filename);
		}
		catch (const string& e) {
			cerr << "it threw! - " << e << "\n";
		}
	}
	