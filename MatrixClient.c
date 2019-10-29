//-----------------------------------------------------------------------------
//  MatrixClient.c
//  A test client for the Matrix ADT
//  https://classes.soe.ucsc.edu/cmps101/Summer19/pa2.pdf
//-----------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <time.h>
#include "Matrix.h"

// See https://stackoverflow.com/questions/5248915/execution-time-of-c-program
#define TICK(X) clock_t X = clock()
#define TOCK(X) printf("Elapsed time %s: %g sec\n", (#X), (double)(clock() - (X)) / CLOCKS_PER_SEC)

// Private function of Matrix, useful for testing
double getValue(Matrix M, int i, int j);

int equal(double d1, double d2) {
   // Return non-zero if d1 and d2 are approximately equal
   double epsilon = 0.000001;
   return fabs(d1 - d2) < epsilon;
}

int main() {
   TICK(overall);
   int n = 100000;

   // size and NNZ
   //
   Matrix A = newMatrix(n);

   printf("size(A) = %d\n", size(A));
   assert(size(A) == n);
   printf("NNZ(A) = %d\n", NNZ(A));
   assert(NNZ(A) == 0);

   // changeEntry
   //
   printf("Adding 4 entries to A...\n");
   changeEntry(A, 1, 1, 1.234);
   changeEntry(A, 1, 3, 3.0);
   changeEntry(A, 1, 2, 2.0);
   changeEntry(A, 100, 102, 6.0);
   printf("A:\n");
   printMatrix(stdout, A);
   changeEntry(A, 1, 1, 1.111);  // Update an existing entry
   changeEntry(A, 1, 1, 5.0);  // Update an existing entry again
   assert(equal(getValue(A, 1, 1), 5.00));
   printf("A:\n");
   printMatrix(stdout, A);

   printf("NNZ(A) = %d\n", NNZ(A));
   assert(NNZ(A) == 4);

   // scalarMult
   //
   printf("C = scalarMult(1.5, A)...\n");
   Matrix C = scalarMult(1.5, A);
   printf("NNZ(C) = %d\n", NNZ(C));
   assert(NNZ(C) == 4);
   assert(equal(getValue(C, 1, 3), 4.50));
   printf("C:\n");
   printMatrix(stdout, C);

   printf("O = scalarMult(0.0, A)...\n");
   Matrix O = scalarMult(0.0, A);
   printf("NNZ(O) = %d\n", NNZ(O));
   assert(NNZ(O) == 0);
   assert(equal(getValue(O, 1, 3), 0.0));
   printf("O:\n");
   printMatrix(stdout, O);

   // makeZero
   //
   printf("Calling makeZero(A)...\n");
   makeZero(A);
   printf("NNZ(A) = %d\n", NNZ(A));
   printf("A:\n");
   printMatrix(stdout, A);

   Matrix B = newMatrix(n);
   changeEntry(A, 1,1,1); changeEntry(B, 1,1,1);
   changeEntry(A, 1,2,2); changeEntry(B, 1,2,0);
   changeEntry(A, 1,3,3); changeEntry(B, 1,3,1);
   changeEntry(A, 2,1,4); changeEntry(B, 2,1,0);
   changeEntry(A, 2,2,5); changeEntry(B, 2,2,1);
   changeEntry(A, 2,3,6); changeEntry(B, 2,3,0);
   changeEntry(A, 3,1,7); changeEntry(B, 3,1,1);
   changeEntry(A, 3,2,8); changeEntry(B, 3,2,1);
   changeEntry(A, 3,3,9); changeEntry(B, 3,3,1);
   changeEntry(A, 3,10,11);
   changeEntry(B, 3,9,10);

   changeEntry(B, 3,1,0);  // Change an existing entry to 0
   assert(NNZ(B) == 6);

   printf("NNZ(A) = %d\n", NNZ(A));
   printf("A:\n");
   printMatrix(stdout, A);
   printf("A[1, 1] = %f\n", getValue(A, 1, 1));
   printf("A[3, 3] = %f\n", getValue(A, 3, 3));
   printf("A[1, 100] = %f\n", getValue(A, 1, 100));

   printf("NNZ(B) = %d\n", NNZ(B));
   printf("B:\n");
   printMatrix(stdout, B);

   // sum, diff
   //
   printf("D = sum(A, B):\n");
   Matrix D = sum(A, B);
   printMatrix(stdout, D);
   assert(equal(getValue(D, 1, 3), 4.00));
   assert(equal(getValue(D, 3, 3), 10.00));
   assert(equal(getValue(D, 3, 9), 10.00));
   assert(equal(getValue(D, 3, 10), 11.00));

   printf("E = diff(A, B):\n");
   Matrix E = diff(A, B);
   printMatrix(stdout, E);
   assert(equal(getValue(E, 1, 1), 0.00));
   assert(equal(getValue(E, 1, 3), 2.00));
   assert(equal(getValue(E, 3, 3), 8.00));
   assert(equal(getValue(E, 3, 9), -10.00));
   assert(equal(getValue(E, 3, 10), 11.00));
   assert(NNZ(E) == 10);

   printf("F = diff(A, A):\n");
   Matrix F = diff(A, A);
   printMatrix(stdout, F);
   assert(NNZ(F) == 0);

   // transpose
   //
   changeEntry(B, 1, 3, 1.3);
   changeEntry(B, 2, 2, 2.2);
   changeEntry(B, 3, 2, 3.2);
   changeEntry(B, 3, 3, 3.3);
   Matrix G = transpose(B);
   assert(NNZ(G) == NNZ(B));
   printf("B:\n");
   printMatrix(stdout, B);
   printf("G = transpose(B):\n");
   printMatrix(stdout, G);
   // Assert all the non-zero values of G
   assert(equal(getValue(G, 1, 1), 1.0));
   assert(equal(getValue(G, 2, 2), 2.2));
   assert(equal(getValue(G, 2, 3), 3.2));
   assert(equal(getValue(G, 3, 1), 1.3));
   assert(equal(getValue(G, 3, 3), 3.3));
   assert(equal(getValue(G, 9, 3), 10.0));

   // product
   //
   Matrix H = newMatrix(n);
   changeEntry(H, 1, 1, 1.0);
   changeEntry(H, 1, 2, 2.0);
   changeEntry(H, 1, 3, 3.0);
   changeEntry(H, 2, 1, 4.0);
   changeEntry(H, 2, 2, 5.0);
   changeEntry(H, 2, 3, 6.0);
   changeEntry(H, 3, 1, 7.0);
   changeEntry(H, 3, 2, 8.0);
   changeEntry(H, 3, 3, 9.0);
   printf("H:\n");
   printMatrix(stdout, H);
   assert(NNZ(H) == 9);

   Matrix J = newMatrix(n);
   changeEntry(J, 1, 1, 1.0);
   changeEntry(J, 1, 3, 1.0);
   changeEntry(J, 3, 1, 1.0);
   changeEntry(J, 3, 2, 1.0);
   changeEntry(J, 3, 3, 1.0);
   printf("J:\n");
   printMatrix(stdout, J);
   assert(NNZ(J) == 5);

   Matrix K = product(H, J);
   printf("K = product(H, J):\n");
   printMatrix(stdout, K);
   assert(NNZ(K) == 9);
   // Assert all the non-zero values of K
   /*
   K=H*J =
   1: (1, 4.0) (2, 3.0) (3, 4.0)
   2: (1, 10.0) (2, 6.0) (3, 10.0)
   3: (1, 16.0) (2, 9.0) (3, 16.0)
   */
   assert(equal(getValue(K, 1, 1), 4.0));
   assert(equal(getValue(K, 1, 2), 3.0));
   assert(equal(getValue(K, 1, 3), 4.0));
   assert(equal(getValue(K, 2, 1), 10.0));
   assert(equal(getValue(K, 2, 2), 6.0));
   assert(equal(getValue(K, 2, 3), 10.0));
   assert(equal(getValue(K, 3, 1), 16.0));
   assert(equal(getValue(K, 3, 2), 9.0));
   assert(equal(getValue(K, 3, 3), 16.0));

   // copy and equals
   //
   Matrix L = copy(A);
   assert(NNZ(L) == NNZ(A));
   printf("L (copy of A):\n");
   printMatrix(stdout, L);
   printf("A:\n");
   printMatrix(stdout, A);

   printf("A == L? %s\n", equals(A, L) ? "true" : "false" );
   printf("A == B? %s\n", equals(A, B) ? "true" : "false" );
   printf("K == K? %s\n", equals(K, K) ? "true" : "false" );

   assert(equals(A, L));
   assert(!equals(A, B));
   assert(equals(A, A));

   makeZero(A);
   assert(NNZ(A) == 0);

   // equals
   //
   Matrix M = newMatrix(n);
   Matrix N = newMatrix(n);
   changeEntry(M, 1, 1, 1.0); changeEntry(N, 1, 1, 1.0);
   changeEntry(M, 1, 2, 2.0); changeEntry(N, 1, 2, 3.0);
   printf("M == N? %s\n", equals(M, N) ? "true" : "false" );
   assert(!equals(M, N));

   /*
   G = product(B, B);
   printf("%d\n", NNZ(G));
   printMatrix(stdout, G);
   */
   freeMatrix(&A);
   freeMatrix(&B);
   freeMatrix(&C);
   freeMatrix(&D);
   freeMatrix(&E);
   freeMatrix(&F);
   freeMatrix(&G);
   freeMatrix(&H);
   freeMatrix(&J);
   freeMatrix(&K);
   freeMatrix(&L);
   freeMatrix(&M);
   freeMatrix(&N);
   freeMatrix(&O);

   printf("---------------------------------------\n");
   printf("Done: All assertions succeeded!\n");
   TOCK(overall);
   printf("---------------------------------------\n");

   return EXIT_SUCCESS;
}

