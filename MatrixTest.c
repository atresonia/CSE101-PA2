/*
*Sonia Atre
*smatre@ucsc.edu
*
*MatrixTest.c
*class: CSE101
*10/28/19
*
*Role: acts as client for creates a Matrix ADT 
*/

//-----------------------------------------------------------------------------
//  MatrixTest.c
//  A test client for the Matrix ADT
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include"Matrix.h"

int main() {
   // Matrix A = newMatrix(3);
   // Matrix B = newMatrix(3);
   // printf("Adding  entries to A\n");

   // changeEntry(A, 1, 1, 1);
   // changeEntry(A, 1, 2, 2);
   // changeEntry(A, 1, 3, 3);
   // changeEntry(A, 2, 1, 4);
   // changeEntry(A, 2, 2, 5);
   // changeEntry(A, 2, 3, 6);
   // changeEntry(A, 3, 1, 7);
   // changeEntry(A, 3, 2, 8);
   // changeEntry(A, 3, 3, 9);
   // printMatrix(stdout, A);

   // //printf("Adding two entries to B\n");
   // printf("Adding  entries to B\n");
   // changeEntry(B, 1, 1, 1);
   // changeEntry(B, 1, 3, 1);
   // changeEntry(B, 3, 1, 1);
   // changeEntry(B, 3, 2, 1);
   // changeEntry(B, 3, 3, 1);
   // printMatrix(stdout, B);
   // printf("Computing diff of B-A\n");

   // Matrix C = diff(B, A);
   // printMatrix(stdout, C);

   //int n = 3;
   //int n = 3;
   // Matrix A = newMatrix(15);
   // Matrix B = newMatrix(15);
   // printf("Initial Size of A: %d\n", size(A));
   // printf("Initial Size of B: %d\n", size(A));

   // printf("Adding entries to A and B...\n");
   // freeMatrix(&B);

   // Matrix C = newMatrix(15);
   // changeEntry(A, 1, 1, 1);
   // changeEntry(C, 1, 1, 1);
   // //if (equals(A, C)) return 1;
   // B = newMatrix(15);
   // changeEntry(A, 1, 1, 1);
   // changeEntry(A, 1, 3, 1);
   // changeEntry(B, 1, 1, 1);
   // changeEntry(B, 1, 3, 1);
   // printMatrix(stdout, A);
   // printMatrix(stdout, B);
   // printf("Equals for A and B: %s\n", equals(A, B) ? "true" : "false" );
   // //if (!equals(A, B)) return 2;
   // changeEntry(A, 1, 3, 0);
   // //failing
   // printMatrix(stdout, A);
   // printMatrix(stdout, B);
   // printf("Equals for A and B: %s\n", equals(A, B) ? "true" : "false" );
   // //if (equals(A, B)) return 3;


   // // changeEntry(A, 1, 1, 0);

   // freeMatrix(&A);
   // freeMatrix(&B);
   // freeMatrix(&C);

   // changeEntry(A, 2, 1, 2);
   // changeEntry(A, 3, 1, 5);
   // changeEntry(A, 1, 2, 2);
   // changeEntry(A, 1, 3, 5);
   // changeEntry(A, 1, 1, 4);
   // changeEntry(A, 2, 2, 2);
   // changeEntry(A, 2, 5, 0);
   // changeEntry(A, 2, 3, 0);
   // changeEntry(A, 3, 3, 5);
   // if (NNZ(A) != 7) return 1;
   // changeEntry(A, 1, 3, 0);
   // changeEntry(A, 3, 1, 0);
   // changeEntry(A, 3, 3, 0);
   // //failing
   // printf("NNZ(A): %d\n", NNZ(A));
   // //if (NNZ(A) != 4) return 2;
   // changeEntry(A, 7, 6, 42);
   // changeEntry(A, 10, 1, 24);
   // if (NNZ(A) != 6) return 3;
   // freeMatrix(&A);

   // makeZero(B);
   // changeEntry(A, 10, 10, 10);
   // changeEntry(B, 10, 10, 10);
   // int n = 100;
   // Matrix A = newMatrix(n);
   // Matrix B = newMatrix(n);
   // changeEntry(A, 1, 1, 1);
   // changeEntry(A, 1, 2, 2);
   // changeEntry(A, 1, 3, 3);
   // changeEntry(A, 2, 1, 4);
   // changeEntry(A, 2, 2, 5);
   // changeEntry(A, 2, 3, 6);
   // changeEntry(A, 3, 1, 7);
   // changeEntry(A, 3, 2, 8);
   // changeEntry(A, 3, 3, 9);
   // changeEntry(B, 1, 1, 1);
   // changeEntry(B, 2, 2, 1);
   // Matrix T = product(A, B);
   // printMatrix(stdout, A);
   // printMatrix(stdout, B);
   // printf("NNZ(T): %d\n", NNZ(T));
   // printMatrix(stdout, T);
   // freeMatrix(&T);
   // freeMatrix(&A);
   // freeMatrix(&B);
   int n = 100000;
   Matrix A = newMatrix(n);
   Matrix B = newMatrix(n);
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

   makeZero(A);
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

   printf("Printing transpose of B\n");
   Matrix F = transpose(B);
   printf("%d\n", NNZ(F));
   printMatrix(stdout, F);
   printf("\n");

   printf("Copying B to H\n");
   Matrix H = copy(B);
   printf("%d\n", NNZ(H));
   printMatrix(stdout, H);
   printf("Equals for B and H: %s\n", equals(B, H) ? "true" : "false" );


   // printf("Subtracting A and C\n");
   // Matrix E = diff(A, A);
   // printf("%d\n", NNZ(E));
   // printMatrix(stdout, E);
   // printf("\n");

   printf("Multiplying Matrix B and B\n");
   printf("\n");
   Matrix G = product(B, B);
   printf("%d\n", NNZ(G));
   printMatrix(stdout, G);
   printf("\n");

   printf("Adding Matrix A and C\n");
   Matrix D = sum(A, C);
   printf("%d\n", NNZ(D));
   printMatrix(stdout, D);
   printf("\n");

   printf("Scalar multiplication of X by 1.5\n");
   Matrix X = scalarMult(1.5, C);
   printf("%d\n", NNZ(X));
   printMatrix(stdout, X);
   printf("\n");

   printf("Scalar multiplication of Y by 0\n");
   Matrix Y = scalarMult(0, C);
   printf("%d\n", NNZ(Y));
   printMatrix(stdout, Y);
   printf("\n");

   freeMatrix(&A);
   freeMatrix(&B);
   freeMatrix(&C);
   freeMatrix(&F);
   freeMatrix(&H);
   freeMatrix(&G);
   freeMatrix(&X);
   freeMatrix(&Y);
   freeMatrix(&D);

   // printf("Adding Matrix A and B\n");
   // Matrix D = sum(A, B);
   // printf("%d\n", NNZ(D));
   // printMatrix(stdout, D);
   // printf("\n");

   // Matrix G = product(B, B);
   // printf("%d\n", NNZ(G));
   // printMatrix(stdout, G);
   // printf("\n");

   // printf("Subtracting A and C\n");
   // Matrix E = diff(A, A);
   // printf("%d\n", NNZ(E));
   // printMatrix(stdout, E);
   // printf("\n");

   // // printf("\n");
   // // Matrix G = product(B, B);
   // // printf("%d\n", NNZ(G));
   // // printMatrix(stdout, G);
   // // printf("\n");

   // // printf("Adding Matrix A and C\n");
   // // Matrix D = sum(A, C);
   // // printf("%d\n", NNZ(D));
   // // printMatrix(stdout, D);
   // // printf("\n");

   // // printf("Subtracting A and C\n");
   // // Matrix E = diff(A, A);
   // // printf("%d\n", NNZ(E));
   // // printMatrix(stdout, E);
   // // printf("\n");
   // /*
   // //Matrix C, D, E, F, G, H;
   // //printf("Size A: %d, Size B: %d\n", size(A), size(B));

   // printf("%d\n", NNZ(A));
   // printMatrix(stdout, A);
   // printf("\n");

   // printf("%d\n", NNZ(B));
   // printMatrix(stdout, B);
   // printf("\n");

   // C = scalarMult(1.5, A);
   // printf("%d\n", NNZ(C));
   // printMatrix(stdout, C);
   // printf("\n");

   // D = sum(A, B);
   // printf("%d\n", NNZ(D));
   // printMatrix(stdout, D);
   // printf("\n");

   // E = diff(A, A);
   // printf("%d\n", NNZ(E));
   // printMatrix(stdout, E);
   // printf("\n");

   // F = transpose(B);
   // printf("%d\n", NNZ(F));
   // printMatrix(stdout, F);
   // printf("\n");

   // G = product(B, B);
   // printf("%d\n", NNZ(G));
   // printMatrix(stdout, G);
   // printf("\n");

   // H = copy(A);
   // printf("%d\n", NNZ(H));
   // printMatrix(stdout, H);
   // printf("\n");

   // printf("%s\n", equals(A, H)?"true":"false" );
   // printf("%s\n", equals(A, B)?"true":"false" );
   // printf("%s\n", equals(A, A)?"true":"false" );

   // makeZero(A);
   // printf("%d\n", NNZ(A));
   // printMatrix(stdout, A);
   // */
   // freeMatrix(&A);
   // freeMatrix(&B);
   // freeMatrix(&C);
   // freeMatrix(&F);
   // freeMatrix(&H);
   // freeMatrix(&G);
   // freeMatrix(&X);
   // freeMatrix(&D);

   // //freeMatrix(&G);

   // //freeMatrix(&E);


   // /*
   // freeMatrix(&C);
   // freeMatrix(&D);
   // freeMatrix(&E);
   // freeMatrix(&F);
   // freeMatrix(&G);
   // freeMatrix(&H);
   // */

   return EXIT_SUCCESS;
}