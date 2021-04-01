#include <stdio.h>
#include <iostream>
#include "strassen.hpp"
#include "matrices.hpp"

using namespace std;

int readSize();

int main(){
    int **A,**B,**C;
    int n;

    n = readSize();

    A = initializeMatrix(n);
    B = initializeMatrix(n);
	
    fillRandom(A,n);
    fillRandom(B,n);

    printMatrix(A,n);
    printMatrix(B,n);
	
    cout << "Usando Strassen:\n";

	C = strassenMultiply(A,B,n);

	printMatrix(C,n);
	
    return 0;
}

int readSize(){
    int size;
    
    cout << "Size of the matrices:\n";
    cin >> size;

    return size;
}
