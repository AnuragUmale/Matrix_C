//  ==========================================
//  Name: Anurag Prashant Umale              =
//  Student Id: 1887255                      =
//  E-mail: aumale@ucsc.edu                  =
//  File: List.c (List ADT) 		     =
//  Class: CSE 101 Spring 2023               =
//  ==========================================
#include <stdlib.h>
#include "List.h"

typedef struct NodeObj *Node;

typedef struct NodeObj
{
    void *data;
    Node prev;
    Node next;
} NodeObj;

typedef struct ListObj
{
    Node front;
    Node cursor;
    Node back;
    int index;
    int length;
} ListObj;

Node newNode(void *data)
{
    Node new_node = (Node)malloc(sizeof(NodeObj));
    if (new_node)
    {
        new_node->data = data;
        new_node->prev = NULL;
        new_node->next = NULL;
        return new_node;
    }
    else
    {
        fprintf(stderr, "1. List Error.\n 2. Node newNode(void *data).\n3. Error allocating memory.\n");
        exit(EXIT_FAILURE);
    }
}

void freeNode(Node *pN)
{
    if (pN != NULL && *pN != NULL)
    {
        free(*pN);
        *pN = NULL;
    }
}

List newList(void)
{
    List L = (List)malloc(sizeof(ListObj));
    if (L != NULL)
    {
        L->front = NULL;
        L->cursor = NULL;
        L->back = NULL;
        L->index = -1;
        L->length = 0;
        return L;
    }
    else
    {
        fprintf(stderr, "1. List Error.\n 2. List newList(void).\n3. Error allocating memory.\n");
        exit(EXIT_FAILURE);
    }
}

void freeList(List *pL)
{
    if (pL != NULL && *pL != NULL)
    {
        while (length(*pL) != 0)
        {
            deleteFront(*pL);
        }
        free(*pL);
        *pL = NULL;
    }
}

int length(List L)
{
    if (L)
    {
        return L->length;
    }
    else
    {
        fprintf(stderr, "1. List Error.\n 2. int length(List L).\n3. Error calling function on NULL pointer.\n");
        exit(EXIT_FAILURE);
    }
}

int index(List L)
{
    if (L)
    {
        if (L->cursor == NULL)
        {
            return -1;
        }
        return L->index;
    }
    else
    {
        fprintf(stderr, "1. List Error.\n 2. int index(List L).\n3. Error calling function on NULL pointer.\n");
        exit(EXIT_FAILURE);
    }
}

void *front(List L)
{
    if (L)
    {
        if (L->length == 0)
        {
            fprintf(stderr, "1. List Error.\n2. void *front(List L).\n 3. Error calling function on empty list.\n");
            exit(EXIT_FAILURE);
        }
        return L->front->data;
    }
    else
    {
        fprintf(stderr, "1. List Error.\n 2. void *front(List L).\n3. Error calling function on NULL pointer.\n");
        exit(EXIT_FAILURE);
    }
}

void *back(List L)
{
    if (L)
    {
        if (L->length == 0)
        {
            fprintf(stderr, "1. List Error.\n2. void *back(List L).\n3. Error calling function on empty list.\n");
            exit(EXIT_FAILURE);
        }
        return L->back->data;
    }
    else
    {
        fprintf(stderr, "1. List Error.\n 2. void *back(List L).\n3. Error calling function on NULL pointer.\n");
        exit(EXIT_FAILURE);
    }
}

void *get(List L)
{
    if (L)
    {
        if (L->cursor == NULL)
        {
            fprintf(stderr, "1. List Error.\n 2. void *get(List L).\n3. Error the cursor is undefined.\n");
            exit(EXIT_FAILURE);
        }
        if (L->length == 0)
        {
            fprintf(stderr, "1. List Error.\n2. void *get(List L).\n 3. Error calling function on empty list.\n");
            exit(EXIT_FAILURE);
        }
        if (L->index < 0)
        {
            fprintf(stderr, "1. List Error.\n2. void *get(List L).\n 3. Error the index is undefined.\n");
            exit(EXIT_FAILURE);
        }
        return L->cursor->data;
    }
    else
    {
        fprintf(stderr, "1. List Error.\n 2. void *get(List L).\n3. Error calling function on NULL pointer.\n");
        exit(EXIT_FAILURE);
    }
}

void clear(List L)
{
    if (L)
    {
        while (L->length > 0)
        {
            deleteFront(L);
        }
        L->front = L->cursor = L->back = NULL;
        L->index = -1;
        L->length = 0;
    }
    else
    {
        fprintf(stderr, "1. List Error.\n 2. void clear(List L).\n3. Error calling function on NULL pointer.\n");
        exit(EXIT_FAILURE);
    }
}

void set(List L, void *x)
{
    if (L)
    {
        if (L->length == 0)
        {
            fprintf(stderr, "1. List Error.\n2. void set(List L, void *x).\n 3. Error calling function on empty list.\n");
            exit(EXIT_FAILURE);
        }
        if (L->index < 0)
        {
            fprintf(stderr, "1. List Error.\n2. void set(List L, void *x).\n 3. Error the index is undefined.\n");
            exit(EXIT_FAILURE);
        }
        L->cursor->data = x;
    }
    else
    {
        fprintf(stderr, "1. List Error.\n 2. void set(List L, void *x).\n3. Error calling function on NULL pointer.\n");
        exit(EXIT_FAILURE);
    }
}

void moveFront(List L)
{
    if (L)
    {
        if (L->length > 0)
        {
            L->cursor = L->front;
            L->index = 0;
        }
    }
    else
    {
        fprintf(stderr, "1. List Error.\n 2. void moveFront(List L).\n3. Error calling function on NULL pointer.\n");
        exit(EXIT_FAILURE);
    }
}

void moveBack(List L)
{
    if (L)
    {

        if (L->length > 0)
        {
            L->cursor = L->back;
            L->index = L->length - 1;
        }
    }
    else
    {
        fprintf(stderr, "1. List Error.\n 2. void moveBack(List L).\n3. Error calling function on NULL pointer.\n");
        exit(EXIT_FAILURE);
    }
}

void movePrev(List L)
{
    if (L)
    {
        if (L->cursor != NULL && L->cursor == L->front)
        {
            L->cursor = NULL;
            L->index = -1;
        }
        else if (L->cursor != NULL)
        {
            L->cursor = L->cursor->prev;
            L->index--;
        }
    }
    else
    {
        fprintf(stderr, "1. List Error.\n 2. void movePrev(List L).\n3. Error calling function on NULL pointer.\n");
        exit(EXIT_FAILURE);
    }
}

void moveNext(List L)
{
    if (L)
    {
        if (L->cursor != NULL && L->cursor == L->back)
        {
            L->cursor = NULL;
            L->index = -1;
        }
        else if (L->cursor != NULL)
        {
            L->cursor = L->cursor->next;
            L->index++;
        }
    }
    else
    {
        fprintf(stderr, "1. List Error.\n 2. void moveNext(List L).\n3. Error calling function on NULL pointer.\n");
        exit(EXIT_FAILURE);
    }
}

void prepend(List L, void *x)
{
    if (L)
    {
        Node new = newNode(x);
        if (L->length == 0)
        {
            L->front = L->back = new;
            L->length++;
        }
        else if (L->length >= 1)
        {
            new->next = L->front;
            L->front->prev = new;
            L->front = new;
            if (L->cursor != NULL)
            {
                L->index++;
            }
            L->length++;
        }
    }
    else
    {
        fprintf(stderr, "1. List Error.\n 2. void prepend(List L, void *x).\n3. Error calling function on NULL pointer.\n");
        exit(EXIT_FAILURE);
    }
}

void append(List L, void *x)
{
    if (L)
    {
        Node new = newNode(x);
        if (L->length == 0)
        {
            L->front = L->back = new;
            L->length++;
        }
        else if (L->length >= 1)
        {
            new->prev = L->back;
            L->back->next = new;
            L->back = new;
            L->length++;
        }
    }
    else
    {
        fprintf(stderr, "1. List Error.\n 2. void append(List L, void *x).\n3. Error calling function on NULL pointer.\n");
        exit(EXIT_FAILURE);
    }
}

void insertBefore(List L, void *x)
{
    if (L)
    {
        if (L->length == 0)
        {
            fprintf(stderr, "1. List Error.\n2. void insertBefore(List L, void *x).\n 3. Error calling function on empty list.\n");
            exit(EXIT_FAILURE);
        }
        if (L->index < 0)
        {
            fprintf(stderr, "1. List Error.\n2. void insertBefore(List L, void *x).\n 3. Error the index is undefined.\n");
            exit(EXIT_FAILURE);
        }
        if (L->cursor != NULL)
        {
            Node N = newNode(x);
            N->prev = L->cursor->prev;
            L->cursor->prev = N;
            N->next = L->cursor;
            if (L->cursor == L->front)
            {
                L->front = N;
            }
            else if (N->prev != NULL && L->cursor != L->front)
            {
                N->prev->next = N;
            }
            L->index++;
            L->length++;
        }
    }
    else
    {
        fprintf(stderr, "1. List Error.\n 2. void insertBefore(List L, void *x).\n3. Error calling function on NULL pointer.\n");
        exit(EXIT_FAILURE);
    }
}

void insertAfter(List L, void *x)
{
    if (L)
    {
        if (L->length == 0)
        {
            fprintf(stderr, "1. List Error.\n2. void insertAfter(List L, void *x).\n 3. Error calling function on empty list.\n");
            exit(EXIT_FAILURE);
        }
        if (L->index < 0)
        {
            fprintf(stderr, "1. List Error.\n2. void insertAfter(List L, void *x).\n 3. Error the index is undefined.\n");
            exit(EXIT_FAILURE);
        }
        if (L->cursor != NULL)
        {
            Node N = newNode(x);
            if (L->cursor == L->back)
            {
                N->prev = L->back;
                L->back->next = N;
                L->back = N;
            }
            else
            {
                N->next = L->cursor->next;
                N->prev = L->cursor;
                L->cursor->next = N;
            }
            L->length++;
        }
    }
    else
    {
        fprintf(stderr, "1. List Error.\n 2. void insertAfter(List L, void *x).\n3. Error calling function on NULL pointer.\n");
        exit(EXIT_FAILURE);
    }
}

void deleteFront(List L)
{
    if (L)
    {

        if (L->length == 0)
        {
            fprintf(stderr, "1. List Error.\n2. void deleteFront(List L).\n3. Error the list is empty.\n");
            exit(EXIT_FAILURE);
        }
        Node N = NULL;
        if (L->length > 1)
        {
            N = L->front;
            L->front = L->front->next;
            freeNode(&N);
            L->front->prev = NULL;
            if (L->cursor != NULL)
            {
                L->index--;
            }
            else if (L->index == 0)
            {
                L->cursor = NULL;
                L->index = -1;
            }
        }
        else if (L->length == 1)
        {
            freeNode(&L->front);
            L->front = L->back = L->cursor = NULL;
            L->index = -1;
        }
        L->length--;
    }
    else
    {
        fprintf(stderr, "1. List Error.\n 2. void deleteFront(List L).\n3. Error calling function on NULL pointer.\n");
        exit(EXIT_FAILURE);
    }
}

void deleteBack(List L)
{
    if (L)
    {
        if (L->length == 0)
        {
            fprintf(stderr, "1. List Error.\n2. void deleteBack(List L).\n3. Error calling function on empty list\n");
            exit(EXIT_FAILURE);
        }
        Node N = NULL;
        if (L->length > 1)
        {
            N = L->back;
            if (L->cursor == L->back)
            {
                L->cursor = NULL;
                L->index = -1;
            }
            L->back = L->back->prev;
            freeNode(&N);
            L->back->next = NULL;
            L->length--;
        }
        else if (L->length == 1)
        {
            freeNode(&L->front);
            L->back = L->front = L->cursor = NULL;
            L->index = -1;
            L->length = 0;
        }
    }
    else
    {
        fprintf(stderr, "1. List Error.\n 2. void deleteBack(List L).\n3. Error calling function on NULL pointer.\n");
        exit(EXIT_FAILURE);
    }
}

void delete(List L)
{
    if (L)
    {
        if (L->length == 0)
        {
            fprintf(stderr, "1. List Error.\n2. void delete(List L).\n3. Error calling function on empty list\n");
        }
        if (L->index < 0)
        {
            fprintf(stderr, "1. List Error.\n2. void delete(List L).\n3. Error the index is undefined.\n");
            exit(EXIT_FAILURE);
        }
        if (L->length == 1)
        {
            freeNode(&L->front);
            L->front = L->back = NULL;
        }
        else if (L->front == L->cursor)
        {
            L->front = L->front->next;
            freeNode(&L->cursor);
            L->front->prev = NULL;
        }
        else if (L->back == L->cursor)
        {
            L->back = L->back->prev;
            freeNode(&L->cursor);
            L->back->next = NULL;
        }
        else
        {
            L->cursor->prev->next = L->cursor->next;
            L->cursor->next->prev = L->cursor->prev;
            freeNode(&L->cursor);
        }
        L->index = -1;
        L->length--;
    }
    else
    {
        fprintf(stderr, "1. List Error.\n 2. void delete(List L).\n3. Error calling function on NULL pointer.\n");
        exit(EXIT_FAILURE);
    }
}

void printList(FILE *out, List L)
{
    if (L)
    {
        Node N = NULL;
        for (N = L->front; N != NULL; N = N->next)
        {
            fprintf(out, "%p ", N->data);
        }
    }
    else
    {
        fprintf(stderr, "1. List Error.\n 2. void printList(FILE *out, List L).\n3. Error calling function on NULL pointer.\n");
        exit(EXIT_FAILURE);
    }
}

List copyList(List L)
{
    if (L)
    {
        List copy = newList();
        moveFront(L);
        while (index(L) != -1)
        {
            append(copy, get(L));
            moveNext(L);
        }
        return copy;
    }
    else
    {
        fprintf(stderr, "1. List Error.\n 2. List copyList(List L).\n3. Error calling function on NULL pointer.\n");
        exit(EXIT_FAILURE);
    }
}