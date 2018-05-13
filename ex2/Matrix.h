
#ifndef Matrix_H
#define Matrix_H
#define SIZE 15

void Matrix();
void printMatrix(int matrix[][SIZE], int row, int col);
void sumMatrix(int matrix[][SIZE], int row, int col);
void subMatrix(int matrix[][SIZE], int row, int col);
int multiplyMatrix(int matrix[][SIZE], int row, int col);
void transpose(int matrix[][SIZE], int row, int col);
void clear(int matrix[][SIZE], int newMatrixDim[2]);


#endif
