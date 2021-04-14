#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
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
double* makeComparison(int **A, int **B, int **C, int n);
void showAverages(double* tTrad, double* tStrass);
double getAverage(double* array);

int main(){
	int **A,**B,**C,n;
	double total_t,tTrad[10],tStrass[10],*temp;
	clock_t start_t, end_t;
	
	n = readSize();
	
	A = initializeMatrix(n);
    B = initializeMatrix(n);
	
	system("cls");
	
	cout<< "\n   Tradicional   Strassen\n\n";
	
	std::cout.precision(6);
	std::fixed;
	
	for(int i = 0; i < 10; i++){
		fillRandom(A,n,time(NULL));
    	fillRandom(B,n,time(NULL));
		temp = makeComparison(A,B,C,n);
		
		tTrad[i] = temp[0];
		tStrass[i] = temp[1];
			
		std::cout << std::setfill(' ') << std::setw(2) << i+1 << " |";
		std::cout << std::setfill(' ') << std::setw(6) << temp[0];
		cout << "      ";
		std::cout << std::setfill(' ') << std::setw(7) << temp[1] << "\n";
	}	
	showAverages(tTrad,tStrass);	
}

void showAverages(double* tTrad, double* tStrass){
	double promTrad,promStrass;
	
	promTrad = getAverage(tTrad);
	promStrass = getAverage(tStrass);
	
	cout<< "\n\nPromedios:\n\n" << "Tradicional: ";
	showDuration(promTrad);
	cout<< "\nStrassen: ";
	showDuration(promStrass);
}

double getAverage(double* array){
	double average=0;
	for(int i = 0; i < 10; i++){
		average += array[i];
	}
	return(average/10);
}

double* makeComparison(int **A, int **B, int **C, int n){
	double t1,t2;
	double *times = new double[2];
	timeval tim;
	
	//Traditional	
	gettimeofday(&tim,NULL);
	t1 = 1.0e6 * tim.tv_sec + tim.tv_usec;
	
	C = traditionalMultiply(A,B,n); 
	
	gettimeofday(&tim,NULL);
	t2 = 1.0e6 * tim.tv_sec + tim.tv_usec;	

	times[0] = t2-t1;

	//Strassen
	gettimeofday(&tim,NULL);
	t1 = 1.0e6 * tim.tv_sec + tim.tv_usec;
	
	C = strassenMultiply(A,B,n);
	
	gettimeofday(&tim,NULL);
	t2 = 1.0e6 * tim.tv_sec + tim.tv_usec;	
	
	times[1] = t2-t1;
	
	return times;
}

int readSize(){
    int size;
    
    cout << "Size of the matrices:\n";
    cin >> size;

    return size;
}

void showDuration(double duration){
	int seconds,ms,usec;
	int temp = (int) duration;
	
	seconds = temp/1000000;
	temp %= 1000000;
	
	ms = temp/1000;
	temp %= 1000;
	
	usec = temp % 1000;
	
	cout << seconds << " seconds  " << ms << "  miliseconds  " << usec << "  usec";
}



