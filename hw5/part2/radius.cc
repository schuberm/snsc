#include <stdio.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <ctime>
#include <iostream>
#include <fstream>
#include <math.h>
#include "array.h"
using namespace std;

int lcg(int seed,int a, int c, int m){
	int rlcg;
	rlcg = (a*seed+c)%m;
	return rlcg;
}

int main (void){
	gsl_rng *gBaseRand;
	signed long randSeed;
	int n = 10000;
	int m = 6075;
	int a = 106;
	int c = 1283;
	float *mtpair=vector(2);
	float *lcgpair=vector(2);

	mtpair[0]=0;
	mtpair[1]=0;
	lcgpair[0]=0;
	lcgpair[1]=0;

	ofstream mtfile ("mtangle.txt");
	ofstream lcgfile ("lcgangle.txt");	

	/* specifying to use Mersenne twister MT-19937 as the uniform PRNG */
	gBaseRand = gsl_rng_alloc(gsl_rng_mt19937);
	srand(time(NULL));                    /* initialization for rand() */
	randSeed = rand();                    /* returns a non-negative integer */
	gsl_rng_set (gBaseRand, randSeed);    /* seed the PRNG */

	int x =rand();
        int y =rand();
	for (int i = 0; i < n; i++) {
		while (sqrt(mtpair[0]*mtpair[0]+mtpair[1]*mtpair[1])<=2){
			mtpair[0]=mtpair[0]+0.2*gsl_rng_uniform (gBaseRand)-0.1;
			mtpair[1]=mtpair[1]+0.2*gsl_rng_uniform (gBaseRand)-0.1;
		}
		while (sqrt(lcgpair[0]*lcgpair[0]+lcgpair[1]*lcgpair[1])<=2){
			x = lcg(x,a,c,m);
			y = lcg(y,a,c,m);
			lcgpair[0]=lcgpair[0]+0.2*(float)(x)/(m-1)-0.1;
			lcgpair[1]=lcgpair[1]+0.2*(float)(y)/(m-1)-0.1;
		}
		mtfile << sin(mtpair[1]/mtpair[0])<<"\n";
		lcgfile << sin(lcgpair[1]/lcgpair[0])<<"\n";
		mtpair[0]=0;
		mtpair[1]=0;
		lcgpair[0]=0;
		lcgpair[1]=0;
	}

	vector_free(lcgpair);
	vector_free(mtpair);
	mtfile.close();
	lcgfile.close();
	gsl_rng_free(gBaseRand);
	return 0;
}
