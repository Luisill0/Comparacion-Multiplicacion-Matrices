#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <limits.h>

#define N 256

void showDuration(double duration);
int potencia2(int n);
int strassen(int *, int *, int *, int, int);
double measureTime(int A[N][N],int B[N][N]);
void randomizeMatrices(int A[N][N],int B[N][N]);
void printMatrix(int A[N][N]);

int main(){
	int i;
	int A[N][N];
	int B[N][N];
	double time;
	
	printf("N = %d\n",N);	

	for(i = 0; i < 10; i++){
		randomizeMatrices(A,B);	
		time = measureTime(A,B);
		printf("%2d |  %.0f  usec\n",i+1,time);
	}
}

void printMatrix(int A[N][N]){
	int r,c;
	
	for( r=0;r<N;r++){
		for(c=0;c<N;c++){
			printf("%d  ",A[r][c]);
		}
		putchar('\n');
	}	
	putchar('\n');
}

void randomizeMatrices(int A[N][N],int B[N][N]){
	int r,c;
	
	srand(time(NULL));
	for( r=0;r<N;r++){
		for(c=0;c<N;c++){
			A[r][c]=B[r][c]=rand()%8+1;
		}
	}
}

double measureTime(int A[N][N],int B[N][N]){
	int i,j,r,c;
	double total_t,t1,t2;
	
	struct timeval tim;
	
	int pot2n,tamat2n;
	
	pot2n = 1;
	while(N > potencia2(pot2n)){
		pot2n = pot2n + 1;
	}
	tamat2n = potencia2(pot2n);
	
	int a[tamat2n][tamat2n],b[tamat2n][tamat2n],CS[tamat2n][tamat2n];
	
	for( i = 0; i < tamat2n; i++){
		for( j = 0; j <  tamat2n; j++){
			a[i][j] = b[i][j] = CS[i][j] = 0;
		}
	}
	
	for( i = 0; i < N; i++){
		for( j = 0; j < N; j++){
			a[i][j] = A[i][j];
			b[i][j] = B[i][j];
		}
	}
	
	gettimeofday(&tim,NULL);
	t1 = 1.0e6 * tim.tv_sec + tim.tv_usec;
	strassen(a,b,CS,tamat2n,tamat2n);
	
	gettimeofday(&tim,NULL);
	t2 = 1.0e6 * tim.tv_sec + tim.tv_usec;
		
    return (t2-t1);
}

int strassen(int *A,int *B,int *C,int m,int n){
	if(m == 2){
		int P=(*A+*(A+n+1))*(*B+*(B+n+1)); //P=(A[0][0]+A[1][1])*(B[0][0]+B[1][1])
		int Q=(*(A+n)+*(A+n+1))*(*B); //Q=(A[1][0]+A[1][1])*B[0][0]
		int R=(*A)*(*(B+1)-*(B+n+1)); //R=A[0][0]*(B[0][1]-B[1][1])
		int S=(*(A+n+1))*(*(B+n)-*B); //S=A[1][1]*(B[1][0]-B[0][0])
		int T=(*A+*(A+1))*(*(B+n+1)); //T=(A[0][0]+A[0][1])*B[1][1]
		int U=(*(A+n)-*A)*(*B+*(B+1)); //U=(A[1][0]-A[0][0])*(B[0][0]+B[0][1])
		int V=(*(A+1)-*(A+n+1))*(*(B+n)+*(B+n+1)); //V=(A[0][1]-A[1][1])*(B[1][0]+B[1][1]);
		*C=*C+P+S-T+V; //C[0][0]=P+S-T+V
		*(C+1)=*(C+1)+R+T; //C[0][1]=R+T
		*(C+n)=*(C+n)+Q+S; //C[1][0]=Q+S
		*(C+n+1)=*(C+n+1)+P+R-Q+U; //C[1][1]=P+R-Q+U
	}else{
		m = m/2;
		strassen(A,B,C,m,n);
		strassen(A,B+m,C+m,m,n);
		strassen(A+m,B+m*n,C,m,n);
		strassen(A+m,B+m*(n+1),C+m,m,n);
		strassen(A+m*n,B,C+m*n,m,n);
		strassen(A+m*n,B+m,C+m*(n+1),m,n);
		strassen(A+m*(n+1),B+m*n,C+m*n,m,n);
		strassen(A+m*(n+1),B+m*(n+1),C+m*(n+1),m,n);		
	}
}

int potencia2(int n){
	int i,p=1;
	
	for(i=1;i<=n;i++){
		p=2*p;
	}
	
	return(p);
}
