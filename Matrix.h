/*
*smatre@ucsc.edu
*
*List.h
*class: CSE101
*10/8/19
*
*Role: header file for List.c
*/
//-----------------------------------------------------------------------------
// List.h
// Header file for the List ADT
//-----------------------------------------------------------------------------
#ifndef _MATRIX_H_INCLUDE_
#define _MATRIX_H_INCLUDE_



// Exported type --------------------------------------------------------------

// Dictionary
typedef struct MatrixObj* Matrix;
// newMatrix()
// Returns a reference to a new nXn Matrix object in the zero state.
Matrix newMatrix(int n);
// freeMatrix()
// Frees heap memory associated with *pM, sets *pM to NULL.
void freeMatrix(Matrix* pM);
// Access functions
// size()
// Return the size of square Matrix M.
int size(Matrix M);
// NNZ()
// Return the number of non-zero elements in M.
int NNZ(Matrix M);
// changeEntry()
// Changes the ith row, jth column of M to the value x.
// Pre: 1<=i<=size(M), 1<=j<=size(M)
void changeEntry(Matrix M, int i, int j, double x);
// list of pairs "(col, val)" giving the column numbers and non-zero values
// in that row. The double val will be rounded to 1 decimal point.
void printMatrix(FILE* out, Matrix M);

// equals()
// Return true (1) if matrices A and B are equal, false (0) otherwise.
int equals(Matrix A, Matrix B);
// Manipulation procedures
// makeZero()
// Re-sets M to the zero Matrix.
void makeZero(Matrix M);

// Matrix Arithmetic operations
// copy()
// Returns a reference to a new Matrix object having the same entries as A.
Matrix copy(Matrix A);
// sum()
// Returns a reference to a new Matrix object representing A+B.
// pre: size(A)==size(B)
Matrix sum(Matrix A, Matrix B);
// diff()
// Returns a reference to a new Matrix object representing A-B.
// pre: size(A)==size(B)
Matrix diff(Matrix A, Matrix B);
// product()
// Returns a reference to a new Matrix object representing AB
// pre: size(A)==size(B)
/*
// transpose()
// Returns a reference to a new Matrix object representing the transpose
// of A.
Matrix transpose(Matrix A);
// scalarMult()
// Returns a reference to a new Matrix object representing xA.
Matrix scalarMult(double x, Matrix A);

Matrix product(Matrix A, Matrix B);
// printMatrix()
// Prints a string representation of Matrix M to filestream out. Zero rows
// are not printed. Each non-zero is represented as one line consisting
// of the row number, followed by a colon, a space, then a space separated


*/
#endif