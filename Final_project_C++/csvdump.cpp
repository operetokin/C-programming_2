/*
2 sets
#1 nodes
#2 edges, lines
dot-Tpng-o  foo.gv
foo.gv.png

digraph Foo{
X -> Y[color = red];
t -> A[color = green];


#include <fstream>
#include <iostream>
#include <vector>
#include <string>
using namespace std;
#include "util.h"

int main(int argc, char* argv[]) {
	if (argc != 3) {
		cerr << "Usage: " << argv[0] << " csv-file csv-separator-char\n";
		return 1;
	}

	string filename = argv[1];
	char sep = argv[2][0];
	vector<vector<string>> csvData;

	try {
		csvRead(filename, sep, csvData);
		csvPrint(csvData);
	}
	catch (const string& e) {
		cerr << "It threw = " << e << "\n";
	}
}
*/