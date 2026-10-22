/***
* Kavya Nemavat
* knemavat
* 2026 Spring CSE101 PA8
* WordFrequency.cpp
* Main program. Reads an input file, extracts words, and adds them to a dictionary along with frequency, or updates frequency if the word already exists inside of the dictionary. Finally, it prints the string representation of the dictionary to the output in form "key : value" in keys' insertion order.
***/

#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include "Dictionary.h"

using namespace std;

void lower(string& word){
	int i;
	for ( i=0; word[i] != '\0'; i++) {
		word[i] = tolower( (unsigned char)word[i] );
	}
}

int main(int argc, char *argv[]) {
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
			lower(token);
			if (D.contains(token)) {
				D.setValue(token, D.getValue(token) + 1);
			} else {
				D.setValue(token, 1);
			}
			begin = min(line.find_first_not_of(delim, end + 1), len);
			end = min(line.find_first_of(delim, begin), len);
			token = line.substr(begin, end - begin);
		}
	}
	out << D;
	in.close();
	out.close();
	return(EXIT_SUCCESS);
}
