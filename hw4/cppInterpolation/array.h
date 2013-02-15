// array.h - header file for array with prototype declarations and constants
#ifndef _ARRAY_
#define _ARRAY_

// Allocate an array of n elements
float* vector(int n);

// Free the memory associated with the 1d array 'a'
void vector_free(float* a);

// Allocate an 'n' x 'm' array (returns an array of pointers to the rows)
float** matrix(int n, int m);

// Free the memory associated with the 2d array 'a'
void matrix_free(float** a);

// Allocate an 'n' x 'm' x 'p' array
float*** tensor(int n, int m, int p);

// Free the memory associated with the 3d array 'a'
void tensor_free(float*** a);

#endif
