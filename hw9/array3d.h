#ifndef ARRAY3DHH
#define ARRAY3DHH

template<typename T> 
T*** allocate3d(int n, int m, int p) 
{
    T*** rho;
    rho       = new T**[n];
    rho[0]    = new T*[n*m];
    rho[0][0] = new T[n*m*p];
    for( int i = 0; i < n; i++ ) {
        rho[i] = rho[0] + i*m;
        for( int j = 0; j < m; j++ ) {
            rho[i][j] = rho[0][0] + (i*m + j)*p;
        }
    }
    return rho;
}

template<typename T> 
void deallocate3d(T*** rho) 
{
    if (rho != 0) {
        if (rho[0] != 0) 
            delete[] rho[0][0];
        delete[] rho[0];
    }
    delete[] rho;    
}

#endif
