#ifndef DICTIONARY_H_INCLUDE
#define DICTIONARY_H_INCLUDE
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
typedef const char* keyType;
typedef int valType;
typedef struct DictionaryObj* Dictionary;
Dictionary newDictionary(void);
void freeDictionary(Dictionary* pD);
int size(Dictionary D);
bool contains(Dictionary D, keyType k);
// pre: contains(D, k)
valType getValue(Dictionary D, keyType k);
void clear(Dictionary D);
void setValue(Dictionary D, keyType k, valType v);
// pre: contains(D, k)
void removeKey(Dictionary D, keyType k);
Dictionary copy(Dictionary D);
bool equals(Dictionary A, Dictionary B);
void printDictionary(FILE* out, Dictionary D);
void printDiagnostic(FILE* out, Dictionary D);
#endif
