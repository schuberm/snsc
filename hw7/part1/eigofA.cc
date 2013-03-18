#include <stdio.h>
#include <iostream>
#include <fstream>
#include <lapacke/lapacke.h>
using namespace std;

int main (int argc, const char * argv[])
{
	const int N = 100;	
	double A[N][N]={{0.0}};
	double WR[N]={0.0};
	double WI[N]={0.0};
	double VL[N][N]={{0.0}};
	int LDVL = N;	
	double VR[N][N]={{0.0}};
	int LDVR = N;
	lapack_int info;
	double D=1.0;
        double dt=0.001;
        double dx=1.0/N;

	for (int i=0; i<N;i++)
	{
		for(int j=0; j<N;j++)
		{
			if (i==j)
				A[i][j]=2*D*dt/(dx*dx);
			if (i+1==j || i-1==j)
				A[i][j]=-D*dt/(dx*dx);
		}
	} 

	info = LAPACKE_dgeev(LAPACK_ROW_MAJOR,'V','V',N,*A,N,WR,WI,*VL,LDVL,*VR,LDVR);

	ofstream eigvec ("eigvec.txt");
	if (eigvec.is_open())
	{
		for(int i=0; i<N; i++)
		{
			for(int j=0; j<N; j++)
			{
			eigvec << VR[i][j];
			eigvec << "\t";
			}
			eigvec << "\n";	
		}
		eigvec.close();
	}
	else cout <<"Unable to open file";
	ofstream eigval ("eigval.txt");
	if (eigval.is_open())
	{
		for(int i=0; i<N; i++)
		{
			eigval << WR[i];
			eigval << "\n";	
		}
		eigval.close();
	}
	else cout <<"Unable to open file";
	
	return(info);
}
