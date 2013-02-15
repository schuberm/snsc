// diffusion_test.c - test for diffusion module
#include "array.h"
#include "interpolation.h"
#include <iostream>
#include <cmath>

int test_constant() 
{
    int size = 4;
    int newsize = (size-1)*2+1;
    float* grid = vector(size);
    float** in = matrix(size,size);
    float** out = matrix(newsize,newsize);
    float** expect = matrix(newsize,newsize);

    float c = 1.0;

    for (int i=0; i < size; i++)
        grid[i] = i-1;

    for (int i=0; i < size; i++)
        for (int j=0; j < size; j++) 
            in[i][j] = c;

    for (int i=0; i < newsize; i++)
        for (int j=0; j < newsize; j++) 
            expect[i][j] = c;

    for (int i=0; i < newsize; i++) {
        float x = 0.5*i-1;
        for (int j=0; j < newsize; j++) {
            float y = 0.5*j-1;
            out[i][j] = interpolation(in, grid, size, grid, size, x, y);
        }
    }

    int failure = 0;
    float bythismuch = 0.0;

    for (int i=0; i < newsize; i++)
        for (int j=0; j < newsize; j++) 
            if (out[i][j] != expect[i][j]) {
                failure++;
                bythismuch += pow(out[i][j]-expect[i][j],2);
                std::cout << "(" << i << "," << j << ") " 
                          << out[i][j] << "<->" << expect[i][j]
                          << std::endl;
            }
    
    if (failure != 0)
        std::cout << "constant test: FAILED (in "
                  << failure << " spots, in total by this much: "
                  << bythismuch << ")" << std::endl;
    else
        std::cout << "constant test: PASSED" << std::endl;

    vector_free(grid);
    matrix_free(in);
    matrix_free(out);
    matrix_free(expect);

    return failure;
}

int test_gradient() 
{
    int size = 4;
    int newsize = (size-1)*2+1;
    float* grid = vector(size);
    float** in = matrix(size,size);
    float** out = matrix(newsize,newsize);
    float** expect = matrix(newsize,newsize);

    for (int i=0; i <= size+1; i++)
        grid[i] = i-1;

    float a = 2;
    float b = 0.015625; 
    float c = 1.0;

    for (int i=0; i < size; i++)
        for (int j=0; j < size; j++) 
            in[i][j] = a*(i-1) + b*(j-1) + c;

    a /= 2;
    b /= 2;
    for (int i=0; i < newsize; i++)
        for (int j=0; j < newsize; j++) 
            expect[i][j] = a*(i-2) + b*(j-2) + c;

    for (int i=0; i < newsize;i++) {
        float x = 0.5*i-1;
        for (int j=0; j < newsize; j++) {
            float y = 0.5*j-1;
            out[i][j] = interpolation(in, grid, size, grid, size, x, y);
        }
    }

    int failure = 0;
    int pass = 0;
    float bythismuch = 0.0;

    for (int i=0; i < newsize; i++)
        for (int j=0; j < newsize; j++) 
            if (out[i][j] != expect[i][j]) {
                failure++;                
                bythismuch += pow(out[i][j]-expect[i][j],2);
                std::cout << "(" << i << "," << j << ") " 
                          << out[i][j] << "<->" << expect[i][j]
                          << std::endl;
            } else
                pass++;
  
    if (failure != 0)
        std::cout << "gradient test: FAILED (in "
                  << failure << " spots, in total by this much: "
                  << bythismuch << ")" << std::endl;
    else
        std::cout << "gradient test: PASSED" << std::endl;

    vector_free(grid);
    matrix_free(in);
    matrix_free(out);
    matrix_free(expect);

    return failure;
}

int main() 
{
    int failure = 0;
    failure += test_constant();
    failure += test_gradient();       
    return failure;
}
