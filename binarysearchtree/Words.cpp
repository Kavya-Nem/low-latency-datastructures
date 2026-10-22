/***
* Kavya Nemavat
* knemavat
* 2026 Spring CSE101 PA7
* Words.cpp
* Main program. Reads an input file, extracts unique words, and outputs in alphabetical order using index Dictionary.
***/

#include <cmath>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>
#include "Dictionary.h"

using namespace std;

int main(int argc, char *argv[]) {
	int token_count = 0;
	size_t begin, end, len;
	ifstream in;
	ofstream out;
	string line;
	string token;
	string delim = " \t\n\r\\\"\',<.>/?;:[{]}|`~!@#$%^&*()-_=+0123456789";
	if (argc != 3) {
		cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
		return(EXIT_FAILURE);
	}
	in.open(argv[1]);
	if (!(in.is_open())) {
		cerr << "Unable to open file " << argv[1] << " for reading" << endl;
		return(EXIT_FAILURE);
	}
	out.open(argv[2]);
	if (!(out.is_open())) {
		cerr << "Unable to open file " << argv[2] << " for writing" << endl;
		return(EXIT_FAILURE);
	}
	Dictionary D;
	while (getline(in, line)) {
		len = line.length();
		begin = min(line.find_first_not_of(delim, 0), len);
		end = min(line.find_first_of(delim, begin), len);
		token = line.substr(begin, end - begin);
		while (token != "") {
			if (!(D.contains(token))) {
				D.setValue(token, token_count);
				token_count++;
			}
			begin = min(line.find_first_not_of(delim, end + 1), len);
			end = min(line.find_first_of(delim, begin), len);
			token = line.substr(begin, end - begin);
		}
	}
	out << "(";
	int count = 0;
	for (D.begin(); D.hasCurrent(); D.next()) {
		if (count != token_count - 1) {
			out << D.currentVal() << ", ";
		} else {
			out << D.currentVal();
		}
		count++;
	}
	out << ")" << endl << endl;
	for (D.begin(); D.hasCurrent(); D.next()) {
		out << D.currentKey() << endl;
	}
	in.close();
	out.close();
	return(EXIT_SUCCESS);
}
