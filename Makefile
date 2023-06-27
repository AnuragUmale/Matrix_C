# ==========================================
# Name: Anurag Prashant Umale              =
# Student Id: 1887255                      =
# E-mail: aumale@ucsc.edu                  =
# File: Makefile						   =
# Class: CSE 101 Spring 2023               =
# ==========================================

CC = gcc
CFLAGS = -std=c17 -Wall

all: ListTest MatrixTest Sparse

Sparse: Sparse.o Matrix.o List.o
	$(CC) -o $@ $^

ListTest: ListTest.o List.o
	$(CC) -o $@ $^

MatrixTest: MatrixTest.o Matrix.o List.o
	$(CC) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f ListTest MatrixTest Sparse *.o

cleanText:
	rm -f *.txt

SparseCheck:
	valgrind --leak-check=full ./Sparse in out

MatrixCheck:
	valgrind --leak-check=full ./MatrixTest

ListCheck:
	valgrind --leak-check=full ./ListTest