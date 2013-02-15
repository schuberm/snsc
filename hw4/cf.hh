//cf.hh
//create and free arrays 1,2,3d
#ifndef __CF_HH_INCLUDED
#define __CF_HH_INCLUDED

float* create1d(const int &n);
void free1d(float* a);
float** create2d(const int &n);
void free2d(float** a);
float*** create3d(const int &x, const int &y, const int &z);
void free3d(float*** a);

#endif
