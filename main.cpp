#include <stdio.h>
#include <iostream>
#include "matrices.hpp"
#include "strassen.hpp"
#include "traditional.hpp"

using namespace std;

int readSize();

int main(){
    int **A,**B,**C;
    int n;

    n = readSize();

    A = initializeMatrix(n);
    B = initializeMatrix(n);
	
    fillRandom(A,n,2500);
    fillRandom(B,n,5000);

    printMatrix(A,n);
    printMatrix(B,n);
	
    cout << "\nUsando el tradicional:\n";
	C = traditionalMultiply(A,B,n);
	printMatrix(C,n);
	
	cout << "\nUsando strassen:\n";
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
