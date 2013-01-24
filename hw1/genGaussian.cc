#include <math.h>
#include "genGaussian.hh"

void genGaussian (int n, float sigma, float **arr)
{
	float c = ((float) n)/2;
	for(int i=0; i<n; i++)
	{
		for(int j=0; j<n; j++)
		{
		float x = (float) i;
		float y = (float) j;
		arr[i][j]=exp(-((y-c)*(y-c)/(2*sigma*sigma)+(x-c)*(x-c)/(2*sigma*sigma)));
		}
	}
}
