#include <stdio.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <ctime>
#include <iostream>
#include <fstream>
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
	float **mtpair=matrix(n,2);
	float **lcgpair=matrix(n,2);
	int x =1;
	int y =1000;
	
	ofstream mtfile ("mtpair.txt");
	ofstream lcgfile ("lcgpair.txt");	

	/* specifying to use Mersenne twister MT-19937 as the uniform PRNG */
	gBaseRand = gsl_rng_alloc(gsl_rng_mt19937);
	srand(time(NULL));                    /* initialization for rand() */
	randSeed = rand();                    /* returns a non-negative integer */
	gsl_rng_set (gBaseRand, randSeed);    /* seed the PRNG */

	for (int i = 0; i < n; i++) {
		x = lcg(x,a,c,m);
		y = lcg(y,a,c,m);
		mtpair[i][0]=0.2*gsl_rng_uniform (gBaseRand)-0.1;
		mtpair[i][1]=0.2*gsl_rng_uniform (gBaseRand)-0.1;
		lcgpair[i][0]=0.2*(float)(x)/(m-1)-0.1;
		lcgpair[i][1]=0.2*(float)(y)/(m-1)-0.1;
//		printf (" %f", k);
//		printf (" %f", x/(m-1));
		mtfile << mtpair[i][0] <<"\t" <<mtpair[i][1] <<"\n";
		lcgfile << lcgpair[i][0] <<"\t" << lcgpair[i][1] <<"\n";
	}

	printf ("\n");
	matrix_free(lcgpair);
	matrix_free(mtpair);
	mtfile.close();
	lcgfile.close();
	gsl_rng_free(gBaseRand);
	return 0;
}
