//  ==========================================
//  Name: Anurag Prashant Umale              =
//  Student Id: 1887255                      =
//  E-mail: aumale@ucsc.edu                  =
//  File: Matrix.h						     =
//  Class: CSE 101 Spring 2023               =
//  ==========================================

#ifndef MATRIX__H
#define MATRIX__H

#include "List.h"

typedef struct MatrixObj *Matrix;

Matrix newMatrix(int n);

void freeMatrix(Matrix *pM);

int size(Matrix M);

int NNZ(Matrix M);

int equals(Matrix A, Matrix B);

void makeZero(Matrix M);

void changeEntry(Matrix M, int i, int j, double x);

Matrix copy(Matrix A);

Matrix transpose(Matrix A);

Matrix scalarMult(double x, Matrix A);

Matrix sum(Matrix A, Matrix B);

Matrix diff(Matrix A, Matrix B);

Matrix product(Matrix A, Matrix B);

void printMatrix(FILE *out, Matrix M);

#endif