# Programming Assignment 4 - Matrix ADT and Its Operations

The file **Matrix.c** has implementation of the **Matrix** Data Structure with help of **List** ADT.

## Files In The Repository

1. List.c
2. Matrix.c
3. Matrix.h
4. Sparse.c
5. List.h
6. ListTest.c
7. Makefile
8. README.md
9. MatrixTest.c


# Make commands

```
$ make clean
```

This command will make the repository clean by deleting the object file and executable file of **MatrixTest.c**, **ListTest.c**, **Sparse.c** and **Matrix.c**.


```
$ make
```

This command will just compile other C files and make the executable and object file for **MatrixTest.c**,and  **ListTest.c**

## Running the program

```
$ make
```

1. This command will just compile and make the executable and object file for **MatrixTest.c**,and  **ListTest.c**

```
$ ./MatrixTest
```

2. This command will run the GraphTest file and show the output of Graph ADT functions.

```
$ ./Sparse <input file> <output file>
```

3. This command will run FindPath.c and it takes **2** arguments.

## Valgrind Check

```
$ make
```

1. This command will just compile and make the executable and object file for **ListTest.c** and **MatrixTest.c**.

```
$ make ListCheck
```

2. This command will show all the possible memory leaks in **ListTest.c**.

```
$ make MatrixCheck
```

3. This command will show all the possible memory leaks in **MatrixTest.c**.


```
$ make SparseChcek
```

4. This command will show all the possible memory leaks in **Sparse.c** (default: infile = input.txt outfile = output.txt)
