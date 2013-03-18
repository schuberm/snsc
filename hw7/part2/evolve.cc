#include <stdio.h>
#include <iostream>
#include <fstream>
//#include <lapacke/lapacke.h>
//#include <cblas.h>
#include <gsl/gsl_blas.h>
using namespace std;

int main (int argc, const char * argv[])
{
	const int N = 100;
	const int numTsteps = 100;	
	double *A = new double [N*N];
	double *Qin = new double [N];
	double *Qout = new double [N];
	double D=1.0;
	double dt=0.00001;
	double dx=1.0/N;

	//set matrix A
	for (int i=0; i<N;i++)
	{
		for(int j=0; j<N;j++)
		{
			if (i==j){
				A[i*(N+1)]=-D*dt/(dx*dx)*2+1;
			}
			if (j+1==i || j-1==i)
				A[i*N+j]=D*dt/(dx*dx);
		}
	} 
	
	//check matrix A
/*	
	for(int i=0;i<N;i++)
	{
		for(int j=0;j<N;j++)
		{
			printf("%lf ",A[i*N+j]);
		}
		printf("\n");
	}
*/	
	//set initial conditions
	for(int i=0;i<N;i++)
	{
		if (i==0)
			Qin[i]=1.0;
		else
			Qin[i]=0.0;
	}
	
	for(int i=0;i<numTsteps;i++)
	{
		cblas_dgemv(CblasRowMajor,CblasNoTrans,N,N,1.0,A,N,Qin,1,0.0,Qout,1);
		for (int j=0;j<N;j++)
			Qin[j]=Qout[j];
		if (i%20==0){
			for (int j=0;j<N;j++){
				cout << Qout[j] << " \t" ;
			        //printf("%lf ",Qout[j]);
			}
			cout << endl;
		}
	}
	
	delete[] A;	
	delete[] Qin;
	delete[] Qout;
	return 0;
}
