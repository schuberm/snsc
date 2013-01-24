#include <stdlib.h>

#include "cf.hh"
#include "genGaussian.hh"
#include "printGaussian.hh"
using namespace std;

int main(int argc, char *argv[])
{
	int n = atoi(argv[1]);
	float sigma = atof(argv[2]);
	float** gaussian = create2d(n);
	genGaussian(n, sigma, gaussian);
	printGaussian(n, gaussian);
	free2d(gaussian);
	return 0;
}
