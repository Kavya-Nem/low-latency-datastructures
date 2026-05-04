/***
* Kavya Nemavat
* knemavat
* 2026 Spring CSE101 PA4
* MatrixTest.c
* Test client used to verify correctness of all Matrix ADT operations.
***/
#include "Matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void check(int condition, char* message) {
	if (condition) {
		printf("PASS: %s\n", message);
	} else {
		printf("FAIL: %s\n", message);
	}
}

Matrix identity (int n) {
	Matrix I = newMatrix(n);
	for(int i = 1; i <= n; i++) {
		changeEntry(I, i, i, 1.0);
	}
	return I;
}

int main() {
	printf("===== MATRIX ADT TESTS =====\n");
	Matrix A = newMatrix(3);
	Matrix B = newMatrix(3);
	changeEntry(A,1,1,1);
	changeEntry(A,1,2,2);
	changeEntry(A,2,1,3);
	changeEntry(A,2,3,4);
	changeEntry(B,1,1,5);
	changeEntry(B,1,2,6);
	changeEntry(B,2,1,7);
	changeEntry(B,3,3,8);
	check(dimension(A) == 3, "dimension");
	check(numNonZero(A) == 4, "numNonZero A");
	Matrix C = copy(A);
	check(equals(A, C), "copy equals");
	Matrix S = scalarMult(2, A);
	Matrix expectedS = newMatrix(3);
	changeEntry(expectedS,1,1,2);
	changeEntry(expectedS,1,2,4);
	changeEntry(expectedS,2,1,6);
	changeEntry(expectedS,2,3,8);
	check(equals(S, expectedS), "scalarMult correctness");
	Matrix zero = scalarMult(0, A);
	check(numNonZero(zero) == 0, "scalarMult by 0");
	Matrix sumAB = sum(A, B);
	Matrix expectedSum = newMatrix(3);
	changeEntry(expectedSum,1,1,6);
	changeEntry(expectedSum,1,2,8);
	changeEntry(expectedSum,2,1,10);
	changeEntry(expectedSum,2,3,4);
	changeEntry(expectedSum,3,3,8);
	check(equals(sumAB, expectedSum), "sum correctness");
	check(equals(sum(A,B), sum(B,A)), "sum commutativity");
	Matrix diffAB = diff(A, B);
	Matrix expectedDiff = newMatrix(3);
	changeEntry(expectedDiff,1,1,-4);
	changeEntry(expectedDiff,1,2,-4);
	changeEntry(expectedDiff,2,1,-4);
	changeEntry(expectedDiff,2,3,4);
	changeEntry(expectedDiff,3,3,-8);
	check(equals(diffAB, expectedDiff), "diff correctness");
	Matrix zero2 = diff(A, A);
	check(numNonZero(zero2) == 0, "A - A = zero");
	Matrix T = transpose(A);
	Matrix TT = transpose(T);
	check(equals(TT, A), "double transpose");
	Matrix I = identity(3);
	Matrix prodAI = product(A, I);
	check(equals(prodAI, A), "A * I = A");
	Matrix prodIA = product(I, A);
	check(equals(prodIA, A), "I * A = A");
	Matrix prodAB = product(A, B);
	Matrix expectedProd = newMatrix(3);
	changeEntry(expectedProd,1,1,19);
	changeEntry(expectedProd,1,2,6);
	changeEntry(expectedProd,2,1,15);
	changeEntry(expectedProd,2,2,18);
	check(equals(prodAB, expectedProd), "product correctness");
	makeZero(A);
	check(numNonZero(A) == 0, "makeZero clears matrix");
	Matrix Z = newMatrix(3);
	check(equals(A, Z), "makeZero equals zero matrix");
	freeMatrix(&A);
	freeMatrix(&B);
	freeMatrix(&C);
	freeMatrix(&S);
	freeMatrix(&expectedS);
	freeMatrix(&sumAB);
	freeMatrix(&expectedSum);
	freeMatrix(&diffAB);
	freeMatrix(&expectedDiff);
	freeMatrix(&T);
	freeMatrix(&TT);
	freeMatrix(&I);
	freeMatrix(&prodAI);
	freeMatrix(&prodIA);
	freeMatrix(&prodAB);
	freeMatrix(&expectedProd);
	freeMatrix(&Z);
	freeMatrix(&zero);
	freeMatrix(&zero2);
	check(A == NULL, "freeMatrix NULL A");
	printf("===== ALL TESTS DONE =====\n");
	return 0;
}
