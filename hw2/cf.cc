#include "cf.hh"

float* create1d(const int &n){
	float *a = new float [n];
	return a;
}

void free1d(float *a){
	delete[] a;
}

float** create2d(const int &n) {
	float **a = new float * [n];
	a[0] = new float [n*n];
	for (int i=1; i<n; i++)
		a[i] = &a[0][i*n];
	return a;
}

void free2d(float **a) {
	delete[] a[0];
	delete[] a;
}

float*** create3d(const int &x, const int &y, const int &z){
	float*** a  = new float**[x];
	a[0] = new float*[x*y];
	a[0][0] = new float[x*y*z];

	for( int i = 0; i < x; i++ ) {
	        a[i] = a[0] + i*(y);
		for( int j = 0; j < y; j++ ) {
			a[i][j] = a[0][0] + (i*y + j)*z;
 		       }
	}
	return a;    
}

void free3d(float ***a){
	delete[] a[0][0];
	delete[] a[0];
	delete[] a;
}

