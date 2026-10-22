/***
* Kavya Nemavat
* knemavat
* 2026 Spring CSE101 PA5
* WordFrequency.c
* Main program. Reads an input file, extracts words, and adds them to a dictionary along with frequency, or updates frequency if the word already exists inside of the dictionary. Finally, it prints the string representation of the dictionary to the output in form "key : value" in keys' insertion order.
***/
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Dictionary.h"

#define MAX_LEN 20480

void lower(char* word){
	int i;
	for ( i=0; word[i] != '\0'; i++) {
		word[i] = tolower( (unsigned char)word[i] );
	}
}

int main(int argc, char *argv[]) {
	FILE *in, *out;
	char line[MAX_LEN];
	char *token;
	char **words = NULL;
	int wordCount = 0;
	int capacity = 10;
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
	words = malloc(capacity * sizeof(char *));
	char *delim = " \t\n\r\\\"\',<.>/?;:[{]}|`~!@#$%^&*()-_=+0123456789";
	while (fgets(line, MAX_LEN, in) != NULL) {
		token = strtok(line, delim);
		while (token != NULL) {
			lower(token);
			if (wordCount >= capacity) {
				capacity *= 2;
				words = realloc(words, capacity * sizeof(char *));
			}
			words[wordCount] = malloc((strlen(token) + 1) * sizeof(char));
			strcpy(words[wordCount], token);
			wordCount++;
			token = strtok(NULL, delim);
		}
	}
	Dictionary D = newDictionary();
	if (wordCount > 0) {
		for (int i = 0; i < wordCount; i++) {
			if (contains(D, words[i])){
				setValue(D, words[i], getValue(D, words[i]) + 1);
			} else {
				setValue(D, words[i], 1);
			}
		}
	}
	fprintf(out, "\n");
	printDictionary(out, D);
	fprintf(out, "\n");
	for (int i = 0; i < wordCount; i++) {
		free(words[i]);
	}
	free(words);
	freeDictionary(&D);
	fclose(in);
	fclose(out);
	return 0;
}
