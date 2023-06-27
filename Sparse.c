/*
==========================================
Name: Anurag Prashant Umale              =
Student Id: 1887255                      =
E-mail: aumale@ucsc.edu                  =
File: Sparse.c                       	 =
Class: CSE 101 Spring 2023               =
==========================================
*/

#include <stdio.h> // including the standard input output libray
#include <stdlib.h> // including the standard library
#include "Matrix.h" // including the matrix header file

void matrix_scalarmult(FILE *outfile,Matrix A, Matrix B){
	fprintf(outfile, "(1.5)*A =\n"); // printing the sting in outfile
	Matrix const_prod = scalarMult(1.5, A); // scalar multiplying the matrix
	printMatrix(outfile, const_prod); // printing the matrix
	fprintf(outfile, "\n"); // printing new line in the outfile
	makeZero(const_prod); // making the matrix 0
	freeMatrix(&const_prod); // freeing the matrix
}

void matrix_sum_matrix(FILE *outfile,Matrix A, Matrix B){
	fprintf(outfile, "A+B =\n"); // printing the sting in outfile
	Matrix add1 = sum(A, B); // adding the two matrix
	printMatrix(outfile, add1); // printing the matrix
	fprintf(outfile, "\n"); // printing new line in the outfile
	makeZero(add1); // making the matrix 0
	freeMatrix(&add1); // freeing the matrix
}

void matrix_sum_same(FILE *outfile,Matrix A, Matrix B){
	fprintf(outfile, "A+A =\n"); // printing the sting in outfile
	Matrix add2 = sum(A, B); // adding the same matrix
	printMatrix(outfile, add2); // printing the matrix
	fprintf(outfile, "\n"); // printing new line in the outfile
	makeZero(add2); // making the matrix 0
	freeMatrix(&add2); // freeing the matrix
}

void matrix_diff(FILE *outfile,Matrix A, Matrix B){
	fprintf(outfile, "B-A =\n"); // printing the sting in outfile
	Matrix sub1 = diff(B, A); // subtracting the matrix
	printMatrix(outfile, sub1); // printing the matrix
	fprintf(outfile, "\n"); // printing new line in the outfile
	makeZero(sub1); // making the matrix 0
	freeMatrix(&sub1); // freeing the matrix
}

void matrix_diff_same(FILE *outfile,Matrix A, Matrix B){
	fprintf(outfile, "A-A =\n"); // printing the sting in outfile
	Matrix sub2 = diff(A, B); // subtracting the same matrix
	printMatrix(outfile, sub2); // printing the matrix
	fprintf(outfile, "\n"); // printing new line in the outfile
	makeZero(sub2); // making the matrix 0
	freeMatrix(&sub2); // freeing the matrix
}

void matrix_transpose(FILE *outfile,Matrix A){
	fprintf(outfile, "Transpose(A) =\n"); // printing the sting in outfile
	Matrix tr_A = transpose(A); // making a traspose matrix
	printMatrix(outfile, tr_A); // printing the matrix
	fprintf(outfile, "\n"); // printing new line in the outfile
	makeZero(tr_A); // making the matrix 0
	freeMatrix(&tr_A); // freeing the matrix
}

void matrix_prod(FILE *outfile,Matrix A, Matrix B){
	fprintf(outfile, "A*B =\n"); // printing the sting in outfile
	Matrix prod1 = product(A, B); // taking product of two matrix
	printMatrix(outfile, prod1); // printing the matrix
	fprintf(outfile, "\n"); // printing new line in the outfile
	makeZero(prod1); // making the matrix 0
	freeMatrix(&prod1); // freeing the matrix
}

void matrix_prod_same(FILE *outfile,Matrix A, Matrix B){
	fprintf(outfile, "B*B =\n"); // printing the sting in outfile
	Matrix prod2 = product(B, B); // taking product of same matrix
	printMatrix(outfile, prod2); // printing the matrix
	makeZero(prod2); // making the matrix 0
	freeMatrix(&prod2); // freeing the matrix
}

void cleanup(FILE *in, FILE *out, Matrix A, Matrix B){
	makeZero(A); // making the matrix 0
	freeMatrix(&A); // freeing the matrix
	makeZero(B); // making the matrix 0
	freeMatrix(&B); // freeing the matrix
	fclose(in); // closing the infile
	fclose(out); // closing the outfile
}

int main(int argc, char* argv[]) { 
	if(argc != 3) { // checking if arguments are equal to 3
		fprintf(stderr, "Usage: ./Sparse <infile> <outfile>\n"); // error message
		exit(EXIT_FAILURE); // exiting in failure
	}

	FILE* in_fp = fopen(argv[1], "r"); // opening file for reading
	FILE* out_fp = fopen(argv[2], "w"); // opening file for writing

	if(in_fp == NULL || out_fp == NULL) { // checking if files are opened correctly
		fprintf(stderr, "Error: Error opening the files\n"); // error message
		exit(EXIT_FAILURE); // exiting in failure
	}

	int a = 0; // decalring the varibale for storing the total changes in matrix A
	int b = 0; // decalring the varibale for storing the total changes in matrix B
	int n = 0; // decalring the varibale for storing the size of the matrices

	fscanf(in_fp, "%d %d %d", &n, &a, &b); // scanning the infile for getting the values
	Matrix A = newMatrix(n); // creating matrix of size n
	Matrix B = newMatrix(n); // creating matrix of size n

	int row = 0; // decalring the varibale for storing the number of row
	int column = 0; // decalring the varibale for storing the number of column
	double data = 0; // decalring the varibale for storing the data

	for(int i = 0; i < a; i++) { // loop starts from 0 to the value of a
		fscanf(in_fp, "%d %d %lf", &row, &column, &data); // scanning the value from file and storing in respective variable
		changeEntry(A, row, column, data); // changing the entry according to row coloumn
	}
	for(int i = 0; i < b; i++) { // loop starts from 0 to the value of b
		fscanf(in_fp, "%d %d %lf", &row, &column, &data); // scanning the value from file and storing in respective variable
		changeEntry(B, row, column, data); // changing the entry according to row coloumn
	}
	fprintf(out_fp, "A has %d non-zero entries:\n", NNZ(A)); // printing the sting in outfile
	printMatrix(out_fp, A); // printing the matrix
	fprintf(out_fp, "\n"); // printing new line in the outfile
	fprintf(out_fp, "B has %d non-zero entries:\n", NNZ(B)); // printing the sting in outfile
	printMatrix(out_fp, B); // printing the matrix
	fprintf(out_fp, "\n"); // printing new line in the outfile
	
	matrix_scalarmult(out_fp, A, B); // calling the function for scalar multiplication
	matrix_sum_matrix(out_fp,A,B); // calling the function fir adding two matrix
	matrix_sum_same(out_fp,A,A); // calling the function for adding 2 same matrix
	matrix_diff(out_fp,A,B); // calling the function for subtracting 2 matrix
	matrix_diff_same(out_fp,A,A); // calling the function for subtracting 2 same matrix
	matrix_transpose(out_fp,A); // making a transpose of the matrix
	matrix_prod(out_fp,A,B); // taking the product on 2 matrix
	matrix_prod_same(out_fp,B,B); // taking the product of 2 same matrix
	cleanup(in_fp,out_fp,A,B); // closing files and freeing matrix
	return EXIT_SUCCESS; // returning success
}
