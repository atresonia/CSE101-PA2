/*
*Sonia Atre
*smatre@ucsc.edu
*
*Sparse.c
*class: CSE101
*10/28/19
*
*Role: serves as main function of program
*/
#include <stdio.h>
#include<stdlib.h>
#define USAGE_MSG "Usage: Sparse <input file> <output file>\n"
#include"Matrix.h"
#define BUFFER_SIZE 128

void printNNZ(Matrix M, FILE* output, char letter, int NNZ) {
	fprintf(output, "%c has %d non-zero entries:\n", letter, NNZ);
	printMatrix(output, M);
	fprintf(output, "\n");
}

void printScalar(Matrix M, FILE* output, double scale, char letter) {
	fprintf(output, "(%0.1f)*%c = \n", scale, letter);
	Matrix A = scalarMult(scale, M);
	printMatrix(output, A);
	freeMatrix(&A);
	fprintf(output, "\n");
}

void printSum(Matrix M, FILE* output, Matrix N, char letter1, char letter2) {
	fprintf(output, "%c+%c = \n", letter1, letter2);
	Matrix A = sum(M, N);
	printMatrix(output, A);
	freeMatrix(&A);
	fprintf(output, "\n");
}

void printDiff(Matrix M, FILE* output, Matrix N, char letter1, char letter2) {
	fprintf(output, "%c-%c = \n", letter1, letter2);
	Matrix A = diff(M, N);
	printMatrix(output, A);
	freeMatrix(&A);
	fprintf(output, "\n");
}

void printTranspose(Matrix M, FILE* output, char letter1) {
	fprintf(output, "Transpose(%c) = \n", letter1);
	Matrix A = transpose(M);
	printMatrix(output, A);
	freeMatrix(&A);
	fprintf(output, "\n");
}

void printProduct(Matrix M, FILE* output, Matrix N, char letter1, char letter2) {
	fprintf(output, "%c*%c = \n", letter1, letter2);
	Matrix A = product(M, N);
	printMatrix(output, A);
	freeMatrix(&A);
	fprintf(output, "\n");
}

int main(int argc, char const *argv[]) {
	if (argc != 3) {
		fprintf(stderr, USAGE_MSG);
		return EXIT_FAILURE;
	}

	FILE* in = fopen(argv[1], "r");
	//attempts to open input file and write to output file, if no success, throw error
	if (in == NULL) {
		printf("Could not read file %s\n", argv[1]);
		return EXIT_FAILURE;
	}
	FILE* out = fopen(argv[2], "w");
	if (out == NULL) {
		printf("Could not write to file %s\n", argv[2]);
		fclose(in);
		return EXIT_FAILURE;
	}
	char line[BUFFER_SIZE];
	int size, NNZ1, NNZ2, read;
	int row, col;
	double doubVal;
	int i = 0;
	int blank = 0;
	Matrix A, B;

	while (fgets(line, sizeof(line),  in)) {
		if (i == 0) {
			printf("Going to allocate mem\n");
			read = sscanf(line, "%d %d %d\n", &size, &NNZ1, &NNZ2);
			A = newMatrix(size);
			B = newMatrix(size);

		} else {
			read = sscanf(line, "%d %d %lf\n", &row, &col, &doubVal);
			//changeEntry(A, row, col, doubVal);
			//changeEntry(B, row, col, doubVal);
			//blank line
			if (read < 1) {
				blank++;
				continue;
			}
			//first set of matrix entries
			if (read > 1 && blank == 1) {
				//printf("%d %d %0.1f\n", row, col, doubVal);
				changeEntry(A, row, col, doubVal);
				//changeEntry(B, row, col, doubVal);
				//printf("New line\n");

			} else {
				changeEntry(B, row, col, doubVal);
			}
		}

		// printf("Numbers read: %d\n", read);
		//printf("%d %d %0.1f\n", row, col, doubVal);
		i++;
	}

	printNNZ(A, out, 'A', NNZ1);
	printNNZ(B, out, 'B', NNZ2);

	printScalar(A, out, 1.5, 'A');

	printSum(A, out, B, 'A', 'B');
	printSum(A, out, A, 'A', 'A');

	printDiff(B, out, A, 'B', 'A');
	printDiff(A, out, A, 'A', 'A');

	printTranspose(A, out, 'A');
	printProduct(A, out, B, 'A', 'B');
	printProduct(B, out, B, 'B', 'B');

	freeMatrix(&A);
	freeMatrix(&B);

	fclose(in);

	// while (fscanf(fp, "%d %lf", &intVal, &doubVal) == 1) {

	// }

	// char c = '\0';
	// while (c != EOF) {
	// 	c = fgetc(in);
	// 	if (c == ' ' || c == '\n') {
	// 		continue;
	// 	}
	// 	printf("%c ", c);

	// }
	// int i = 0;
	// fscanf (in, "%d", &i);
	// while (!feof (in))
	// {
	// 	printf ("%d ", i);
	// 	fscanf (in, "%d", &i);
	// }
	return 0;
}

