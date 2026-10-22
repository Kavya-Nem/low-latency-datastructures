/***
* Kavya Nemavat
* knemavat
* 2026 Spring CSE101 PA4
* List.c
* Implementation of List ADT using a doubly linked list with cursor.
***/
#include "List.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	ListElement data;
	struct Node* next;
	struct Node* previous;
} Node;

typedef struct ListObj {
	Node* front;
	Node* back;
	Node* cursor;
	int length;
	int position;
} ListObj;

Node* newNode(ListElement data) {
	Node* N = malloc(sizeof(Node));
	if (N == NULL) {
		fprintf(stderr, "List Error: newNode(): NULL node\n");
		exit(EXIT_FAILURE);
	}
	N->data = data;
	N->next = NULL;
	N->previous = NULL;
	return N;
}

List newList() {
	List L = malloc(sizeof(ListObj));
	if (L == NULL) {
		fprintf(stderr, "List Error: newList(): NULL list\n");
		exit(EXIT_FAILURE);
	}
	L->front = L->back = L->cursor = NULL;
	L->length = 0;
	L->position = -1;
	return L;
}

void freeList(List *pL) {
	if (pL != NULL && *pL != NULL) {
		clear(*pL);
		free(*pL);
		*pL = NULL;
	}
}

int length(List L) {
	if (L == NULL) {
		fprintf(stderr, "List Error: length(): NULL list\n");
		exit(EXIT_FAILURE);
	}
	return L->length;
}

int position(List L) {
	if (L == NULL) {
		fprintf(stderr, "List Error: position(): NULL list\n");
		exit(EXIT_FAILURE);
	}
	return L->position;
}

// Pre: length()>0
ListElement front(List L) {
	if (L == NULL) {
		fprintf(stderr, "List Error: front(): NULL list\n");
		exit(EXIT_FAILURE);
	}
	if (L->length <= 0) {
		fprintf(stderr, "List Error: front(): empty list\n");
		exit(EXIT_FAILURE);
	}
	return L->front->data;
}

// Pre: length()>0
ListElement back(List L) {
	if (L == NULL) {
		fprintf(stderr, "List Error: back(): NULL list\n");
		exit(EXIT_FAILURE);
	}
	if (L->length <= 0) {
		fprintf(stderr, "List Error: back(): empty list\n");
		exit(EXIT_FAILURE);
	}
	return L->back->data;
}

//Pre: length()>0, position()>=0
ListElement get(List L) {
	if (L == NULL) {
		fprintf(stderr, "List Error: get(): NULL list\n");
		exit(EXIT_FAILURE);
	}
	if (length(L) <= 0) {
		fprintf(stderr, "List Error: get(): empty list\n");
		exit(EXIT_FAILURE);
	}
	if (position(L) < 0) {
		fprintf(stderr, "List Error: get(): undefined position\n");
		exit(EXIT_FAILURE);
	}
	return L->cursor->data;
}

void clear(List L) {
	if (L == NULL) {
		fprintf(stderr, "List Error: clear(): NULL list\n");
		exit(EXIT_FAILURE);
	}
	while (length(L) > 0) {
		deleteFront(L);
	}
}

//Pre: length()>0, position()>=0
void set(List L, ListElement x) {
	if (L == NULL) {
		fprintf(stderr, "List Error: set(): NULL list\n");
		exit(EXIT_FAILURE);
	}
	if (length(L) <= 0) {
		fprintf(stderr, "List Error: set(): empty list\n");
		exit(EXIT_FAILURE);
	}
	if (position(L) < 0) {
		fprintf(stderr, "List Error: set(): undefined position\n");
		exit(EXIT_FAILURE);
	}
	L->cursor->data = x;
}

void moveFront(List L) {
	if (L == NULL) {
		fprintf(stderr, "List Error: moveFront(): NULL list\n");
		exit(EXIT_FAILURE);
	}
	if (length(L) > 0) {
		L->cursor = L->front;
		L->position = 0;
	}
}

void moveBack(List L) {
	if (L == NULL) {
		fprintf(stderr, "List Error: moveBack(): NULL list\n");
		exit(EXIT_FAILURE);
	}
	if (length(L) > 0) {
		L->cursor = L->back;
		L->position = length(L) - 1;
	}
}

void movePrev(List L) {
	if (L == NULL) {
		fprintf(stderr, "List Error: movePrev(): NULL list\n");
		exit(EXIT_FAILURE);
	}
	if (length(L) > 0 && L->cursor != NULL) {
		L->cursor = L->cursor->previous;
		L->position--;
	}
}

void moveNext(List L) {
	if (L == NULL) {
		fprintf(stderr, "List Error: moveNext(): NULL List\n");
		exit(EXIT_FAILURE);
	}
	if (length(L) > 0 && L->cursor != NULL) {
		L->cursor = L->cursor->next;
		L->position++;
		if (position(L) == length(L)) {
			L->position = -1;
		}
	}
}

void prepend(List L, ListElement data) {
	if (L == NULL) {
		fprintf(stderr, "List Error: prepend(): NULL list\n");
		exit(EXIT_FAILURE);
	}
	Node* N = newNode(data);
	if (length(L) == 0) {
		L->front = L->back = N;
	} else {
		N->next = L->front;
		L->front->previous = N;
		L->front = N;
	}
	if (position(L) >= 0) {
		L->position++;
	}
	L->length++;
}

void append(List L, ListElement data) {
	if (L == NULL) {
		fprintf(stderr, "List Error: append(): NULL list\n");
		exit(EXIT_FAILURE);
	}
	if (length(L) == 0) {
		prepend(L, data);
	} else {
		Node* N = newNode(data);
		N->previous = L->back;
		L->back->next = N;
		L->back = N;
		L->length++;
	}
}

//Pre: length()>0, position()>=0
void insertBefore(List L, ListElement data) {
	if (L == NULL) {
		fprintf(stderr, "List Error: insertBefore(): NULL list\n");
		exit(EXIT_FAILURE);
	}
	if (length(L) <= 0) {
		fprintf(stderr, "List Error: insertBefore(): empty list\n");
		exit(EXIT_FAILURE);
	}
	if (position(L) < 0) {
		fprintf(stderr, "List Error: insertBefore(): undefined position\n");
		exit(EXIT_FAILURE);
	}
	if (L->cursor == L->front) {
		prepend(L, data);
	} else {
		Node* N = newNode(data);
		N->previous = L->cursor->previous;
		N->next = L->cursor;
		L->cursor->previous->next = N;
		L->cursor->previous = N;
		L->length++;
		L->position++;
	}
}

//Pre: length()>0, position()>=0
void insertAfter(List L, ListElement data) {
	if (L == NULL) {
		fprintf(stderr, "List Error: insertAfter(): NULL list\n");
		exit(EXIT_FAILURE);
	}
	if (length(L) <= 0) {
		fprintf(stderr, "List Error: insertAfter(): empty list\n");
		exit(EXIT_FAILURE);
	}
	if (position(L) < 0) {
		fprintf(stderr, "List Error: insertAfter(): undefined position\n");
		exit(EXIT_FAILURE);
	}
	if (L->cursor == L->back) {
		append(L, data);
	} else {
		Node* N = newNode(data);
		N->next = L->cursor->next;
		N->previous = L->cursor;
		L->cursor->next->previous = N;
		L->cursor->next = N;
		L->length++;
	}
}

// Pre: length()>0
void deleteFront(List L) {
	if (L == NULL) {
		fprintf(stderr, "List Error: deleteFront(): NULL list\n");
		exit(EXIT_FAILURE);
	}
	if (length(L) <= 0) {
		fprintf(stderr, "List Error: deleteFront(): empty list\n");
		exit(EXIT_FAILURE);
	}
	if (L->cursor == L->front) {
		L->cursor = NULL;
		L->position = -1;
	} else if (L->position > 0) {
		L->position--;
	}
	if (length(L) > 1) {
		L->front = L->front->next;
		free(L->front->previous);
		L->front->previous = NULL;
	} else {
		free(L->front);
		L->front = L->back = NULL;
	}
	L->length--;
}

// Pre: length()>0
void deleteBack(List L) {
	if (L == NULL) {
		fprintf(stderr, "List Error: deleteBack(): NULL list\n");
		exit(EXIT_FAILURE);
	}
	if (length(L) <= 0) {
		fprintf(stderr, "List Error: deleteBack(): empty list\n");
		exit(EXIT_FAILURE);
	}
	if (L->cursor == L->back) {
		L->cursor = NULL;
		L->position = -1;
	}
	if (length(L) > 1) {
		L->back = L->back->previous;
		free(L->back->next);
		L->back->next = NULL;
		L->length--;
	} else {
		deleteFront(L);
	}
}

//Pre: length()>0, position()>=0
void delete(List L) {
	if (L == NULL) {
		fprintf(stderr, "List Error: delete(): NULL list\n");
		exit(EXIT_FAILURE);
	}
	if (length(L) <= 0) {
		fprintf(stderr, "List Error: delete(): empty list\n");
		exit(EXIT_FAILURE);
	}
	if (position(L) < 0) {
		fprintf(stderr, "List Error: delete(): undefined position\n");
		exit(EXIT_FAILURE);
	}
	if (position(L) == 0) {
		deleteFront(L);
	} else if (position(L) == length(L) - 1) {
		deleteBack(L);
	} else {
		L->cursor->previous->next = L->cursor->next;
		L->cursor->next->previous = L->cursor->previous;
		free(L->cursor);
		L->cursor = NULL;
		L->position = -1;
		L->length--;
	}
}

List join(List A, List B) {
	if (A == NULL || B == NULL) {
		fprintf(stderr, "List Error: join(): NULL list(s)\n");
		exit(EXIT_FAILURE);
	}
	List C = newList();
	moveFront(A);
	while (position(A) != -1) {
		append(C, get(A));
		moveNext(A);
	}
	moveFront(B);
	while (position(B) != -1) {
		append(C, get(B));
		moveNext(B);
	}
	return C;
}

//Pre: length(L)>0, position(L)>=0
List split(List L) {
	if (L == NULL) {
		fprintf(stderr, "List Error: split(): NULL list\n");
		exit(EXIT_FAILURE);
	}
	if (length(L) <= 0) {
		fprintf(stderr, "List Error: split(): empty list\n");
		exit(EXIT_FAILURE);
	}
	if (position(L) < 0) {
		fprintf(stderr, "List Error: split(): undefined position\n");
		exit(EXIT_FAILURE);
	}
	List M = newList();
	while (L->front != L->cursor) {
		append(M, front(L));
		deleteFront(L);
	}
	return M;
}
