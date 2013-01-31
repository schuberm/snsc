#include <cmath>

#include "analytical2dDiff.hh"
#include "cf.hh"

float** analytical2dDiff(const float &D,const float &time,const float &sigma0, const float &a0, const int &numPoints, const int &numImages, float *x, const int &x1, const int &x2){
	float **arr=create2d(numPoints+2);
	float sigma = sqrt( 2*D*time + pow(sigma0,2) );
	float a     = a0 * pow(sigma0/sigma,2);
	for( int i = 0; i < numPoints+2; i++ ) {
		for( int j = 0; j < numPoints+2; j++ ) {
			float rhoValue = 0.0;
			for( int k = -numImages; k <= numImages; k++ ) {
				for( int l = -numImages; l <= numImages; l++ ) {
					float ximage = x[i] - k*(x2 - x1);
					float yimage = x[j] - l*(x2 - x1);
					rhoValue += a*exp(-(pow(ximage,2)+pow(yimage,2))
							/(2*pow(sigma,2)));
				}
			}
			arr[i][j] = rhoValue;
		}
	}
	return arr;
}

float errorCalc(float** theory,float** active,const int &numPoints){
	float error =0.0;
	for (int i = 1; i <= numPoints; i++ ) {
		for( int j = 1; j <= numPoints; j++ ) {
			error += pow( theory[i][j]-active[i][j] , 2 );
		}
	}
	error = sqrt(error);
	return error;
}
