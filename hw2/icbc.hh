//icbc.hh

#ifndef __ICBC_HH_INCLUDED
#define __ICBC_HH_INCLUDED

void initialConditions(float* x,float** active,const int &numPoints, const float &dx, const float &x1, const float &a0,const float &sigma0);
void periodicConditions(float** before,const int &numPoints);

#endif
