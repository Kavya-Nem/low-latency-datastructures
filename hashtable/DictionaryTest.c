/***
* Kavya Nemavat
* knemavat
* 2026 Spring CSE101 PA5
* DictionaryTest.c
* Test client used to verify correctness of all Dictionary ADT operations.
***/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Dictionary.h"

void check(int condition, char* message) {
	if (condition) {
		printf("PASS: %s\n", message);
	} else {
		printf("FAIL: %s\n", message);
	}
}

int main() {
	printf("===== DICTIONARY ADT TESTS =====\n");
	Dictionary A = newDictionary();
	setValue(A, "a", 1);
	check(getValue(A, "a") == 1, "getValue A original");
	setValue(A, "b", 2);
	setValue(A, "c", 3);
	setValue(A, "d", 4);
	setValue(A, "a", 5);
	setValue(A, "b", 6);
	setValue(A, "c", 7);
	setValue(A, "d", 8);
	check(size(A) == 4, "size");
	check(contains(A, "a"), "contains A original");
	check(getValue(A, "a") == 5, "getValue A edited");
	removeKey(A, "a");
	check(!contains(A, "a"), "contains A edited");
	Dictionary B = copy(A);
	check(equals(A, B), "copy equals");
	clear(A);
	check(size(A) == 0, "clear clears dictionary");
	Dictionary C = newDictionary();
	check(equals(A, C), "clear equals empty dictionary");
	printDictionary(stdout, A);
	printDiagnostic(stdout, B);
	freeDictionary(&A);
	freeDictionary(&B);
	freeDictionary(&C);
	check(A == NULL, "freeDictionary");
	printf("===== ALL TESTS DONE =====\n");
	return 0;
}
