#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <sys/time.h>
#include <limits.h>
#include "matrices.hpp"
#include "strassen.hpp"
#include "traditional.hpp"

using namespace std;

int readSize();
void showDuration(struct timeval duration);

int main(){
    int **A,**B,**C;
    int n;

    struct timeval start,end,duration;
    long micros;

    n = readSize();

    A = initializeMatrix(n);
    B = initializeMatrix(n);
	
    fillRandom(A,n,2500);
    fillRandom(B,n,5000);

    //printMatrix(A,n);
    //printMatrix(B,n);

    cout << "\nUsando el tradicional:\n";

    gettimeofday(&start,NULL);
	C = traditionalMultiply(A,B,n);
    gettimeofday(&end,NULL);

	putchar('\n');
    duration.tv_usec = abs(end.tv_usec - start.tv_usec);
    duration.tv_sec = abs(end.tv_sec - start.tv_sec);
	showDuration(duration);

    cout << "\n\n--------------------------------------------------------------\n";

	cout << "\nUsando strassen:\n";

    gettimeofday(&start,NULL);
	C = strassenMultiply(A,B,n);
    gettimeofday(&end,NULL);

	putchar('\n');
    duration.tv_usec = abs(end.tv_usec - start.tv_usec);
    duration.tv_sec = abs(end.tv_sec - start.tv_sec);
	showDuration(duration);
	
    return 0;
}

int readSize(){
    int size;
    
    cout << "Size of the matrices:\n";
    cin >> size;

    return size;
}

void showDuration(struct timeval duration){
    long temp;

    printf("%ld seconds   ",duration.tv_sec);
    //Divide msec & usec
    if(duration.tv_usec > 1000){
        temp = duration.tv_usec/1000;
        printf("%ld miliseconds   %ld microseconds", temp,duration.tv_usec%1000);
    }else{
        printf("%ld microseconds",duration.tv_usec);
    }
}
