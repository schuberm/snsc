#include "cf.hh"

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
