
#include <stdio.h>
#include "Matrix.h"
#define SIZE 15
/************************************************************************
*function name: Matrix.                                                 *
*The input: -.                                                          *
*The output:-.                                                          *
*The Function operation: The function gets a matrix from the user and   *
*runs different operations on it.                                       *
*************************************************************************/
void Matrix() {
	int row = -1, col = -1, i, j, temp;
	int matrix1[SIZE][SIZE];
	char operation = "\0";
	int newMatrixDim[2] = { 0 };
	printf("Welcome to the Matrix calculator\n");
	//Making sure to recieve correct dimentions.
	while (row <= 0 || col <= 0) {
		printf("Please enter first matrix dimensions (row col):\n");
		scanf("%d %d", &row, &col);
		if (row <= 0 || col <= 0) {
			printf("Error\n");
		}
	}
	//Asking from the user to enter the matrix elements.
	printf("Please enter matrix elements(%dx%d):\n", row, col);
	for (i = 0; i < row; i++) {
		for (j = 0; j < col; j++) {
			scanf(" %d", &matrix1[i][j]);
		}
	}
	//The menu of the different operations on the matrix.
	do {			
		printf("Please enter operation:(+,-,*,t,c,q)\n");
		scanf(" %c", &operation);
		switch (operation) 			{
			case'+': {
				sumMatrix(matrix1, row, col);
				break;
			}
			case'-': {
				subMatrix(matrix1, row, col);
				break;
			}
			case'*': {
				//Changing the main matrix colum dimension..
				col = multiplyMatrix(matrix1, row, col);
				break;
			}
			case't': {
				transpose(matrix1, row, col);
				//Changing the main matrix dimensions.
				temp = row;
				row = col;
				col = temp;
				break;
			}
			case'c': {
				clear(matrix1, newMatrixDim);
				//Changing the main matrix dimensions.
				row = newMatrixDim[0];
				col = newMatrixDim[1];
				break;
			}
			case'q': {
				break;
			}
			default: printf("This operation does not exist!\n");
		}
	} while (operation != 'q');
}
/************************************************************************
*function name: printMatrix.                                            *
*The input: a matrix and it's dimensions.                               *
*The output:-                                                           *
*The Function operation: The function prints a matrix.                  *
*************************************************************************/
void printMatrix(int matrix[][SIZE], int row, int col) {
	int i, j;
	for (i = 0; i < row; i++) {
		for (j = 0; j < col; j++) {
			printf("%4d", matrix[i][j]);
		}
		printf("\n");
	}
}
/************************************************************************
*function name: sumMatrix.                                              *
*The input: a matrix and it's dimensions.                               *
*The output:-                                                           *
*The Function operation: The function sums two matrixes.                *
*************************************************************************/
void sumMatrix(int matrix[][SIZE], int row, int col) {
	int matrix2[SIZE][SIZE];
	int i, j;
	//Creating the seconed matrix.
	printf("Please enter matrix elements(%dx%d):\n", row, col);
	if (row > 0 && col > 0) {
		for (i = 0; i < row; i++) {
			for (j = 0; j < col; j++) {
				scanf(" %d", &matrix2[i][j]);
			}
		}
	}
	//Summing both matrixes.
	for (i = 0; i < row; i++) {
		for (j = 0; j < col; j++) {
			matrix[i][j] += matrix2[i][j];
		}
	}
	printf("The answer is:\n");
	printMatrix(matrix, row, col);
}
/************************************************************************
*function name: subMatrix.                                              *
*The input: a matrix and it's dimensions.                               *
*The output:-                                                           *
*The Function operation: The function substracts one matrix fron another.*
*************************************************************************/
void subMatrix(int matrix[][SIZE], int row, int col) {
	int matrix2[SIZE][SIZE];
	int i, j;
	//Creating the seconed matrix.
	printf("Please enter matrix elements(%dx%d):\n", row, col);
	if (row > 0 && col > 0) {
		for (i = 0; i < row; i++) {
			for (j = 0; j < col; j++) {
				scanf("%d", &matrix2[i][j]);
			}
		}
	}
	//Substract both matrixes.
	for (i = 0; i < row; i++) {
		for (j = 0; j < col; j++) {
			matrix[i][j] -= matrix2[i][j];
		}
	}
	printf("The answer is:\n");
	printMatrix(matrix, row, col);
}
/************************************************************************
*function name: multiplyMatrix.                                         *
*The input: a matrix and it's dimensions.                               *
*The output: the new colum value of the main matrix.                    *
*The Function operation: The function multiplies two matrixes.          *
*************************************************************************/
int multiplyMatrix(int matrix[][SIZE], int row, int col) {
	int multiplyMatrix[SIZE][SIZE];
	int matrix2[SIZE][SIZE];
	int i, j, r, c, l, sum;
	int n = 0;
	while (n <= 0)
	{
		printf("Please enter column dimension of second matrix:\n");
		scanf("%d", &n);//Asking from the user the number of dimensions of the seconed matrix.
		if (n <= 0)
			printf("Error\n");
	}

	printf("Please enter matrix elements(%dx%d):\n", col, n);
	for (r = 0; r < col; r++)//Asking from the user a seconed matrix.
	{
		for (c = 0; c < n; c++)
		{
			scanf(" %d", &matrix2[r][c]);
		}
	}
	//Creating a matrix by multiplying two matrixes.
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < n; j++)
		{
			sum = 0;
			for (l = 0; l < col; l++)
			{
				sum += matrix[i][l] * matrix2[l][j];
			}
			multiplyMatrix[i][j] = sum;
		}
	}
	//Printing the new matrix.
	printf("The answer is:\n");
	printMatrix(multiplyMatrix, row, n);
	//Copying the new matrix to the main matrix.
	for (i = 0; i < SIZE; i++)
	{
		for (j = 0; j < SIZE; j++)
		{
			matrix[i][j] = multiplyMatrix[i][j];
		}
	}
	return n;
}
/************************************************************************
*function name: clear.                                                  *
*The input: a matrix.                                                   *
*The output:-                                                           *
*The Function operation: The function clears the main matrix.           *
*************************************************************************/
void clear(int matrix[][SIZE], int newMatrixDim[2]) {
	int row = -1, col = -1, i, j;
	//Recieving from the user a new matrix to run the program with.
	while (row <= 0 || col <= 0) {
		printf("Please enter first matrix dimensions (row col):\n");
		scanf("%d %d", &row, &col);
		if (row <= 0 || col <= 0) {
			printf("Error\n");
		}
	}
	printf("Please enter matrix elements(%dx%d):\n", row, col);
	for (i = 0; i < row; i++) {
		for (j = 0; j < col; j++) {
			scanf(" %d", &matrix[i][j]);
		}
	}
	newMatrixDim[0] = row;
	newMatrixDim[1] = col;
}
/************************************************************************
*function name: transpose.                                              *
*The input: a matrix and it's dimensions.                               *
*The output:-                                                           *
*The Function operation: The function transposes the main matrix.       *
*************************************************************************/
void transpose(int matrix[][SIZE], int row, int col) {
	int i, j;
	int transpose[SIZE][SIZE];
	//Creating a transposed matrix.
	for (i = 0; i < row; i++) {
		for (j = 0; j < col; j++) {
			transpose[j][i] = matrix[i][j];
		}
	}
	//Printing the transposed matrix.
	printf("The answer is:\n");
	printMatrix(transpose, col, row);
	//Copying the transposed matrix to the main matrix.
	for (i = 0; i < SIZE; i++) {
		for (j = 0; j < SIZE; j++) {
			matrix[i][j] = transpose[i][j];
		}
	}
}