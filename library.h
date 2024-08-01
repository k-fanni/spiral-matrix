#ifndef LIBRARY_H
#define LIBRARY_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#define BUFFER_MAX 30

struct _Matrix
{
    int n;
    int **matrix;
    char *irany;
    char *forgas;
};

typedef struct _Matrix Matrix;

// menu.c
void programMenu(Matrix *data);
void menuText();
void titleBorder(char title[]);
void chooseOption(int option, Matrix *data);
void userGuide();

// matrix.c
int **generateMatrix_temp(int *n);
void generateMatrix(Matrix* data);
void printMatrix(Matrix *data);
void saveMatrix(Matrix *data);
void loadMatrix(Matrix *data);

// extraFunctions.c
void matrixAlloc(Matrix *data, int n, int lengthDir, int lengthTurn);
void fillMatrix(Matrix *data);
bool strEq(char a[], char b[]);
void evenCenter(int *i, int *j, char irany[], char forgas[]);
char charDir(char irany[]);
char turnCw(char dir);
char turnCcw(char dir);
int numOfDigits(int num);
void drawMatrix(int n, int **matrix, FILE *f);
void removeNewline(char *s);
void findCenter(int *nums, int n, int *j, int *k);
void findDir(int *nums, int n, char *dir, int *j, int *k);
void findTurn(int *nums, char *dir, char *turn, int n, int j, int k);

#endif // LIBRARY_H