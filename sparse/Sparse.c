/***
* Kavya Nemavat
* knemavat
* 2026 Spring CSE101 PA4
* Sparse.c
* Main program. Reads an input file, extracts dimension of matrix and the number of non-zero values. Then, it populates two matrices with given values and performs 8 mathematical operations on both the matrices. Finally, it prints the output of all the operations that're done.
***/
#include "Matrix.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	FILE *in, *out;
	if (argc != 3) {
		fprintf(stderr, "Usage: %s <input file> <output file>\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	in = fopen(argv[1], "r");
	if (in == NULL) {
		fprintf(stderr, "Unable to open file %s for reading\n", argv[1]);
		exit(EXIT_FAILURE);
	}
	out = fopen(argv[2], "w");
	if (out == NULL) {
		fprintf(stderr, "Unable to open file %s for writing\n", argv[2]);
		exit(EXIT_FAILURE);
	}
	int n;
	int a;
	int b;
	if (fscanf(in, "%d %d %d", &n, &a, &b) != 3) {
		return(EXIT_FAILURE);
	}
	Matrix A = newMatrix(n);
	int row;
	int column;
	double value;
	for (int i = 0; i < a; i++) {
		if (fscanf(in, "%d %d %lf", &row, &column, &value) == 3) {
			changeEntry(A, row, column, value);
		}
	}
	Matrix B = newMatrix(n);
	for (int i = 0; i < b; i++) {
		if (fscanf(in, "%d %d %lf", &row, &column, &value) == 3) {
			changeEntry(B, row, column, value);
		}
	}
	fprintf(out, "A has %d non-zero entries:\n", numNonZero(A));
	printMatrix(out, A);
	if (numNonZero(A) > 0) {
		fprintf(out, "\n");
	}
	fprintf(out, "\nB has %d non-zero entries:\n", numNonZero(B));
	printMatrix(out, B);
	if (numNonZero(B) > 0) {
                fprintf(out, "\n");
        }
	fprintf(out, "\n(1.5)*A =\n");
	Matrix SM = scalarMult(1.5, A);
	printMatrix(out, SM);
	if (numNonZero(SM) > 0) {
                fprintf(out, "\n");
        }
	freeMatrix(&SM);
	fprintf(out, "\nA+B =\n");
	Matrix SAB = sum(A, B);
	printMatrix(out, SAB);
	if (numNonZero(SAB) > 0) {
                fprintf(out, "\n");
        }
	freeMatrix(&SAB);
	fprintf(out, "\nA+A =\n");
	Matrix SAA = sum(A, A);
	printMatrix(out, SAA);
	if (numNonZero(SAA) > 0) {
                fprintf(out, "\n");
        }
	freeMatrix(&SAA);
	fprintf(out, "\nB-A =\n");
	Matrix DBA = diff(B, A);
	printMatrix(out, DBA);
	if (numNonZero(DBA) > 0) {
                fprintf(out, "\n");
        }
	freeMatrix(&DBA);
	fprintf(out, "\nA-A =\n");
	Matrix DAA = diff(A, A);
	printMatrix(out, DAA);
	freeMatrix(&DAA);
	fprintf(out, "\nTranspose(A) =\n");
	Matrix T = transpose(A);
	printMatrix(out, T);
	if (numNonZero(T) > 0) {
                fprintf(out, "\n");
        }
	freeMatrix(&T);
	fprintf(out, "\nA*B =\n");
	Matrix PAB = product(A, B);
	printMatrix(out, PAB);
	if (numNonZero(PAB) > 0) {
                fprintf(out, "\n");
        }
	freeMatrix(&PAB);
	fprintf(out, "\nB*B =\n");
	Matrix PBB = product(B, B);
	printMatrix(out, PBB);
	if (numNonZero(PBB) > 0) {
                fprintf(out, "\n");
        }
	freeMatrix(&PBB);
	freeMatrix(&B);
	freeMatrix(&A);
	fclose(in);
	fclose(out);
	return 0;
}
