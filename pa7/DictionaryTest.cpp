/***
* Kavya Nemavat
* knemavat
* 2026 Spring CSE101 PA5
* DictionaryTest.c
* Test client used to verify correctness of all Dictionary ADT operations.
***/
#include <iostream>
#include <string>
#include <stdexcept>
#include "Dictionary.h"

using namespace std;

int main() {
    cout << "Starting DictionaryTest..." << endl << endl;

    Dictionary A;

    // Test 1: Basic insertions and size
    cout << "Test 1: Insertions and size()" << endl;
    A.setValue("apple", 1);
    A.setValue("banana", 2);
    A.setValue("cherry", 3);
    A.setValue("date", 4);
    A.setValue("elderberry", 5);

    cout << "A.size() (Expected 5): " << A.size() << endl;
    cout << "A contains 'banana' (Expected 1): " << A.contains("banana") << endl;
    cout << "A contains 'fig' (Expected 0): " << A.contains("fig") << endl;
    cout << endl;

    // Test 2: Overwriting a value
    cout << "Test 2: Overwriting a value" << endl;
    A.setValue("cherry", 300);
    cout << "Value of 'cherry' (Expected 300): " << A.getValue("cherry") << endl;
    cout << endl;

    // Test 3: String outputs
    cout << "Test 3: to_string() and pre_string()" << endl;
    cout << "In-order (to_string):" << endl << A.to_string() << endl;
    cout << "Pre-order (pre_string):" << endl << A.pre_string() << endl;

    // Test 4: Copy constructor and equals
    cout << "Test 4: Copy constructor and equals()" << endl;
    Dictionary B = A;
    cout << "B.size() (Expected 5): " << B.size() << endl;
    cout << "A == B (Expected 1): " << (A == B) << endl;

    B.setValue("fig", 6);
    cout << "A == B after modifying B (Expected 0): " << (A == B) << endl;
    cout << endl;

    // Test 5: Forward Iteration
    cout << "Test 5: Forward Iteration" << endl;
    cout << "Forward printing B: ";
    for (B.begin(); B.hasCurrent(); B.next()) {
        cout << "(" << B.currentKey() << ", " << B.currentVal() << ") ";
    }
    cout << endl << endl;

    // Test 6: Reverse Iteration
    cout << "Test 6: Reverse Iteration" << endl;
    cout << "Reverse printing B: ";
    for (B.end(); B.hasCurrent(); B.prev()) {
        cout << "(" << B.currentKey() << ", " << B.currentVal() << ") ";
    }
    cout << endl << endl;

    // Test 7: Deletions
    cout << "Test 7: remove()" << endl;
    B.remove("cherry"); // Remove a node with two children (depending on tree structure)
    B.remove("apple");  // Remove root or leaf
    cout << "B.size() after 2 removals (Expected 4): " << B.size() << endl;
    cout << "B contains 'cherry' (Expected 0): " << B.contains("cherry") << endl;
    cout << endl;

    // Test 8: Clearing the Dictionary
    cout << "Test 8: clear()" << endl;
    B.clear();
    cout << "B.size() after clear (Expected 0): " << B.size() << endl;
    cout << endl;

    // Test 9: Exception Handling
    cout << "Test 9: Exception Handling" << endl;
    try {
        A.getValue("grape");
    } catch (logic_error& e) {
        cout << "Caught exception for getValue(): " << e.what() << endl;
    }

    try {
        A.remove("grape");
    } catch (logic_error& e) {
        cout << "Caught exception for remove(): " << e.what() << endl;
    }

    Dictionary C;
    try {
        C.currentKey();
    } catch (logic_error& e) {
        cout << "Caught exception for currentKey() on empty: " << e.what() << endl;
    }

    cout << endl << "DictionaryTest complete." << endl;

    return EXIT_SUCCESS;
}
