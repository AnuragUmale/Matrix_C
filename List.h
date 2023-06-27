//  ==========================================
//  Name: Anurag Prashant Umale              =
//  Student Id: 1887255                      =
//  E-mail: aumale@ucsc.edu                  =
//  File: Matrix.c (Matrix ADT) 		     =
//  Class: CSE 101 Spring 2023               =
//  ==========================================
#ifndef LIST_H_INCLUDE_
#define LIST_H_INCLUDE_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct ListObj *List;

List newList(void);
void freeList(List *pL);

int length(List L);
int index(List L);
void *front(List L);
void *back(List L);
void *get(List L);

void clear(List L);
void set(List L, void *x);
void moveFront(List L);
void moveBack(List L);
void movePrev(List L);

void moveNext(List L);

void prepend(List L, void *x);

void append(List L, void *x);

void insertBefore(List L, void *x);
void insertAfter(List L, void *x);
void deleteFront(List L);
void deleteBack(List L);
void delete(List L);

void printList(FILE *out, List L);

List copyList(List L);

#endif