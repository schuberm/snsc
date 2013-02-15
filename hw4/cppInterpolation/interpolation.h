// interpolation.h
#ifndef INTERPOLATIONH
#define INTERPOLATIONH

// interpolate, given a square (density) field of size nx*ny, with
// coordinates given in xgrid and ygrid, to the off-grid point (x,y).
// interpolation outside of the grid (within a tolerance), will cause
// an error and the program to exit.
float interpolation(float** rho, float* xgrid, int nx, float* ygrid, int ny, float x, float y);

#endif
