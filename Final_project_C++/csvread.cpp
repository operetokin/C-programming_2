/*#include <fstream>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

void trimSpace(string& s) {
	while (!s.empty() && s[0] == ' ')
		s.erase(0, 1);
}

void csvPrint(vector <vector<string> > & csvData)
{
	cout << "range-based for:\n";
	for (auto& line : csvData) {
		for (auto& field : line) {
			cout << " {" << field << "}";
		}
		cout << "\n";
	}
	cout << "\n";
	cout << "\n";

	cout << "indicates for:\n";
	for (size_t line = 0; line < csvData.size(); line++) {
		for (size_t field = 0; field < csvData[line].size(); field++) {
			cout << " <" << csvData[line][field] << ">";
		}
		cout << "\n";
	}
	cout << "\n";
	cout << "\n";

	cout << "iterator for:\n";
	for (auto line = csvData.begin(); line < csvData.end(); line++) {
		for (auto field = line->begin(); field < line->end(); field++) {
			cout << " (" << *field << ")";
		}
		cout << "\n";
	}
	cout << "\n";
	cout << "\n";
}

void csvRead(string& filename, char sep, vector <vector<string> > & csvData)
{
	fstream in(filename, ios::in);
	if ( !in.is_open() )
		throw string("cannot open file'") + filename + "'";
	
	string line;
	while (getline(in, line)) {
		auto cr = line.find('\r');
		if (cr != string::npos)
			line.erase(cr, 1);

		cout << "line = [" << line << "]\n";

		string field;
		vector<string> fields;

		for (size_t index = 0; index < line.size(); index++) {
			if (line[index] != sep)
				field += line[index];
			else {
				//fields.push_back(field);
				//field.clear(); //old school
				trimSpace(field);

				fields.push_back(move(field));
			}
		}

		trimSpace(field);

		fields.push_back(move(field));  //dont forget about last field!

		for (auto&e : fields)
			cout << " <" << e << ">";
		cout << "\n";

		csvData.push_back(move(fields));

	}

	for (auto& line : csvData) {
		for (auto& field : line) {
			cout << " {" << field << "}";
		}
		cout << "\n";
	}
	cout << "\n";
}

/*int main(int argc, char* argv[])
{
	if (argc != 3) {
		cerr << "Usage: " << argv[0] << " task - csv - file    task - csv - separator - char\n";
			return 1;
	}

	string filename = argv[1];
	char sep = argv[2][0];
	vector<vector<string> > csvTaskData;
	

	try {
		csvRead(filename, sep, csvTaskData);
		csvPrint(csvTaskData);
	}
	catch (const string& e) {
		cerr << "it threw! - " << e << "\n";
	}
}*/