#include "del2op.hh"

float del2op(float **arr, const int &i, const int &j){
        float scalar = (+arr[i+1][j]
                        +arr[i-1][j]
                        +arr[i][j+1]
                        +arr[i][j-1]
                        -4*arr[i][j]);
        return scalar;
}
