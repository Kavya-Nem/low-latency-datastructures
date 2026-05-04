#ifndef MATRIX_H_INCLUDE
#define MATRIX_H_INCLUDE
#include <stdbool.h>
#include <stdio.h>
#include "List.h"
typedef struct MatrixObj* Matrix;
Matrix newMatrix(int n);
void freeMatrix(Matrix* pM);
int dimension(Matrix M);
int numNonZero(Matrix M);
bool equals(Matrix A, Matrix B);
void makeZero(Matrix M);
//Pre: 1<=i<=dimension(M), 1<=j<=dimension(M)
void changeEntry(Matrix M, int i, int j, double x);
Matrix copy(Matrix A);
Matrix transpose(Matrix A);
Matrix scalarMult(double x, Matrix A);
// pre: dimension(A)==dimension(B)
Matrix sum(Matrix A, Matrix B);
// pre: dimension(A)==dimension(B)
Matrix diff(Matrix A, Matrix B);
// pre: dimension(A)==dimension(B)
Matrix product(Matrix A, Matrix B);
void printMatrix(FILE* out, Matrix M);
#endif
