// interpolation.cc
#include "interpolation.h"
#include <cstdlib>
#include <iostream>

float interpolation(float** rho, float* xgrid, int nx, float* ygrid, int ny, float x, float y)
{
    // bilinear interpolation, given a square (density) field of size
    // npnts*npnts, with coordinates given in xgrid and ygrid, to the
    // off-grid point (x,y).
    float tol = 1.e-5;
    bool check1 = (x - xgrid[0] >= -tol);
    bool check2 = (x - xgrid[nx-1] < tol);
    bool check3 = (y - xgrid[0] >= -tol);
    bool check4 = (y - xgrid[ny-1] < tol);

    if (check1 && check2 && check3 && check4) {
        // find a `patch' such that x lies between xgrid[i] and
        // xgrid[i+1] (likewise for y).  initial guess:
        float dx = (xgrid[nx-1]-xgrid[0])/(nx-1);
        float dy = (ygrid[ny-1]-ygrid[0])/(ny-1);
        int i = (int)((x-xgrid[0])/dx);
        int j = (int)((y-ygrid[0])/dy);
        // by round off the patch could be out of bounds, correct for
        // this:
        if (i>=nx-1) i=nx-2;
        if (j>=ny-1) j=ny-2;
        // the computation will not work for non-uniform grids,
        // correct for this too:
        while (xgrid[i] >= x && i > 0)
            i--;
        while (xgrid[i] < x && i < nx-2)
            i++;
        while (ygrid[j] >= y && j > 0)
            j--;
        while (ygrid[j] < y && j < ny-2)
            j++;
        // relative position within patch
        float xr = (x - xgrid[i])/(xgrid[i+1] - xgrid[i]);
        float yr = (y - ygrid[j])/(ygrid[j+1] - ygrid[j]);
        // corner values
        float a = rho[i][j];
        float b = rho[i+1][j] - rho[i][j];
        float c = rho[i][j+1] - rho[i][j];
        float d = rho[i][j] + rho[i+1][j+1] - rho[i+1][j] - rho[i][j+1];
        // bilinear interpolation
        float result = a + b*xr + c*yr + d*xr*yr;
        return result;
    }
    else
    {
        std::cerr << "ERROR in interpolation: a point fell off the grid"
                  << "\nx,y           = " << x << "," << y
                  << "\nmin(x),min(y) = " << xgrid[0] << "," << ygrid[0]
                  << "\nmax(x),max(y) = " << xgrid[nx-1] << "," << ygrid[ny-1]
                  << "\ncheck1=" << check1
                  << "\ncheck2=" << check2
                  << "\ncheck3=" << check3
                  << "\ncheck4=" << check4
                  << std::endl;
        exit(1);
    } 
}
