/***
* Kavya Nemavat
* knemavat
* 2026 Spring CSE101 PA5
* Dictionary.c
* Implementation of Dictionary ADT which can create, free, clear, set values, remove keys, copy, check equality, and print standard or diagnostic output of a dictionary type.
***/
#include <inttypes.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "Dictionary.h"

const size_t TableInitialSize = 8;
const double TableLoadFactorThreshold = 0.67;
const int TableExpandFactor1 = 4;
const int TableExpandFactor2 = 2;
const int TableSizeThreshold = 50000;
const int TableEmpty = 0;
const int TableDeleted = -1;
const size_t DataInitialSize = 1;
const double DataExpandFactor = 1.5;
const double DataDensityThreshold = 0.8;
const keyType DataEmpty = NULL;
const char dummy[] = {255, 0};
const keyType DataDeleted = dummy;

typedef uint64_t codeType;

typedef struct element{
	keyType key;
	valType val;
	codeType code;
}element;

typedef struct DictionaryObj{
	element* data;
	uint64_t dataNextIndex;
	uint64_t numPairs;
	uint64_t numDeleted;
	uint64_t dataSize;
	double dataDensity;
	size_t tableSize;
	double tableLoadFactor;
	int64_t* table;
}DictionaryObj;

codeType hash(keyType k) {
	codeType magicNumber1 = 0xcbf29ce484222325;
	codeType magicNumber2 = 0x100000001b3;
	codeType result = magicNumber1;
	codeType nextChar = *k;
	while( nextChar ) {
		result ^= nextChar;
		result *= magicNumber2;
		nextChar = *(++k);
	}
	return result;
}

size_t probe (codeType code, size_t tbl_size, size_t i) {
	codeType h1 = code & (tbl_size-1);
	codeType h2 = 2*(code & (tbl_size/2 - 1)) + 1;
	return (h1 + i*h2) & (tbl_size-1);
}

uint64_t findSlot(Dictionary D, keyType k, codeType code) {
	if (D == NULL) {
		fprintf(stderr, "Dictionary Error: findSlot(): NULL dictionary\n");
		exit(EXIT_FAILURE);
	}
	size_t i = 0;
	int64_t deleted = -1;
	uint64_t slot = probe(code, D->tableSize, i);
	while (D->table[slot] != TableEmpty){
		if (D->table[slot] != TableDeleted) {
			if (strcmp((D->data[D->table[slot]]).key, k) == 0) {
				return(slot);
			}
		} else if (deleted == -1){
			deleted = slot;
		}
		i++;
		slot = probe(code, D->tableSize, i);
	}
	if (deleted != -1) {
		return deleted;
	} else {
		return(slot);
	}
}

void insertIndex(int64_t* T, size_t m, size_t idx, codeType code){
	if (T == NULL) {
		fprintf(stderr, "Dictionary Error: insertIndex(): NULL table\n");
		exit(EXIT_FAILURE);
	}
	size_t i = 0;
	uint64_t slot = probe(code, m, i);
	while (T[slot] != TableEmpty && T[slot] != TableDeleted){
		i++;
		slot = probe(code, m, i);
	}
	T[slot] = idx;
}

element newElement(keyType key, valType value, codeType code) {
	element e;
	e.key = key;
	e.val = value;
	e.code = code;
	return e;
}

void compactData(Dictionary D){
	if (D == NULL) {
		fprintf(stderr, "Dictionary Error: compactData(): NULL dictionary\n");
		exit(EXIT_FAILURE);
	}
	D->numDeleted = 0;
	D->dataDensity = 1.0;
	element* newData = malloc(D->dataSize * sizeof(element));
	newData[0] = newElement(DataEmpty, 0, 0);
	uint64_t count = 0;
	for (uint64_t a = 1; a < D->dataNextIndex; a++){
		element e = D->data[a];
		if (e.key != DataDeleted) {
			newData[a - count] = newElement(e.key, e.val, e.code);
			(D->data[a]).key = NULL;
		} else {
			count++;
		}
	}
	D->dataNextIndex = D->numPairs;
	for (uint64_t b = D->dataNextIndex; b < D->dataSize; b++) {
		newData[b] = newElement(DataEmpty, 0, 0);
	}
	free(D->data);
	D->data = newData;
}

void expandTable(Dictionary D){
	if (D == NULL) {
		fprintf(stderr, "Dictionary Error: expandTable(): NULL dictionary\n");
		exit(EXIT_FAILURE);
	}
	if (D->dataDensity < DataDensityThreshold) {
		compactData(D);
	}
	if (D->tableSize < TableSizeThreshold) {
		D->tableSize *= TableExpandFactor1;
	} else {
		D->tableSize *= TableExpandFactor2;
	}
	D->tableLoadFactor = (double)D->numPairs / D->tableSize;
	D->table = realloc(D->table, sizeof(int64_t) * D->tableSize);
	memset(D->table, TableEmpty, D->tableSize * sizeof(int64_t));
	for (uint64_t i = 1; i < D->dataNextIndex; i++){
		element e = D->data[i];
		if (e.key != DataDeleted) {
			insertIndex(D->table, D->tableSize, i, e.code);
		}
	}
}

void expandData(Dictionary D){
	if (D == NULL) {
		fprintf(stderr, "Dictionary Error: expandData(): NULL dictionary\n");
		exit(EXIT_FAILURE);
	}
	uint64_t oldSize = D->dataSize;
	D->dataSize = ceil(D->dataSize * DataExpandFactor);
	D->data = realloc(D->data, sizeof(element) * D->dataSize);
	for (; oldSize < D->dataSize; oldSize++) {
		D->data[oldSize] = newElement(DataEmpty, 0, 0);
	}
}

Dictionary newDictionary(void) {
	Dictionary D = malloc(sizeof(DictionaryObj));
	if (D == NULL) {
		fprintf(stderr, "Dictionary Error: newDictionary(): NULL dictionary\n");
		exit(EXIT_FAILURE);
	}
	D->data = malloc(sizeof(element));
	D->data[0] = newElement(DataEmpty, 0, 0);
	D->dataNextIndex = 1;
	D->numPairs = 0;
	D->numDeleted = 0;
	D->dataSize = DataInitialSize;
	D->dataDensity = 1.0;
	D->tableSize = TableInitialSize;
	D->tableLoadFactor = 0.0;
	D->table = calloc(D->tableSize, sizeof(int64_t));
	return(D);
}

void freeDictionary(Dictionary* pD) {
	if (pD != NULL && *pD != NULL) {
		clear(*pD);
		free((*pD)->data);
		(*pD)->data = NULL;
		free((*pD)->table);
		(*pD)->table = NULL;
		free(*pD);
		*pD = NULL;
	}
}

int size(Dictionary D) {
	if (D == NULL) {
		fprintf(stderr, "Dictionary Error: size(): NULL dictionary\n");
		exit(EXIT_FAILURE);
	}
	return(D->numPairs);
}

bool contains(Dictionary D, keyType k) {
	if (D == NULL) {
		fprintf(stderr, "Dictionary Error: contains(): NULL dictionary\n");
		exit(EXIT_FAILURE);
	}
	int64_t tableValue = D->table[findSlot(D, k, hash(k))];
	if ((tableValue != TableEmpty) && (tableValue != TableDeleted)) {
		return(true);
	} else {
		return(false);
	}
}

//pre: contains(D, k)
valType getValue(Dictionary D, keyType k) {
	if (D == NULL) {
		fprintf(stderr, "Dictionary Error: getValue(): NULL dictionary\n");
		exit(EXIT_FAILURE);
	}
	if (!contains(D, k)) {
		fprintf(stderr, "Dictionary Error: getValue(): key not present\n");
		exit(EXIT_FAILURE);
	}
	return((D->data[D->table[findSlot(D, k, hash(k))]]).val);
}

void clear(Dictionary D){
	if (D == NULL) {
		fprintf(stderr, "Dictionary Error: clear(): NULL dictionary\n");
		exit(EXIT_FAILURE);
	}
	for (uint64_t i = 1; i < D->dataNextIndex; i++) {
		char* k = (char*)((D->data[i]).key);
		if (k != DataDeleted) {
			free(k);
		}
	}
	D->data = realloc(D->data, sizeof(element));
	D->dataNextIndex = 1;
	D->numPairs = 0;
	D->numDeleted = 0;
	D->dataSize = DataInitialSize;
	D->dataDensity = 1.0;
	D->tableSize = TableInitialSize;
	D->tableLoadFactor = 0.0;
	D->table = realloc(D->table, sizeof(int64_t) * D->tableSize);
	memset(D->table, TableEmpty, D->tableSize * sizeof(int64_t));
}

void setValue(Dictionary D, keyType k, valType v){
	if (D == NULL) {
		fprintf(stderr, "Dictionary Error: setValue(): NULL dictionary\n");
		exit(EXIT_FAILURE);
	}
	if (contains(D, k)){
		(D->data[D->table[findSlot(D, k, hash(k))]]).val = v;
	} else {
		D->numPairs++;
		D->tableLoadFactor = (double)D->numPairs / D->tableSize;
		if (D->tableLoadFactor > TableLoadFactorThreshold) {
			expandTable(D);
		}
		if (D->dataNextIndex == D->dataSize) {
			expandData(D);
		}
		D->dataDensity = (double)D->numPairs / (D->numPairs + D->numDeleted);
		char* newKey = malloc(strlen(k) + 1);
		strcpy(newKey, k);
		D->data[D->dataNextIndex] = newElement(newKey, v, hash(k));
		insertIndex(D->table, D->tableSize, D->dataNextIndex, hash(k));
		D->dataNextIndex++;
	}
}

//pre: contains(D, k)
void removeKey(Dictionary D, keyType k){
	if (D == NULL) {
		fprintf(stderr, "Dictionary Error: removeKey(): NULL dictionary\n");
		exit(EXIT_FAILURE);
	}
	if (!contains(D, k)) {
		fprintf(stderr, "Dictionary Error: removeKey(): key not present\n");
		exit(EXIT_FAILURE);
	}
	D->numPairs--;
	D->numDeleted++;
	D->dataDensity = (double)D->numPairs / (D->numPairs + D->numDeleted);
	D->tableLoadFactor = (double)D->numPairs / D->tableSize;
	uint64_t slot = findSlot(D, k, hash(k));
	int64_t index = D->table[slot];
	free((char*)(D->data[index]).key);
	(D->data[index]).key = DataDeleted;
	D->table[slot] = TableDeleted;
}

Dictionary copy(Dictionary D) {
	if (D == NULL) {
		fprintf(stderr, "Dictionary Error: copy(): NULL dictionary\n");
		exit(EXIT_FAILURE);
	}
	Dictionary A = newDictionary();
	for (uint64_t a = 1; a < D->dataNextIndex; a++) {
		element e = D->data[a];
		if (e.key != DataDeleted) {
			setValue(A, e.key, e.val);
		}
	}
	return(A);
}

bool equals(Dictionary A, Dictionary B) {
	if (A == NULL || B == NULL) {
		fprintf(stderr, "Dictionary Error: equals(): A or B is NULL dictionary\n");
		exit(EXIT_FAILURE);
	}
	if (size(A) != size(B)) {
		return(false);
	}
	for (uint64_t a = 1; a < A->dataNextIndex; a++){
		element e = A->data[a];
		if ((e.key != DataEmpty) && (e.key != DataDeleted) && ((!contains(B, e.key)) || (getValue(B, e.key) != e.val))) {
			return(false);
		}
	}
	return(true);
}

void printDictionary(FILE* out, Dictionary D) {
	if (D == NULL) {
		fprintf(stderr, "Dictionary Error: printDictionary(): NULL dictionary\n");
		exit(EXIT_FAILURE);
	}
	for (uint64_t i = 1; i < D->dataNextIndex; i++){
		element e = D->data[i];
		if (e.key != DataDeleted) {
			fprintf(out, "%s : %d\n", e.key, e.val);
		}
	}
}

void printDiagnostic(FILE* out, Dictionary D) {
	if (D == NULL) {
		fprintf(stderr, "Dictionary Error: printDiagnostic(): NULL dictionary\n");
		exit(EXIT_FAILURE);
	}
	fprintf(out, "\nData: \n");
	for (uint64_t i = 0; i < D->dataSize; i++){
		element e = D->data[i];
		if (e.key == DataEmpty){
			fprintf(out, "(null) : 0 : 0\n");
		} else if (e.key == DataDeleted) {
			fprintf(out, "%c : %d : %"PRIu64"\n", e.key[0], e.val, e.code);
		} else {
			fprintf(out, "%s : %d : %"PRIu64"\n", e.key, e.val, e.code);
		}
	}
	fprintf(out, "numPairs: %"PRIu64"\nnumDeleted: %"PRIu64"\ndataSize: %"PRIu64"\ndataNextIndex: %"PRIu64"\ndataDensity: %f\n\nTable: \n", D->numPairs, D->numDeleted, D->dataSize, D->dataNextIndex, D->dataDensity);
	for (size_t i = 0; i < D->tableSize; i++){
		fprintf(out, "%zu : %"PRId64"\n", i, D->table[i]);
	}
	fprintf(out, "tableSize: %zu\ntableLoadFactor: %f\n", D->tableSize, D->tableLoadFactor);
}
