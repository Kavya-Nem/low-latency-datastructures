/***
* Kavya Nemavat
* knemavat
* 2026 Spring CSE101 PA8
* DictionaryTest.cpp
* Test client used to verify correctness of all Dictionary ADT operations.
***/

#include <iostream>
#include <cassert>
#include <stdexcept>
#include "Dictionary.h"

using namespace std;

int main() {
	Dictionary A;
	assert(A.size() == 0);
	assert(A.contains("a") == false);
	assert(A.hasCurrent() == false);
	A.setValue("a", 10);
	A.setValue("b", 20);
	A.setValue("a", 30);
	assert(A.getValue("a") == 30);
	A.clear();
	A.setValue("a", 15);
	A.remove("a");
	A.setValue("b", 25);
	A.begin();
	assert(A.currentKey() == "b");
	assert(A.currentVal() == 25);
	A.end();
	A.next();
	A.end();
	A.prev();
	assert(A.to_string() == "b : 25");
	assert(A.pre_string() == "b\n");
	assert(A == A);
	cout << A << endl;
	Dictionary B = A;
	cout << "All Unit Assertions Passed Cleanly!" << endl;
	return 0;
}
/* Expected Output:
b : 25
All Unit Assertions Passed Cleanly!
*/
