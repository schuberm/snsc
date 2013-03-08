#include <stdio.h>
#include <math.h>
#include <ctime>
#include <gsl/gsl_integration.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_monte.h>
#include <gsl/gsl_monte_plain.h>


double f (double x, void * params) {
//	double alpha = *(double *) params;
	double f = log(x)*sin(x)*exp(x);
	return f;
}

double g (double *x, size_t dim, void *params)
{
	double g = log(x[0])*sin(x[0])*exp(x[0]);
	return g;
}


double extsimp (double lowlim, double uplim, int numeval){
	double integral=0.0;
	double h=(uplim-lowlim)/ ((double) (numeval));
	void * params;
	for (int i=0; i < numeval; i++){
		if (isnan(f(lowlim+(double)(i)*h,params))){
		integral=integral+0.0;
		}
		if(i%2==0 && isnan(f(lowlim+(double)(i)*h,params))==false && i!=0 && i!=numeval){
		integral=integral+f(lowlim+((double)(i))*h,params)*2*h/3;
		}
		if(i%2!=0 && isnan(f(lowlim+(double)(i)*h,params))==false){
		integral=integral+f(lowlim+((double)(i))*h,params)*4*h/3;	
		}
		if((i==0 || i==numeval) && isnan(f(lowlim+(double)(i)*h,params))==false ){
		integral=integral+f(lowlim+((double)(i))*h,params)*h/3;
		}

	}
	return integral;
}

double mc (double lowlim, double uplim, double min, double max, int numeval){
	signed long randSeed;
	double x,y,fx;
	void * params;
	double accept=0.0;
	gsl_rng *gBaseRand;
	/* specifying to use Mersenne twister MT-19937 as the uniform PRNG */
	gBaseRand = gsl_rng_alloc(gsl_rng_mt19937);
	srand(time(NULL));                    /* initialization for rand() */
	randSeed = rand();                    /* returns a non-negative integer */
	gsl_rng_set (gBaseRand, randSeed);    /* seed the PRNG */
	for (int i=0; i < numeval; i++){
		x=(uplim-lowlim)*gsl_rng_uniform (gBaseRand)+lowlim;
//		printf ("x          = % .18f\n", x);
		y=(max-min)*gsl_rng_uniform (gBaseRand)+min;
//		printf ("y          = % .18f\n", y);	
		fx=f(x,params);
//		printf ("fx          = % .18f\n", fx);		
		if (abs(y)<=abs(fx))
			accept=accept+1.0;
	}
	gsl_rng_free(gBaseRand);	
	return accept/((double) (numeval))*(uplim-lowlim)*(max-min);
}

double mc_gsl(double lowlim, double uplim, int numeval){
	double res, err;

	double xl[1] = {lowlim};
	double xu[1] = {uplim};

	const gsl_rng_type *T;
	gsl_rng *r;

	gsl_monte_function G = { &g, 1, 0 };

	size_t calls = numeval;

	gsl_rng_env_setup ();

	T = gsl_rng_default;
	r = gsl_rng_alloc (T);

	{
		gsl_monte_plain_state *s = gsl_monte_plain_alloc (1);
		gsl_monte_plain_integrate (&G, xl, xu, 1, calls, r, s, 
				&res, &err);
		gsl_monte_plain_free (s);

	}
	gsl_rng_free (r);
	return res;
}

double gq_gsl(double lowlim, double uplim, int numeval){
	double res,err;
	gsl_integration_workspace * w 
		= gsl_integration_workspace_alloc (numeval);
	gsl_function F;
	F.function = &f;
//	F.params = &alpha;
	gsl_integration_qags (&F, lowlim, uplim, 0, 1e-7, numeval,w, &res, &err);
	gsl_integration_workspace_free (w);
	return res;
}

int main (void)
{

	double expected = 7.38359;
	double lowlim = 0.0;
	double uplim = 3.0;
	double min = 0.0;
	double max = 6.4;
	double gq = 0.0;
	double simpson = 0.0;
	double montec = 0.0;
	double mcplain = 0.0;
	int numeval = 1000;

        simpson = extsimp ( lowlim, uplim, numeval);	
	montec = mc(lowlim, uplim, min, max, numeval);
	mcplain = mc_gsl(lowlim, uplim, numeval);
	gq = gq_gsl(lowlim,uplim,numeval);	

	printf ("exact result    = % .18f\n", expected);
	printf ("simpson rule = %.18f\n", simpson);
	printf ("monte carlo = %.18f\n", montec);	
	printf ("mc_gsl = %.18f\n", mcplain);	
	printf ("gq_gsl = %.18f\n", gq);	

	return 0;
}
