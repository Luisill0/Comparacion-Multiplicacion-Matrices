#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int** initializeMatrix(int size){
    int **C = new int*[size];
    for(int i = 0; i < size; i++){
        C[i] = new int[size];
    }
    
    return C;
}

void setMatrixTo(int **M,int size,int value){
	for(int i = 0; i < size; i++){
		for(int j = 0; j < size; j++){
			M[i][j] = value;
		}
	}
}

void freeMatrix(int ***M, int size){
    for(int i = 0; i < size; i++){
        free(*(M+i));
    }
    free(*M);
    *M = NULL;
}

int** add(int** M1,int** M2, int n){
    int** temp = initializeMatrix(n);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            temp[i][j] = M1[i][j] + M2 [i][j];
        }
    }
    return temp;
}

int** subtract(int** M1, int** M2, int n){
    int** temp = initializeMatrix(n);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            temp[i][j] = M1[i][j] - M2[i][j];
        }
    }
    return temp;
}

void fillRandom(int** matrix, int n, double SEED){
    srand(SEED);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            matrix[i][j] = rand() % 8 + 1;
        }
    }
}

void printMatrix(int** matrix, int n){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            printf("[%3d]",matrix[i][j]);
        }
        putchar('\n');
    }
    putchar('\n');
}
