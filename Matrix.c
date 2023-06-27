//  ==========================================
//  Name: Anurag Prashant Umale              =
//  Student Id: 1887255                      =
//  E-mail: aumale@ucsc.edu                  =
//  File: Matrix.c (Matrix ADT) 		     =
//  Class: CSE 101 Spring 2023               =
//  ==========================================
#include <stdio.h> // include the standard input and output header file
#include <stdlib.h> // include the standard library
#include "Matrix.h" // include the matrix header file

typedef struct EntryObj *Entry; // type casting the struct pointer

typedef struct EntryObj
{
    int column; // column value
    double data; // data 
} EntryObj;

typedef struct MatrixObj
{
    List *row; // array of lists
    int size; // size of the matrix
    int NNZ; // Non-Zero entries
} MatrixObj;

Entry newEntry(double data, int column)
{
    Entry entry = (Entry)malloc(sizeof(EntryObj)); // Dynamically allocating memory
    if (entry) // checking if the pointer is not equal to NULL
    {
        entry->data = data; // setting the data of the structure to the data
        if (column < 1) // checking if column is less than 1
        {
            fprintf(stderr, "1. Matrix Error.\n2. Entry newEntry(double data, int column).\n3. Column value is less than 0.\n"); // Error Message
            exit(EXIT_FAILURE); // exiting in failure
        }
        entry->column = column; // setting the column to column
        return entry; // returning the entry
    }
    else
    {
        fprintf(stderr, "1. Matrix Error.\n2. Entry newEntry(double data, int column).\n3. Error in allocating the memory.\n"); // Error Message
        exit(EXIT_FAILURE); // exiting in failure
    }
}

void freeEntry(Entry *pE)
{
    if (pE != NULL && *pE != NULL) // checking if pointer and pointer to pointer is not equal NULL
    {
        free(*pE);
        *pE = NULL;
    }
}

Matrix newMatrix(int n)
{
    if (n < 1)
    {
        fprintf(stderr, "1. Matrix Error.\n2. Matrix newMatrix(int n).\n3. Error invalid size of the Matrix.\n"); // Error Message
        exit(EXIT_FAILURE); // exiting in failure
    }
    Matrix new_matrix = (Matrix)malloc(sizeof(MatrixObj)); // Dynamically allocating memory
    if (new_matrix) // checking if the pointer is not equal to NULL
    {
        new_matrix->row = (List *)calloc(n + 1, sizeof(List));
        if (new_matrix->row == NULL) // checking if the pointer is equal to NULL
        {
            fprintf(stderr, "1. Matrix Error.\n2. Matrix newMatrix(int n).\n3. Error in allocating the memory.\n"); // Error Message
            exit(EXIT_FAILURE); // exiting in failure
        }
        new_matrix->size = n;
        new_matrix->NNZ = 0;
        for (int i = 1; i <= n; i++)
        {
            new_matrix->row[i] = newList();
        }
        return new_matrix;
    }
    else
    {
        fprintf(stderr, "1. Matrix Error.\n2. Matrix newMatrix(int n).\n3. Error in allocating the memory.\n"); // Error Message
        exit(EXIT_FAILURE); // exiting in failure
    }
}


void freeMatrix(Matrix *pM)
{
    if (pM != NULL && *pM != NULL)
    {
        for (int i = 1; i <= size(*pM); i++)
        {
            List element = (*pM)->row[i];
            for (moveFront(element); index(element) >= 0; moveNext(element))
            {
                Entry E = get(element);
                Entry temp = E;
                freeEntry(&temp);

                E = NULL;
                set(element, NULL);
            }
            freeList(&((*pM)->row[i]));
        }
        free((*pM)->row);
        (*pM)->row = NULL;
        free(*pM);
        *pM = NULL;
    }
}

int size(Matrix M)
{
    if (M) // checking if the pointer is not equal to NULL
    {
        return M->size;
    }
    else
    {
        fprintf(stderr, "1. Matrix Error.\n2. size(Matrix M).\n3. Calling function on Null pointer.\n"); // Error Message
        exit(EXIT_FAILURE); // exiting in failure
    }
}

int NNZ(Matrix M)
{
    if (M) // checking if the pointer is not equal to NULL
    {
        return M->NNZ;
    }
    else
    {
        fprintf(stderr, "1. Matrix Error.\n2. NNZ(Matrix M).\n3. Calling function on Null pointer.\n"); // Error Message
        exit(EXIT_FAILURE); // exiting in failure
    }
}

int equals(Matrix A, Matrix B)
{
    if (A && B) // checking if the pointer is not equal to NULL
    {
        if (A->size != B->size || A->NNZ != B->NNZ)
        {
            return 0;
        }
        for (int i = 1; i <= size(A); i++)
        {
            if (length(A->row[i]) != length(B->row[i]))
            {
                return 0;
            }
            for (moveFront(A->row[i]), moveFront(B->row[i]); index(A->row[i]) >= 0 && index(B->row[i]) >= 0; moveNext(A->row[i]), moveNext(B->row[i]))
            {
                Entry Ae = get(A->row[i]);
                Entry Be = get(B->row[i]);
                if (Ae->column != Be->column || Ae->data != Be->data)
                {
                    return 0;
                }
            }
        }
        return 1;
    }
    else
    {
        fprintf(stderr, "1. Matrix Error.\n2. equals(Matrix A, Matrix B).\n3. Calling function on Null pointer.\n"); // Error Message
        exit(EXIT_FAILURE); // exiting in failure
    }
}

void makeZero(Matrix M)
{
    if (M) // checking if the pointer is not equal to NULL
    {
        M->NNZ = 0;
        for (int i = 1; i <= size(M); i++)
        {
            List row = M->row[i];
            for (moveFront(row); index(row) >= 0; moveNext(row))
            {
                Entry e = (Entry)get(row);
                freeEntry(&e);
            }
            clear(row);
        }
    }
    else
    {
        fprintf(stderr, "1. Matrix Error.\n2. makeZero(Matrix M).\n3. Calling function on Null pointer.\n"); // Error Message
        exit(EXIT_FAILURE); // exiting in failure
    }
}

void changeEntry(Matrix M, int i, int j, double x)
{
    if (M) // checking if the pointer is not equal to NULL
    {
        if (i < 1 || i > size(M) || j < 1 || j > size(M))
        {
            fprintf(stderr, "1. Matrix Error.\n2. changeEntry(Matrix M, int i, int j, double x).\n3. Calling function on Invalid Index.\n"); // Error Message
            exit(EXIT_FAILURE);
        }
        List row = M->row[i];
        moveFront(row);
        Entry E = NULL;
        while (index(row) >= 0 && ((Entry)get(row))->column < j)
        {
            moveNext(row);
        }
        if (index(row) >= 0 && ((Entry)get(row))->column == j)
        {
            E = (Entry)get(row);
            if (x == 0)
            {
                delete (row);
                M->NNZ--;
                freeEntry(&E);
            }
            else
            {
                E->data = x;
            }
        }
        else if (x != 0)
        {
            E = malloc(sizeof(EntryObj));
            E->column = j;
            E->data = x;
            if (index(row) < 0)
                append(row, E);
            else
                insertBefore(row, E);
            M->NNZ++;
        }
    }
    else
    {
        fprintf(stderr, "1. Matrix Error.\n2. changeEntry(Matrix M, int i, int j, double x).\n3. Calling function on Null pointer.\n"); // Error Message
        exit(EXIT_FAILURE); // exiting in failure
    }
}

Matrix copy(Matrix A)
{
    if (A) // checking if the pointer is not equal to NULL
    {
        Matrix copy_matrix = newMatrix(size(A));

        for (int i = 1; i <= size(A); i++)
        {
            List element = A->row[i];
            for (moveFront(element); index(element) >= 0; moveNext(element))
            {
                Entry E = (Entry)get((A->row)[i]);
                append((copy_matrix->row)[i], newEntry(E->data, E->column));
                copy_matrix->NNZ++;
            }
        }
        copy_matrix->NNZ = A->NNZ;
        return copy_matrix;
    }
    else
    {
        fprintf(stderr, "1. Matrix Error.\n2. copy(Matrix A).\n3. Calling function on Null pointer.\n"); // Error Message
        exit(EXIT_FAILURE); // exiting in failure
    }
}

Matrix transpose(Matrix A)
{
    if (A) // checking if the pointer is not equal to NULL
    {
        Matrix transpose_matrix = newMatrix(size(A));

        for (int i = 1; i <= size(A); i++)
        {
            List element = A->row[i];
            for (moveFront(element); index(element) >= 0; moveNext(element))
            {
                Entry E = (Entry)get((A->row)[i]);
                append((transpose_matrix->row)[E->column], newEntry(E->data, i));
                transpose_matrix->NNZ++;
            }
        }
        transpose_matrix->NNZ = A->NNZ;
        return transpose_matrix;
    }
    else
    {
        fprintf(stderr, "1. Matrix Error.\n2. transpose(Matrix A).\n3. Calling function on Null pointer.\n"); // Error Message
        exit(EXIT_FAILURE); // exiting in failure
    }
}

Matrix scalarMult(double x, Matrix A)
{
    if (A)  // checking if the pointer is not equal to NULL
    {
        Matrix scaler_mult_matrix = newMatrix(size(A));

        for (int i = 1; i <= size(A); i++)
        {
            List element = A->row[i];
            for (moveFront(element); index(element) >= 0; moveNext(element))
            {
                Entry E = (Entry)get((A->row)[i]);
                append((scaler_mult_matrix->row)[i], newEntry(x * E->data, E->column));
                scaler_mult_matrix->NNZ++;
            }
        }

        return scaler_mult_matrix;
    }
    else
    {
        fprintf(stderr, "1. Matrix Error.\n2. scalarMult(double x, Matrix A).\n3. Calling function on Null pointer.\n"); // Error Message
        exit(EXIT_FAILURE); // exiting in failure
    }
}

Matrix sum(Matrix A, Matrix B)
{
    if (A && B) // checking if the pointer is not equal to NULL
    {
        if (size(A) != size(B))
        {
            fprintf(stderr, "1. Matrix Error.\n2. Matrix sum(Matrix A, Matrix B).\n3. Error matrices are not equal.\n"); // Error Message
            exit(EXIT_FAILURE); // exiting in failure
        }

        if (equals(A, B))
        {
            return scalarMult(2, A);
        }

        Matrix sum_matrix = newMatrix(size(A));
        for (int i = 1; i <= size(A); i++)
        {
            int j = 0;
            for (moveFront(A->row[i]), moveFront(B->row[i]);
                 index(A->row[i]) >= 0 || index(B->row[i]) >= 0;)
            {
                Entry a = (index(A->row[i]) >= 0) ? (Entry)get(A->row[i]) : NULL;
                Entry b = (index(B->row[i]) >= 0) ? (Entry)get(B->row[i]) : NULL;
                if (A == NULL && B == NULL)
                    break;
                if (a != NULL && b != NULL && a->column == b->column)
                {
                    double sum = a->data + b->data;
                    if (sum != 0)
                    {
                        Entry e = newEntry(sum, a->column);
                        append(sum_matrix->row[i], e);
                        j++;
                    }
                    moveNext(A->row[i]);
                    moveNext(B->row[i]);
                }
                else if (b == NULL || (a != NULL && a->column < b->column))
                {
                    Entry e = newEntry(a->data, a->column);
                    append(sum_matrix->row[i], e);
                    j++;
                    moveNext(A->row[i]);
                }
                else
                {
                    Entry e = newEntry(b->data, b->column);
                    append(sum_matrix->row[i], e);
                    j++;
                    moveNext(B->row[i]);
                }
            }
            sum_matrix->NNZ += j;
        }
        return sum_matrix;
    }
    else
    {
        fprintf(stderr, "1. Matrix Error.\n2. Matrix sum(Matrix A, Matrix B).\n3. Error calling function on NULL pointer.\n"); // Error Message
        exit(EXIT_FAILURE); // exiting in failure
    }
}

Matrix diff(Matrix A, Matrix B)
{

    if (A && B) // checking if the pointer is not equal to NULL
    {
        if (size(A) != size(B))
        {
            fprintf(stderr, "1. Matrix Error.\n2. Matrix diff(Matrix A, Matrix B).\n3. Error matrices are not equal.\n"); // Error Message
            exit(EXIT_FAILURE); // exiting in failure
        }

        if (equals(A, B))
        {
            return newMatrix(size(A));
        }
        Matrix diff_matrix = newMatrix(size(A));

        for (int i = 1; i <= size(A); i++)
        {
            moveFront(A->row[i]);
            moveFront(B->row[i]);

            for (int j = 0; j < length(A->row[i]) + length(B->row[i]); j++)
            {
                if (index(A->row[i]) >= 0 && index(B->row[i]) >= 0)
                {
                    Entry ae = (Entry)get(A->row[i]);
                    Entry be = (Entry)get(B->row[i]);

                    if (ae->column == be->column)
                    {
                        double diff = ae->data - be->data;
                        if (diff != 0)
                        {
                            append(diff_matrix->row[i], newEntry(diff, ae->column));
                            diff_matrix->NNZ++;
                        }
                        moveNext(A->row[i]);
                        moveNext(B->row[i]);
                    }
                    else if (ae->column < be->column)
                    {
                        append(diff_matrix->row[i], newEntry(ae->data, ae->column));
                        diff_matrix->NNZ++;
                        moveNext(A->row[i]);
                    }
                    else
                    {
                        append(diff_matrix->row[i], newEntry(-1 * be->data, be->column));
                        diff_matrix->NNZ++;
                        moveNext(B->row[i]);
                    }
                }
                else if (index(A->row[i]) >= 0)
                {
                    Entry ae = (Entry)get(A->row[i]);
                    append(diff_matrix->row[i], newEntry(ae->data, ae->column));
                    diff_matrix->NNZ++;
                    moveNext(A->row[i]);
                }
                else if (index(B->row[i]) >= 0)
                {
                    Entry be = (Entry)get(B->row[i]);
                    append(diff_matrix->row[i], newEntry(-1 * be->data, be->column));
                    diff_matrix->NNZ++;
                    moveNext(B->row[i]);
                }
            }
        }
        return diff_matrix;
    }
    else
    {
        fprintf(stderr,"1. Matrix Error.\n2. Matrix diff(Matrix A, Matrix B).\n 3. Error calling function Null pointer"); // Error Message
        exit(EXIT_FAILURE); // exiting in failure
    }
}

double vectorDot(List P, List Q)
{
    double sum = 0;
    moveFront(P);
    moveFront(Q);
    while (index(P) >= 0 && index(Q) >= 0)
    {
        Entry e1 = (Entry)get(P);
        Entry e2 = (Entry)get(Q);
        if (e1->column == e2->column)
        {
            sum += (e1->data * e2->data);
            moveNext(P);
            moveNext(Q);
        }
        else if (e1->column < e2->column)
            moveNext(P);
        else
            moveNext(Q);
    }
    return sum;
}

Matrix product(Matrix A, Matrix B)
{
    if(A && B)// checking if the pointer is not equal to NULL
    {
        Matrix transpose_matrix = transpose(B);
        Matrix product_matrix = newMatrix(size(A));
        for (int i = 1; i <= size(product_matrix); i++)
        {
            if (length(A->row[i]) == 0)
            {
                continue;
            }
            else
            {
                for (int j = 1; j <= size(product_matrix); j++)
                {
                    if (length(transpose_matrix->row[j]) != 0)
                    {
                        double p = vectorDot(A->row[i], transpose_matrix->row[j]);
                        if (p != 0)
                        {
                            Entry e = newEntry(p, j);
                            append(product_matrix->row[i], e);
                            product_matrix->NNZ += 1;
                        }
                    }
                }
            }
        }
        freeMatrix(&transpose_matrix);
        return product_matrix;
    }
    else
    {
        fprintf(stderr,"1. Matrix Error.\n2. Matrix product(Matrix A, Matrix B).\n 3. Error calling function Null pointer"); // Error Message
        exit(EXIT_FAILURE); // exiting in failure
    }
}

void printMatrix(FILE *out, Matrix M)
{
    if (M) // checking if the pointer is not equal to NULL
    {
        for (int i = 1; i <= size(M); i++)
        {
            if (length(M->row[i]) != 0)
            {
                fprintf(out, "%i:", i);
                for (moveFront((M->row)[i]); index((M->row)[i]) >= 0; moveNext((M->row)[i]))
                {
                    Entry E = (Entry)get((M->row)[i]);
                    fprintf(out, " (%i, %.1lf)", E->column, E->data);
                }
                fprintf(out, "\n");
            }
        }
    }
    else
    {
        fprintf(stderr,"1. Matrix Error.\n2. Matrix print.\n 3. Error calling function Null pointer"); // Error Message
        exit(EXIT_FAILURE); // exiting in failure
    }
}