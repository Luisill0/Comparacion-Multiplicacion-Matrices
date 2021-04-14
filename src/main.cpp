#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <sys/time.h>
#include <limits.h>
#include "matrices.hpp"
#include "strassen.hpp"
#include "traditional.hpp"

#define N 8

using namespace std;

int readSize();
void showDuration(double duration);
void showDuration2(double duration);

int main(){
    int **A,**B,**C;
    int n;
	double total_t,t1,t2;
	clock_t start_t, end_t;
	
	timeval tim;
    long micros;

    n = readSize();

    A = initializeMatrix(n);
    B = initializeMatrix(n);
	
	system("cls");
	
	cout.precision(6);
	cout << "n = " << n << "\n";
	cout << "\nLlenando matrices:\n";
	
	start_t = clock();
    fillRandom(A,n,2500);
    fillRandom(B,n,5000);
    end_t = clock();
    
	total_t = (double) (end_t - start_t)/CLOCKS_PER_SEC;
    
    cout << "Matrices llenas ( " << total_t << "  segundos)\n";

    cout << "\n\nUsando el tradicional:\n\n";
	
	start_t = clock();	
	gettimeofday(&tim,NULL);
	t1 = 1.0e6 * tim.tv_sec + tim.tv_usec;
	
	C = traditionalMultiply(A,B,n); 
	
	gettimeofday(&tim,NULL);
	t2 = 1.0e6 * tim.tv_sec + tim.tv_usec;	
    end_t = clock();
    total_t = (double) (end_t - start_t)/CLOCKS_PER_SEC;

	printf("Usando clock(): %f segundos\n",total_t);
	showDuration(total_t);
	
	cout << "\nUsando gettimeofday(): " << (t2-t1) << "\n";
	showDuration2(t2-t1);
	
    cout << "\n\n--------------------------------------------------------------\n";

	cout << "\nUsando strassen:\n";

    start_t = clock();	
	gettimeofday(&tim,NULL);
	t1 = 1.0e6 * tim.tv_sec + tim.tv_usec;
	
	C = strassenMultiply(A,B,n);
	
	gettimeofday(&tim,NULL);
	t2 = 1.0e6 * tim.tv_sec + tim.tv_usec;	
    end_t = clock();
    total_t = (double) (end_t - start_t)/CLOCKS_PER_SEC;

	printf("Usando clock(): %f segundos\n",total_t);
	showDuration(total_t);
	
	cout << "\nUsando gettimeofday(): " << (t2-t1) << "\n";
	showDuration2(t2-t1);
	
	return 0;
}

int readSize(){
    int size;
    
    cout << "Size of the matrices:\n";
    cin >> size;

    return size;
}

void showDuration2(double duration){
	int seconds,ms,usec;
	int temp = (int) duration;
	
	seconds = temp/1000000;
	temp %= 1000000;
	
	ms = temp/1000;
	temp %= 1000;
	
	usec = temp % 1000;
	
	cout << seconds << " seconds  " << ms << "  miliseconds  " << usec << "  usec";
}

void showDuration(double duration){
	int seconds,ms;
	
	seconds = (int) duration;
	ms = (int) (duration * 1000) % 1000;
	
	cout << seconds << " seconds  " << ms << " miliseconds\n";	
}

