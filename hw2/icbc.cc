#include <cmath>
#include "icbc.hh"

void initialConditions(float* x,float** active,const int &numPoints, const float &dx, const float &x1, const float &a0,const float &sigma0){
	for( int i = 0; i < numPoints+2; i++ ) {
		x[i] = x1 + (i + 0.5)*dx;
	}
	for( int i = 0; i < numPoints+2; i++ ) {
		for( int j = 0; j < numPoints+2; j++ ) {
			active[i][j] = a0*exp( -(pow(x[i],2) + pow(x[j],2))/(2*pow(sigma0,2)) );
		}
	}
}

void periodicConditions(float** before,const int &numPoints){
	for( int i = 0; i < numPoints+2; i++ ) {
		before[0][i]           = before[numPoints][i];
		before[numPoints+1][i] = before[1][i];
		before[i][0]           = before[i][numPoints];
		before[i][numPoints+1] = before[i][1];
	}
}
