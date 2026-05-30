/***
* Kavya Nemavat
* knemavat
* 2026 Spring CSE101 PA5
* Words.cpp
* Top-level client for Dictionary ADT based on BST. Parses an input file into words, discarding duplicates, and records their insertion order. 
***/
#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include "Dictionary.h"

using namespace std;

int main(int argc, char * argv[]) {
    size_t begin, end, len;
    ifstream in;
    ofstream out;
    string line;
    string token;
    // Standard delimiter set handling punctuation and spaces
    string delimiters = " \t\n\r\\\"\',<.>/?;:[{]}|`~!@#$%^&*()-_=+0123456789";

    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
        return EXIT_FAILURE;
    }

    in.open(argv[1]);
    if (!in.is_open()) {
        cerr << "Unable to open file " << argv[1] << " for reading" << endl;
        return EXIT_FAILURE;
    }

    out.open(argv[2]);
    if (!out.is_open()) {
        cerr << "Unable to open file " << argv[2] << " for writing" << endl;
        return EXIT_FAILURE;
    }

    Dictionary D;
    int order = 0;

    // Read each line and parse words
    while (getline(in, line)) {
        len = line.length();
        
        begin = min(line.find_first_not_of(delimiters, 0), len);
        end = min(line.find_first_of(delimiters, begin), len);
        token = line.substr(begin, end - begin);
        
        while (token != "") {
            // Only insert unique words, retaining exact casing
            if (!D.contains(token)) {
                D.setValue(token, order);
                order++;
            }
            begin = min(line.find_first_not_of(delimiters, end + 1), len);
            end = min(line.find_first_of(delimiters, begin), len);
            token = line.substr(begin, end - begin);
        }
    }

    // Step 1: Output the ordered list of insertion values exactly like (x, y, z)
    D.begin();
    if (D.hasCurrent()) {
        out << "(" << D.currentVal();
        D.next();
        while (D.hasCurrent()) {
            out << ", " << D.currentVal();
            D.next();
        }
        out << ")" << endl << endl;
    }

    // Step 2: Output the alphabetized keys, one per line
    for (D.begin(); D.hasCurrent(); D.next()) {
        out << D.currentKey() << endl;
    }

    in.close();
    out.close();

    return EXIT_SUCCESS;
}

