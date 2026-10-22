#ifndef LIST_H_INCLUDE_
#define LIST_H_INCLUDE_
#include <stdbool.h>
#include <stdio.h>
typedef void* ListElement;
typedef struct ListObj* List;
List newList();
void freeList(List *pL);
int length(List L);
int position(List L);
// Pre: length()>0
ListElement front(List L);
// Pre: length()>0
ListElement back(List L);
//Pre: length()>0, position()>=0
ListElement get(List L);
void clear(List L);
//Pre: length()>0, position()>=0
void set(List L, ListElement x);
void moveFront(List L);
void moveBack(List L);
void movePrev(List L);
void moveNext(List L);
void prepend(List L, ListElement data);
void append(List L, ListElement data);
//Pre: length()>0, position()>=0
void insertBefore(List L, ListElement data);
//Pre: length()>0, position()>=0
void insertAfter(List L, ListElement data);
// Pre: length()>0
void deleteFront(List L);
// Pre: length()>0
void deleteBack(List L);
//Pre: length()>0, position()>=0
void delete(List L);
List join(List A, List B);
//Pre: length(L)>0, position(L)>=0
List split(List L);
#endif
