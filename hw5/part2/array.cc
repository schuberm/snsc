// array.c - implementation for array
#include "array.h"
#include <stdlib.h>

float* vector(int n) 
{
    // Allocate an array of n elements
    return new float[n];
}

void vector_free(float* a) 
{
    // Free the memory associated with the 1d array 'a'
    delete[] a;
}

float** matrix(int n, int m)
{
    // Allocate an 'n' x 'm' array (returns an array of pointers to the rows) 
    float** a = new float*[n];
    a[0] = new float[n*m];
    for (int i=1;i<n;i++)
        a[i] = &a[0][i*m];
    return a;
}

void matrix_free(float** a) 
{
    // Free the memory associated with the 2d array 'a'
    if (a != 0)
        delete[] a[0];
    delete[] a;
}

float*** tensor(int n, int m, int p)
{
    // Allocate an 'n' x 'm' x 'p' array
    float ***a;
    a = new float**[n];
    a[0] = new float*[n*m];
    a[0][0] = new float[n*m*p];
    for (int i = 0; i < n; i++) {
        a[i] = a[0] + i*m;
        for (int j = 0; j < m; j++) {
            a[i][j] = a[0][0] + (i*m + j)*p;
        }
    }
    return a;
}

void tensor_free(float*** a)
{
    // Free the memory associated with the 3d array 'a'
    if (a != 0) {
        if (a[0] != 0)
            delete[] a[0][0];
        delete[] a[0];
    }
    delete[] a;

}

