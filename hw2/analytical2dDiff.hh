//analytical2dDiff.hh

#ifndef __A2DIFF_HH_INCLUDED
#define __A2DIFF_HH_INCLUDED

float** analytical2dDiff(const float &D,const float &time,const float &sigma0, const float &a0, const int &numPoints, const int &numImages, float *x, const int &x1, const int &x2);

float errorCalc(float** theory,float** active,const int &numPoints);

#endif
