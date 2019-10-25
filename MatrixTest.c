//-----------------------------------------------------------------------------
//  MatrixTest.c
//  A test client for the Matrix ADT
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include"Matrix.h"

int main() {
   //int n = 100000;
   int n = 10;
   Matrix A = newMatrix(n);
   Matrix B = newMatrix(n);
   printf("Initial Size of A: %d\n", size(A));
   printf("Initial Size of B: %d\n", size(A));

   printf("Adding entries to A and B...\n");

   changeEntry(A, 1, 1, 1); changeEntry(B, 1, 1, 1);
   changeEntry(A, 1, 2, 2); changeEntry(B, 1, 2, 0);
   changeEntry(A, 1, 3, 3); changeEntry(B, 1, 3, 1);
   changeEntry(A, 2, 1, 4); changeEntry(B, 2, 1, 0);
   changeEntry(A, 2, 2, 5); changeEntry(B, 2, 2, 1);
   changeEntry(A, 2, 3, 6); changeEntry(B, 2, 3, 0);
   changeEntry(A, 3, 1, 7); changeEntry(B, 3, 1, 1);
   changeEntry(A, 3, 2, 8); changeEntry(B, 3, 2, 1);
   changeEntry(A, 3, 3, 9); changeEntry(B, 3, 3, 1);
   printf("Non-zero entries of A: %d\n", NNZ(A));
   printf("Non-zero entries of B: %d\n", NNZ(B));

   printf("Printing entries of A...\n");
   printMatrix(stdout, A);
   printf("Printing entries of B...\n");
   printMatrix(stdout, B);

   printf("Non-zero entries of A: %d\n", NNZ(A));
   printf("Non-zero entries of B: %d\n", NNZ(B));

   printf("Printing entries of A...\n");
   printMatrix(stdout, A);
   printf("Printing entries of B...\n");
   printMatrix(stdout, B);

   makeZero(B);
   printf("Non-zero entries of B: %d\n", NNZ(B));
   printf("Printing entries of B...\n");
   printMatrix(stdout, B);

   Matrix C = newMatrix(size(A));
   changeEntry(C, 2, 1, 4);
   changeEntry(C, 2, 2, 5);
   changeEntry(C, 2, 3, 6);
   changeEntry(C, 3, 1, 7);
   changeEntry(C, 3, 2, 8);
   changeEntry(C, 3, 3, 9);

   printf("Printing entries of A...\n");
   printMatrix(stdout, A);
   printf("Printing entries of C...\n");
   printMatrix(stdout, C);
   printf("Equals for A and B: %s\n", equals(A, B) ? "true" : "false" );

   printf("Copying A to H\n");
   //Matrix H = copy(A);
   printf("%d\n", NNZ(H));
   //printMatrix(stdout, H);
   printf("Equals for A and H: %s\n", equals(A, H) ? "true" : "false" );

   printf("\n");

   printf("Adding Matrix A and C\n");
   Matrix D = sum(A, C);
   printf("%d\n", NNZ(D));
   printMatrix(stdout, D);
   printf("\n");

   // printf("Subtracting A and C\n");
   // Matrix E = diff(A, A);
   // printf("%d\n", NNZ(E));
   // printMatrix(stdout, E);
   // printf("\n");
   /*
   //Matrix C, D, E, F, G, H;
   //printf("Size A: %d, Size B: %d\n", size(A), size(B));

   printf("%d\n", NNZ(A));
   printMatrix(stdout, A);
   printf("\n");

   printf("%d\n", NNZ(B));
   printMatrix(stdout, B);
   printf("\n");

   C = scalarMult(1.5, A);
   printf("%d\n", NNZ(C));
   printMatrix(stdout, C);
   printf("\n");

   D = sum(A, B);
   printf("%d\n", NNZ(D));
   printMatrix(stdout, D);
   printf("\n");

   E = diff(A, A);
   printf("%d\n", NNZ(E));
   printMatrix(stdout, E);
   printf("\n");

   F = transpose(B);
   printf("%d\n", NNZ(F));
   printMatrix(stdout, F);
   printf("\n");

   G = product(B, B);
   printf("%d\n", NNZ(G));
   printMatrix(stdout, G);
   printf("\n");

   H = copy(A);
   printf("%d\n", NNZ(H));
   printMatrix(stdout, H);
   printf("\n");

   printf("%s\n", equals(A, H)?"true":"false" );
   printf("%s\n", equals(A, B)?"true":"false" );
   printf("%s\n", equals(A, A)?"true":"false" );

   makeZero(A);
   printf("%d\n", NNZ(A));
   printMatrix(stdout, A);
   */
   freeMatrix(&A);
   freeMatrix(&B);
   freeMatrix(&C);
   //freeMatrix(&H);
   freeMatrix(&D);
   //freeMatrix(&E);

   /*
   freeMatrix(&C);
   freeMatrix(&D);
   freeMatrix(&E);
   freeMatrix(&F);
   freeMatrix(&G);
   freeMatrix(&H);
   */

   return EXIT_SUCCESS;
}
