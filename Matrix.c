/*
*Sonia Atre
*smatre@ucsc.edu
*
*Matrix.c
*class: CSE101
*10/28/19
*
*Role: creates a Matrix ADT used for the Matrix implementation
*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include "List.h"
#include "Matrix.h"

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
//getEntry()
//returns Entry at specific row, col (i, j)
Entry getEntry(Matrix M, int i, int j) {
	if (i < 0 || i > size(M)) {
		fprintf(stderr, "Invalid row size for i\n");
		exit(EXIT_FAILURE);
	}
	if (j < 0 || j > size(M)) {
		fprintf(stderr, "Invalid column size for j\n");
		exit(EXIT_FAILURE);
	}
	List L = M->entries[i - 1];
	if (length(L) == 0) {
		return NULL;
	}
	for (moveFront(L); index(L) >= 0; moveNext(L)) {
		Entry E = (Entry)get(L);
		if (E->column == j) {
			return E;
		}
	}
	return NULL;
}

double vectorDot(List A, List B) {
	double sum = 0;
	moveFront(A);
	moveFront(B);
	while (index(A) >= 0 && index(B) >= 0) {
		Entry entryA = (Entry)get(A);
		Entry entryB = (Entry)get(B);
		if (entryA->column == entryB->column) {
			sum += (entryA->value * entryB->value);
			//printf("sum: %d\n", sum);
			moveNext(A);
			moveNext(B);
		} else if (entryA->column < entryB->column) {
			moveNext(A);
		} else {
			moveNext(B);
		}
	}
	return sum;
}

double getValue(Matrix M, int i, int j) {
	Entry entry = getEntry(M, i, j);
	return entry ? entry->value : 0.0;
}

Matrix sumOrDiff(Matrix A, Matrix B, int sum) {
	char* op = sum ? "sum" : "diff";
	if (A == NULL) {
		printf("Matrix error: Calling %s on NULL Matrix reference A\n", op);
		exit(1);
	}
	if (B == NULL) {
		printf("Matrix error: Calling %s on NULL Matrix reference B\n", op);
		exit(1);
	}
	if (size(A) != size(B)) {
		printf("Matrix error: Calling %s on matrices of different sizes\n", op);
		exit(1);
	}
	Matrix C = newMatrix(size(A));
	for (int i = 0; i < size(A); i++) {
		List rowA = A->entries[i];
		if (length(rowA) == 0) {
			continue;
		}
		for (moveFront(rowA); index(rowA) >= 0; moveNext(rowA)) {
			Entry X = (Entry)get(rowA);
			//Entry Y = getEntry(B, i + 1, X->column);
			double result = sum ? X->value + getValue(B, i + 1, X->column) : X->value - getValue(B, i + 1, X->column);
			if (result != 0) {
				append(C->entries[i], newEntry(X->column, result));
				C->NNZ++;
			}

		}

	}
	for (int i = 0; i < size(B); i++) {
		List rowB = B->entries[i];
		if (length(rowB) == 0) {
			continue;
		}
		for (moveFront(rowB); index(rowB) >= 0; moveNext(rowB)) {
			Entry X = (Entry)get(rowB);
			Entry Y = getEntry(A, i + 1, X->column);
			if (Y == NULL) {
				double result = sum ? X->value : -1 * X->value;
				if (result != 0) {
					changeEntry(C, i + 1, X->column, result);
					//append(C->entries[i], newEntry(X->column, result));
					//C->NNZ++;

				}
			}

		}

	}
	return C;
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
	for (int i = 0; i < n; i++) {
		M->entries[i] = newList();
	}
	assert(M != NULL);

	M->size = n;
	M->NNZ = 0;
	return M;
}

//freeList()
//Destructor for the List ADT
void freeMatrix(Matrix * pM) {
	if (pM != NULL && *pM != NULL) {
		for (int i = 0; i < (*pM)->size; i++) {
			if ((*pM)->entries[i] != NULL) {
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

//equals()
//Return true (1) if matrices A and B are equal, false (0) otherwise.
int equals(Matrix A, Matrix B) {
	if (A == NULL) {
		fprintf(stderr, "Matrix Error: equals() called on NULL Matrix A reference\n");
		exit(EXIT_FAILURE);
	}
	if (B == NULL) {
		fprintf(stderr, "Matrix Error: equals() called on NULL Matrix B reference\n");
		exit(EXIT_FAILURE);
	}

	//check lengths
	if (A->size != B->size) {
		//printf("Going in size\n");
		return 0;
	}
	//check NNZ
	if (A->NNZ != B->NNZ) {
		return 0;
	}
	for (int i = 0; i < A->size; i++) {
		List rowA = A->entries[i];
		List rowB = B->entries[i];
		moveFront(rowA);
		moveFront(rowB);
		if ((length(rowA) == 0 && length(rowB) != 0) || (length(rowA) != 0 && length(rowB) == 0)) {
			return 0;
		}
		while (index(rowA) != -1 && index(rowB) != -1) {
			Entry entryA = (Entry)get(rowA);
			Entry entryB = (Entry)get(rowB);
			if (!isNearlyEqual(entryA->value, entryB->value) ) {
				return 0;
			}
			moveNext(rowA);
			moveNext(rowB);
		}

	}
	return 1;
}

// // equals()
// // Return true (1) if matrices A and B are equal, false (0) otherwise.
// int equals(Matrix A, Matrix B) {
// 	if (A == NULL) {
// 		fprintf(stderr, "Matrix Error: equals() called on NULL Matrix A reference\n");
// 		exit(EXIT_FAILURE);
// 	}
// 	if (B == NULL) {
// 		fprintf(stderr, "Matrix Error: equals() called on NULL Matrix B reference\n");
// 		exit(EXIT_FAILURE);
// 	}

// 	//check lengths
// 	if (A->size != B->size) {
// 		return 0;
// 	}
// 	//check NNZ
// 	if (A->NNZ != B->NNZ) {
// 		return 0;
// 	}

// 	for (int i = 0; i < A->size; i++) {
// 		//creating list variable with i
// 		//loop to go through list
// 		//put if statements inside loop
// 		List rowA = A->entries[i];
// 		List rowB = B->entries[i];
// 		if (rowA == NULL && rowB == NULL) {
// 			continue;
// 		}
// 		//either rowA or rowB is null, but not both
// 		if ((rowA == NULL && rowB != NULL) || (rowB == NULL && rowA != NULL)) {
// 			return 0;
// 		}

// 		if (length(rowA) != length(rowB)) {
// 			return 0;
// 		}
// 		//both rows not null -> compare values
// 		for (moveFront(rowA); index(rowA) >= 0; moveNext(rowA)) {
// 			Entry E = (Entry)get(rowA);
// 			int j = E->column;

// 			//getEntry: returns null if list is null or no entry at col j
// 			Entry X = (Entry)get(rowA);
// 			Entry Y = getEntry(B, i + 1, j);

// 			//if no entry exists at column j, entry values don't match
// 			if ((Y == NULL) || (Y != NULL && (X->value != Y->value))) {
// 				return 0;
// 			}
// 		}
// 	}
// 	return 1;
// }

// Manipulation procedures
// makeZero()
// Re-sets M to the zero Matrix.
void makeZero(Matrix M) {
	if (M == NULL) {
		fprintf(stderr, "Matrix Error: makeZero() called on NULL Matrix reference\n");
		exit(EXIT_FAILURE);
	}
	for (int i = 0; i < size(M); i++) {
		List L = (M->entries)[i];
		if (length(L) > 0) {
			//first clear Entry ob that each node's data points to
			for (moveFront(L); index(L) >= 0; moveNext(L)) {
				free((Entry)get(L));
			}
			clear(L);

		}
	}
	M->NNZ = 0;
}

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

	if (isNearlyEqual(x, 0.0) && length(M->entries[i - 1]) == 0) {
		return;
	}

	//if List hasn't been created yet
	if (length(M->entries[i - 1]) == 0) {
		//Entry E = newEntry(j, x);
		if (!isNearlyEqual(x, 0)) {
			append(M->entries[i - 1], newEntry(j, x));
			M->NNZ++;
		}
		return;
	}

	//see if entry already exists
	List L = M->entries[i - 1];
	for (moveFront(L); index(L) >= 0; moveNext(L)) {
		Entry E = (Entry)get(L);
		if (E->column == j) {
			if (isNearlyEqual(x, 0.0)) {
				M->NNZ--;
				delete(L);
				freeEntry(&E);
			} else {
				//modify existing entry
				E->value = x;
			}
			return;
		} else if (E->column > j && !isNearlyEqual(x, 0.0)) {
			insertBefore(L, newEntry(j, x));
			M->NNZ++;
			return;
		}
	}

	//inserting last entry
	if (!isNearlyEqual(x, 0.0)) {
		append(L, newEntry(j, x));
		M->NNZ++;
	}
}



// Matrix Arithmetic operations ------------------------------------------------

// copy()
// Returns a reference to a new Matrix object having the same entries as A.
Matrix copy(Matrix A) {
	if (A == NULL) {
		fprintf(stderr, "Matrix Error: copy() called on NULL Matrix reference\n");
		exit(EXIT_FAILURE);
	}
	Matrix B = newMatrix(size(A));

	for (int i = 0; i < size(A); i++) {
		List rowA = A->entries[i];
		List rowB = B->entries[i];
		if (length(rowA) != 0) {
			for (moveFront(rowA); index(rowA) >= 0; moveNext(rowA)) {
				Entry E = (Entry)get(rowA);
				append(rowB, newEntry(E->column, E->value));
			}
		}
	}

	B->NNZ = A->NNZ;
	return B;
}
// sum()
// Returns a reference to a new Matrix object representing A+B.
// pre: size(A)==size(B)
Matrix sum(Matrix A, Matrix B) {
	return sumOrDiff(A, B, 1);
}

// diff()
// Returns a reference to a new Matrix object representing A-B.
// pre: size(A)==size(B)
Matrix diff(Matrix A, Matrix B) {
	return sumOrDiff(A, B, 0);
}

// transpose()
// Returns a reference to a new Matrix object representing the transpose
// of A.
Matrix transpose(Matrix A) {
	if (A == NULL) {
		fprintf(stderr, "Matrix Error: transpose() called on NULL Matrix reference\n");
		exit(EXIT_FAILURE);
	}
	Matrix B = newMatrix(size(A));
	B->NNZ = A->NNZ;
	for (int i = 0; i < size(A); i++) {
		List rowA = A->entries[i];
		if (length(rowA) != 0) {
			for (moveFront(rowA); index(rowA) >= 0; moveNext(rowA)) {
				Entry entryA = (Entry)get(rowA);
				Entry entryB = newEntry(i + 1, entryA->value);
				List rowB = B->entries[entryA->column - 1];
				append(rowB, entryB);
			}
		}

	}

	return B;
}

// scalarMult()
// Returns a reference to a new Matrix object representing xA.
Matrix scalarMult(double x, Matrix A) {
	if (A == NULL) {
		fprintf(stderr, "Matrix Error: scalarMult() called on NULL Matrix A reference\n");
		exit(EXIT_FAILURE);
	}
	Matrix M = newMatrix(size(A));
	if (isNearlyEqual(x, 0.0)) {
		return M;
	}

	M->NNZ = A->NNZ;
	for (int i = 0; i < size(A); i++) {
		List rowA = A->entries[i];
		if (length(rowA) != 0) {
			for (moveFront(rowA); index(rowA) >= 0; moveNext(rowA)) {
				Entry E = (Entry)get(rowA);
				append(M->entries[i], newEntry(E->column, E->value * x));
			}
		}

	}
	return M;
}

// product()
// Returns a reference to a new Matrix object representing AB
// pre: size(A)==size(B)
Matrix product(Matrix A, Matrix B) {
	if (A == NULL) {
		fprintf(stderr, "Matrix Error: product() called on NULL Matrix A reference\n");
		exit(EXIT_FAILURE);
	}
	if (B == NULL) {
		fprintf(stderr, "Matrix Error: product() called on NULL Matrix B reference\n");
		exit(EXIT_FAILURE);
	}
	//check lengths
	if (A->size != B->size) {
		fprintf(stderr, "Cannot multiply matrixes of different lengths\n");
		exit(EXIT_FAILURE);
	}
	Matrix C = newMatrix(size(A));
	Matrix D = transpose(B);

	for (int i = 0; i < size(A); i++) {

		List rowA = A->entries[i];
		if (length(rowA) != 0) {
			for (int j = 0; j < size(D); j++) {
				List rowD = D->entries[j];
				if (length(rowD) != 0) {
					List rowD = D->entries[j];
					double val = vectorDot(rowA, rowD);
					if (!isNearlyEqual(val, 0.0)) {
						append(C->entries[i], newEntry(j + 1, val));
						C->NNZ++;
					}
				}
				//printf("i: %d, j: %d\n", i, j);
				//List rowC = C->entries[j];

			}
			//printf("i: %d,length rowD: %d\n", i, length(rowD));

		}

	}
	freeMatrix(&D);
	return C;
}
/*

// scalarMult()
// Returns a reference to a new Matrix object representing xA.
Matrix scalarMult(double x, Matrix A) {

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

void printMatrix(FILE* out, Matrix M) {
	if (M == NULL) {
		fprintf(stderr, "Matrix Error: printMatrix() called on NULL Matrix reference\n");
		exit(EXIT_FAILURE);
	}
	for (int i = 0; i < size(M); i++) {
		List L = M->entries[i];
		//fprintf(out, "Index: %d, element val: %f\n", index(L), ((Entry)get(L))->value);
		if (length(L) != 0) {
			fprintf(out, "%d: ", i + 1);
			for (moveFront(L); index(L) >= 0; moveNext(L)) {
				Entry entry = (Entry)get(L);
				fprintf(out, "(%d, %.1f) ", entry->column, entry->value);
			}
			fprintf(out, "\n");
		}

	}
}







