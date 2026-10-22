/***
* Kavya Nemavat
* knemavat
* 2026 Spring CSE101 PA4
* Matrix.c
* Implementation of Matrix ADT which can perform addition, subtraction, and multiplication on two matrices.
***/
#include "Matrix.h"
#include <stdlib.h>

typedef struct Entry {
        int column;
        double value;
} Entry;

typedef struct MatrixObj{
        List* matrix;
	int dimension;
	int numNonZero;
} MatrixObj;

Entry* newEntry(int column, double value) {
        Entry* E = malloc(sizeof(Entry));
        if (E == NULL) {
                fprintf(stderr, "Matrix Error: newEntry(): NULL entry\n");
                exit(EXIT_FAILURE);
        }
        E->column = column;
        E->value = value;
        return E;
}

Matrix newMatrix(int n) {
	Matrix M = malloc(sizeof(MatrixObj));
	if (M == NULL) {
		fprintf(stderr, "Matrix Error: newMatrix(): NULL matrix\n");
		exit(EXIT_FAILURE);
	}
	M->matrix = malloc(sizeof(List) * (n + 1));
	for (int i = 1; i <= n; i++) {
		M->matrix[i] = newList();
	}
	M->dimension = n;
	M->numNonZero = 0;
	return(M);
}

void freeMatrix(Matrix *pM) {
	if (pM != NULL && *pM != NULL) {
		makeZero(*pM);
		for (int i = 1; i <= dimension(*pM); i++) {
			freeList(&((*pM)->matrix[i]));
		}
		free((*pM)->matrix);
		(*pM)->matrix = NULL;
		free(*pM);
		*pM = NULL;
	}
}

int dimension(Matrix M) {
	if (M == NULL) {
		fprintf(stderr, "Matrix Error: dimension(): NULL matrix\n");
		exit(EXIT_FAILURE);
	}
	return(M->dimension);
}

int numNonZero(Matrix M) {
	if (M == NULL) {
		fprintf(stderr, "Matrix Error: numNonZero(): NULL matrix\n");
		exit(EXIT_FAILURE);
	}
	return(M->numNonZero);
}

bool equals(Matrix A, Matrix B) {
	if (A == NULL || B == NULL) {
		fprintf(stderr, "Matrix Error: equals(): A or B is NULL matrix\n");
		exit(EXIT_FAILURE);
	}
	if ((A->dimension == B->dimension) && (A->numNonZero == 0) && (B->numNonZero == 0)) {
		return true;
	} else if ((A->dimension == B->dimension) && (A->numNonZero == B->numNonZero)) {
		for (int i = 1; i <= dimension(A); i++) {
        		if (length(A->matrix[i]) != length(B->matrix[i])) {
                		return false;
        		}
			moveFront(B->matrix[i]);
			for (moveFront(A->matrix[i]); position(A->matrix[i]) != -1; moveNext(A->matrix[i])) {
				Entry* e1 = get(A->matrix[i]);
				Entry* e2 = get(B->matrix[i]);
				if ((e1->column != e2->column) || (e1->value != e2->value)) {
					return false;
				}
				moveNext(B->matrix[i]);
			}
		}
        	return true;
	} else {
		return false;
	}
}

void makeZero(Matrix M){
	if (M == NULL) {
		fprintf(stderr, "Matrix Error: makeZero(): NULL matrix\n");
		exit(EXIT_FAILURE);
	}
	for (int i = 1; i <= dimension(M); i++) {
		for (moveFront(M->matrix[i]); position(M->matrix[i]) != -1; moveNext(M->matrix[i])) {
			Entry* e = get(M->matrix[i]);
			free(e);
			e = NULL;
		}
		clear(M->matrix[i]);
	}
	M->numNonZero = 0;
}

//Pre: 1<=i<=dimension(M), 1<=j<=dimension(M)
void changeEntry(Matrix M, int i, int j, double x){
	if (M == NULL) {
		fprintf(stderr, "Matrix Error: changeEntry(): NULL matrix\n");
		exit(EXIT_FAILURE);
	}
	if ((1 > i) || (i > dimension(M))) {
                fprintf(stderr, "Matrix Error: changeEntry(): i is not a valid row\n");
                exit(EXIT_FAILURE);
        }
	if ((1 > j) || (j > dimension(M))) {
                fprintf(stderr, "Matrix Error: changeEntry(): j is not a valid column\n");
                exit(EXIT_FAILURE);
        }
	List L = M->matrix[i];
	bool entryExists = false;
	for (moveFront(L); position(L) != -1; moveNext(L)) {
		Entry* e = (Entry*)get(L);
		if (e->column == j) {
			entryExists = true;
			break;
		}
		if (e->column > j) {
			break;
		}
	}
	if (x == 0) {
		if (entryExists) {
			Entry* e = get(L);
			free(e);
			delete(L);
			M->numNonZero--;
		}
	} else {
		if (entryExists) {
			Entry* e = get(L);
			e->value = x;
		} else {
			if (position(L) != -1) {
				insertBefore(L, newEntry(j, x));
			} else {
				append(L, newEntry(j, x));
			}
			M->numNonZero++;
		}
	}
}

Matrix copy(Matrix A){
	if (A == NULL) {
		fprintf(stderr, "Matrix Error: copy(): NULL matrix\n");
		exit(EXIT_FAILURE);
	}
	Matrix B = newMatrix(dimension(A));
	for (int i = 1; i <= dimension(A); i++){
		for (moveFront(A->matrix[i]); position(A->matrix[i]) != -1; moveNext(A->matrix[i])){
			Entry* e = get(A->matrix[i]);
			append(B->matrix[i], newEntry(e->column, e->value));
		}
        }
	B->numNonZero = numNonZero(A);
	return(B);
}

Matrix transpose(Matrix A) {
	if (A == NULL) {
		fprintf(stderr, "Matrix Error: transpose(): NULL matrix\n");
		exit(EXIT_FAILURE);
	}
	Matrix B = newMatrix(dimension(A));
	for (int i = 1; i <= dimension(A); i++) {
		for (moveFront(A->matrix[i]); position(A->matrix[i]) != -1; moveNext(A->matrix[i])){
			Entry* e = (Entry*)(get(A->matrix[i]));
			append(B->matrix[e->column], newEntry(i, e->value));
		}
	}
	B->numNonZero = numNonZero(A);
	return(B);
}

Matrix scalarMult(double x, Matrix A) {
        if (A == NULL) {
		fprintf(stderr, "Matrix Error: scalarMult(): NULL matrix\n");
		exit(EXIT_FAILURE);
	}
	Matrix B = newMatrix(dimension(A));
	if (x == 0) {
		return(B);
	}
        for (int i = 1; i <= dimension(A); i++){
		for (moveFront(A->matrix[i]); position(A->matrix[i]) != -1; moveNext(A->matrix[i])){
			Entry* e = (Entry*)(get(A->matrix[i]));
			append(B->matrix[i], newEntry(e->column, e->value * x));
		}
	}
	B->numNonZero = numNonZero(A);
	return(B);
}

// Pre: dimension(A)==dimension(B)
Matrix sum(Matrix A, Matrix B) {
	if (A == NULL || B == NULL) {
		fprintf(stderr, "Matrix Error: sum(): A or B is NULL matrix\n");
		exit(EXIT_FAILURE);
	}
	if (dimension(A) != dimension(B)) {
		fprintf(stderr, "Matrix Error: sum(): Dimension of A does not match dimension of B\n");
		exit(EXIT_FAILURE);
	}
	Matrix C = newMatrix(dimension(A));
	if ((numNonZero(A) == 0) && (numNonZero(B) == 0)){
		return(C);
	} else if (numNonZero(A) == 0) {
		freeMatrix(&C);
		return(copy(B));
	} else if (numNonZero(B) == 0) {
		freeMatrix(&C);
		return(copy(A));
	} else if (equals(A, B)) {
		freeMatrix(&C);
		return(scalarMult(2.0, A));
	} else {
		for (int i = 1; i <= dimension(A); i++) {
			moveFront(A->matrix[i]);
			moveFront(B->matrix[i]);
			while ((position(A->matrix[i]) != -1) && (position(B->matrix[i]) != -1)) {
				Entry* e1 = get(A->matrix[i]);
                                Entry* e2 = get(B->matrix[i]);
				if (e1->column == e2->column) {
					if (e1->value + e2->value != 0) {
						append(C->matrix[i], newEntry(e1->column, e1->value + e2->value));
						C->numNonZero++;
					}
					moveNext(A->matrix[i]);
					moveNext(B->matrix[i]);
				} else if (e1->column < e2->column){
					append(C->matrix[i], newEntry(e1->column, e1->value));
					C->numNonZero++;
					moveNext(A->matrix[i]);
				} else {
					append(C->matrix[i], newEntry(e2->column, e2->value));
					C->numNonZero++;
					moveNext(B->matrix[i]);
				}
			}
			while (position(A->matrix[i]) != -1) {
				Entry* e = get(A->matrix[i]);
				append(C->matrix[i], newEntry(e->column, e->value));
				C->numNonZero++;
                                moveNext(A->matrix[i]);
                        }
			while (position(B->matrix[i]) != -1) {
                                Entry* e = get(B->matrix[i]);
                                append(C->matrix[i], newEntry(e->column, e->value));
				C->numNonZero++;
                                moveNext(B->matrix[i]);
                        }
		}
		return(C);
	}
}

// Pre: dimension(A)==dimension(B)
Matrix diff(Matrix A, Matrix B) {
	if (A == NULL || B == NULL) {
		fprintf(stderr, "Matrix Error: diff(): A or B is NULL matrix\n");
		exit(EXIT_FAILURE);
	}
	if (dimension(A) != dimension(B)) {
		fprintf(stderr, "Matrix Error: diff(): Dimension of A does not match dimension of B\n");
		exit(EXIT_FAILURE);
	}
	Matrix C = newMatrix(dimension(A));
	if ((numNonZero(A) == 0) && (numNonZero(B) == 0)){
		return(C);
	} else if (numNonZero(B) == 0) {
		freeMatrix(&C);
		return(copy(A));
	} else if (equals(A, B)) {
		return(C);
	} else if (numNonZero(A) == 0) {
		freeMatrix(&C);
		return(scalarMult(-1.0, B));
	} else {
		for (int i = 1; i <= dimension(A); i++) {
			moveFront(A->matrix[i]);
			moveFront(B->matrix[i]);
			while ((position(A->matrix[i]) != -1) && (position(B->matrix[i]) != -1)) {
				Entry* e1 = get(A->matrix[i]);
                                Entry* e2 = get(B->matrix[i]);
				if (e1->column == e2->column) {
					if (e1->value - e2->value != 0) {
						append(C->matrix[i], newEntry(e1->column, e1->value - e2->value));
						C->numNonZero++;
					}
					moveNext(A->matrix[i]);
					moveNext(B->matrix[i]);
				} else if (e1->column < e2->column){
					append(C->matrix[i], newEntry(e1->column, e1->value));
					C->numNonZero++;
					moveNext(A->matrix[i]);
				} else {
					append(C->matrix[i], newEntry(e2->column, e2->value * -1));
					C->numNonZero++;
					moveNext(B->matrix[i]);
				}
			}
			while (position(A->matrix[i]) != -1) {
				Entry* e = get(A->matrix[i]);
				append(C->matrix[i], newEntry(e->column, e->value));
				C->numNonZero++;
				moveNext(A->matrix[i]);
			}
			while (position(B->matrix[i]) != -1) {
				Entry* e = get(B->matrix[i]);
				append(C->matrix[i], newEntry(e->column, e->value * -1));
				C->numNonZero++;
				moveNext(B->matrix[i]);
                        }
		}
		return(C);
	}
}

double vectorDot(List P, List Q) {
	if (P == NULL || Q == NULL) {
		fprintf(stderr, "Matrix Error: vectorDot(): P or Q is NULL list\n");
		exit(EXIT_FAILURE);
	}
	if (length(P) == 0 || length(Q) == 0) {
		return(0.0);
	} else {
		double sum = 0;
		moveFront(P);
		moveFront(Q);
		while ((position(P) != -1) && (position(Q) != -1)) {
			Entry* e1 = get(P);
			Entry* e2 = get(Q);
			if (e1->column == e2->column) {
				sum += e1->value * e2->value;
				moveNext(P);
				moveNext(Q);
			} else if (e1->column < e2->column) {
				moveNext(P);
			} else {
				moveNext(Q);
			}
		}
		return(sum);
	}
}

// Pre: dimension(A)==dimension(B)
Matrix product(Matrix A, Matrix B) {
	if (A == NULL || B == NULL) {
		fprintf(stderr, "Matrix Error: product(): A or B is NULL matrix\n");
		exit(EXIT_FAILURE);
	}
	if (dimension(A) != dimension(B)) {
		fprintf(stderr, "Matrix Error: product(): Dimension of A does not match dimension of B\n");
		exit(EXIT_FAILURE);
	}
	Matrix R = newMatrix(dimension(A));
	if ((numNonZero(A) == 0) || (numNonZero(B) == 0)) {
		return(R);
	} else {
		Matrix T = transpose(B);
		for (int i = 1; i <= dimension(A); i++){
			if (length(A->matrix[i]) == 0) {
				continue;
			}
			for (int j = 1; j <= dimension(T); j++){
				if (length(T->matrix[j]) == 0) {
					continue;
				}
				double sum;
				sum = vectorDot(A->matrix[i], T->matrix[j]);
				if (sum != 0) {
					append(R->matrix[i], newEntry(j, sum));
					R->numNonZero++;
				}
			}
		}
		freeMatrix(&T);
		return(R);
	}
}

void printMatrix(FILE *out, Matrix M) {
	if (M == NULL) {
		fprintf(stderr, "Matrix Error: printMatrix(): NULL matrix\n");
		exit(EXIT_FAILURE);
	}
	bool entered = false;
	for (int i = 1; i <= dimension(M); i++) {
		if (length(M->matrix[i]) > 0) {
			if (entered) {
				fprintf(out, "\n");
			} else {
				entered = true;
			}
			fprintf(out, "%d:", i);
			for (moveFront(M->matrix[i]); position(M->matrix[i]) != -1; moveNext(M->matrix[i])) {
				fprintf(out, " (%d, %.1lf)", ((Entry*)(get(M->matrix[i])))->column, ((Entry*)(get(M->matrix[i])))->value);
			}
		}
	}
}
