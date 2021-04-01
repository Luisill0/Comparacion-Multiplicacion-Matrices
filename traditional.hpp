#include <stdio.h>
#include <stdlib.h>

int** traditionalMultiply(int** A, int** B, int n){
    int **C = initializeMatrix(n);

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            C[i][j] = 0;
            for(int k = 0; k < n; k++){
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    
    return C;
}
