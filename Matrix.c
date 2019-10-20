/*
*Sonia Atre
*smatre@ucsc.edu
*
*Matrix.c
*class: CSE101
*10/11/19
*
*Role: creates a Matrix ADT used for the Matrix implementation
*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include "List.h"
#include "Matrix.h"

// Private Types and Functions ------------------------------------------------
//EntryObj type
typedef struct EntryObj {
	int column;
	double value;
} EntryObj;

typedef EntryObj* Entry;

//MatrixObj type
typedef struct MatrixObj {
	int size;
	List* entries;
	int NNZ;
} MatrixObj;

//newEntry()
//Constructor for Entry type
Entry newEntry(int c, double v) {
	Entry E = malloc(sizeof(EntryObj));
	assert(E != NULL);
	E->column = c;
	E->value = v;
	return E;
}

//clear()
//returns M to empty state
void clearM(Matrix M) {
	if (M == NULL) {
		fprintf(stderr, "Matrix Error: clearM() called on NULL Matrix reference\n");
		exit(EXIT_FAILURE);
	}
	for (int i = 0; i < size(M); i++) {
		List L = (M->entries)[i];
		clear(L);
	}
}

int isNearlyEqual(double a, double b) {
	double epsilon = 0.0001;
	if (fabs(a - b) < epsilon) {
		return 1;
	}
	return 0;
}

//freeEntry()
//Destructor for Entry type
void freeEntry(Entry* pE) {
	if (pE != NULL && *pE != NULL) {
		free(*pE);
		*pE = NULL;
	}
}

//Constructors-Destructors ------------------------------------------------

//newMatrix()
//Constructor for the List ADT
Matrix newMatrix(int n) {
	if (n < 0) {
		printf("Matrix error: cannot create matrix of size less than 0\n");
		exit(EXIT_FAILURE);
	}
	Matrix M = malloc(sizeof(MatrixObj));
	assert(M != NULL);
	M->entries = calloc(n, sizeof(List));
	M->size = n;
	return M;
}

//freeList()
//Destructor for the List ADT
void freeMatrix(Matrix* pM) {
	if (pM != NULL && *pM != NULL) {
		for (int i = 0; i < (*pM)->size; i++) {
			if ((*pM)->entries[i] != NULL) {
				//clear((*pM)->entries[i]);
				List L = (*pM)->entries[i];
				for (moveFront(L); index(L) >= 0; moveNext(L)) {
					free((Entry)get(L));
				}
				freeList(&L);
			}
		}

		free((*pM)->entries);
		free(*pM);
		*pM = NULL;
	}
}

// Access functions ------------------------------------------------
// size()
// Return the size of square Matrix M.
int size(Matrix M) {
	if (M == NULL) {
		fprintf(stderr, "Matrix Error: size() called on NULL Matrix reference\n");
		exit(EXIT_FAILURE);
	}
	return M->size;
}

// NNZ()
// Return the number of non-zero elements in M.
int NNZ(Matrix M) {
	if (M == NULL) {
		fprintf(stderr, "Matrix Error: NNZ() called on NULL Matrix reference\n");
		exit(EXIT_FAILURE);
	}
	return M->NNZ;

}
/*
// equals()
// Return true (1) if matrices A and B are equal, false (0) otherwise.
int equals(Matrix A, Matrix B) {

}
*/

// Manipulation procedures
// makeZero()
// Re-sets M to the zero Matrix.
/*
void makeZero(Matrix M) {
	clearM(M);
	for (int i = 1; i <= size(M); i++) {
		M->entries[i] = newList();
	}
}
*/
// changeEntry()
// Changes the ith row, jth column of M to the value x.
// Pre: 1<=i<=size(M), 1<=j<=size(M)

void changeEntry(Matrix M, int i, int j, double x) {
	if (M == NULL) {
		fprintf(stderr, "Matrix Error: changeEntry() called on NULL Matrix reference\n");
		exit(EXIT_FAILURE);
	}
	if (i < 1 || i > size(M)) {
		fprintf(stderr, "Invalid row size for i\n");
		exit(EXIT_FAILURE);
	}
	if (j < 1 || j > size(M)) {
		fprintf(stderr, "Invalid column size for j\n");
		exit(EXIT_FAILURE);
	}

	if (isNearlyEqual(x, 0.0) && M->entries[i - 1] == NULL) {
		return;
	}

	//if List hasn't been created yet
	if (M->entries[i - 1] == NULL) {
		M->entries[i - 1] = newList();
		Entry E = newEntry(j, x);
		append(M->entries[i - 1], E);
		return;
	}

	//see if entry already exists
	List L = M->entries[i - 1];
	for (moveFront(L); index(L) >= 0; moveNext(L)) {
		Entry E = (Entry)get(L);
		if (E->column == j) {
			if (isNearlyEqual(x, 0.0)) {
				delete(L);
			} else {
				//modify existing entry
				E->value = x;
			}
			return;
		} else if (E->column > j && !isNearlyEqual(x, 0.0)) {
			insertBefore(L, newEntry(j, x));
			return;
		}
	}

	//inserting last entry
	if (!isNearlyEqual(x, 0.0)) {
		append(L, newEntry(j, x));
	}
}



// Matrix Arithmetic operations ------------------------------------------------
/*
// copy()
// Returns a reference to a new Matrix object having the same entries as A.
Matrix copy(Matrix A) {

}
// transpose()
// Returns a reference to a new Matrix object representing the transpose
// of A.
Matrix transpose(Matrix A) {

}
// scalarMult()
// Returns a reference to a new Matrix object representing xA.
Matrix scalarMult(double x, Matrix A) {

}
// sum()
// Returns a reference to a new Matrix object representing A+B.
// pre: size(A)==size(B)
Matrix sum(Matrix A, Matrix B) {

}
// diff()
// Returns a reference to a new Matrix object representing A-B.
// pre: size(A)==size(B)
Matrix diff(Matrix A, Matrix B) {

}
// product()
// Returns a reference to a new Matrix object representing AB
// pre: size(A)==size(B)
Matrix product(Matrix A, Matrix B) {

}
*/
// printMatrix()
// Prints a string representation of Matrix M to filestream out. Zero rows
// are not printed. Each non-zero is represented as one line consisting
// of the row number, followed by a colon, a space, then a space separated
// list of pairs "(col, val)" giving the column numbers and non-zero values
// in that row. The double val will be rounded to 1 decimal point.
/*
void printMatrix(FILE* out, Matrix M) {
	if (M == NULL) {
		fprintf(stderr, "Matrix Error: printMatrix() called on NULL Matrix reference\n");
		exit(EXIT_FAILURE);
	}
	for (int i = 1; i <= size(M); i++) {
		List L = M->entries[i];
		//fprintf(out, "Index: %d, element val: %f\n", index(L), ((Entry)get(L))->value);
		if (L != NULL) {
			fprintf(out, "%d: ", i);
			moveFront(L);
			fprintf(out, "Index: %d, ", length(L));

			for (moveFront(L); index(L) >= 0; moveNext(L)) {
				Entry entry = (Entry)get(L);
				fprintf(out, "(%d, %f) ", entry->column, entry->value);

			}
		}

	}
}
*/



