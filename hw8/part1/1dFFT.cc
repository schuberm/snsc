#include <iostream>
#include <cmath>
#include <fstream>
#include <fftw3.h>
int main()
{
	int N=8192;
	double *input;
	input=new double [N];
	for(int i=0;i<N;i++) 
		input[i] = 2.0;

	fftw_complex *out;
	out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * (N/2)+1);
	fftw_plan p;
	p= fftw_plan_dft_r2c_1d(N,input,out,FFTW_ESTIMATE);
	fftw_execute(p);

	for(int i=0;i<(N/2)+1;i++)
	{
		std::cout << i <<"\t"<< out[i][0] << "\t" << out[i][1] <<std::endl;
	}

	return 0;
}
