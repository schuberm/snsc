#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "cpgplot.h"
#include <mpi.h>
#include <omp.h>
#include <time.h>

int main(int argc, char **argv) {
    /* simulation parameters */
    const int totpoints=1000;
    const float xleft = -12., xright = +12.;
    const float kappa = 1.;

    const int nsteps=100000;
    const int plotsteps=50;

    /* data structures */
    float *x;
    float **temperature;
    float *theory;

    /* parameters of the original temperature distribution */
    const float ao=1., sigmao=1.;
    float a, sigma;

    float fixedlefttemp, fixedrighttemp;

    int old, new;
    int step, i;
    int red, grey,white;
    float time;
    float dt, dx;
    float error;
    clock_t t1,t2;
    
    /*MPI parameters */
    int rank, size, thread;
    int ierr;
    int localsize;
    int leftn,rightn;
    float localxleft, localxright;
    const int TAG=1;
    MPI_Status status;

    t1=clock();
    //ierr = MPI_Init(&argc, &argv);
    ierr = MPI_Init_thread(&argc, &argv, MPI_THREAD_FUNNELED,&thread);
    if (thread>=MPI_THREAD_FUNNELED){
    ierr = MPI_Comm_size(MPI_COMM_WORLD,&size);
    ierr = MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    
    //printf(" %d \t %d\n ", rank, size);
    if (totpoints%size==0){
    localsize = totpoints/size+2;
    //printf("local size = %d\n", localsize);
    }
    else{
    localsize = (totpoints+totpoints%size)/size+2;
    //printf("local size = %d\n", localsize);
    }
    
    /* set parameters */
    //dx = (xright-xleft)/(totpoints-1);

    dx = (xright-xleft)/(localsize*size);
    dt = dx*dx * kappa/10.;

    /*
     * allocate data, including ghost cells: old and new timestep
     * theory doesn't need ghost cells, but we include it for simplicity
     */

    theory = (float *)malloc((localsize)*sizeof(float));
    x      = (float *)malloc((localsize)*sizeof(float));
    temperature = (float **)malloc(2 * sizeof(float *));
    temperature[0] = (float *)malloc((localsize)*sizeof(float));
    temperature[1] = (float *)malloc((localsize)*sizeof(float));
    old = 0;
    new = 1;

    /* setup initial conditions */

    localxleft = xleft+rank*(localsize)*dx;
    localxright = xleft+(rank+1)*(localsize)*dx;
    //printf(" %g \t %g\n ", localxleft, localxright);
    
    leftn=(rank-1+size)%size;
    rightn=(rank+1)%size;

    time = 0.;
    //for (i=0; i<totpoints+2; i++) {
    for (i=0; i<localsize; i++) {
        x[i] = localxleft + (i-1)*dx;
        temperature[old][i] = ao*exp(-(x[i]*x[i]) / (2.*sigmao*sigmao));
        theory[i]           = ao*exp(-(x[i]*x[i]) / (2.*sigmao*sigmao));
    }
    fixedlefttemp = ao*exp(-(xleft-dx)*(xleft-dx) / (2.*sigmao*sigmao));
    fixedrighttemp= ao*exp(-(xright+dx)*(xright+dx)/(2.*sigmao*sigmao));

#ifdef PGPLOT
    cpgbeg(0, "/xwindow", 1, 1);
    cpgask(0);
    cpgenv(localxleft, localxright, 0., 1.5*ao, 0, 0);
    cpglab("x", "Temperature", "Diffusion Test");
    red = 2;  cpgscr(red,1.,0.,0.);
    grey = 3; cpgscr(grey,.2,.2,.2);
    white=4;cpgscr(white,1.0,1.0,1.0);

    cpgsls(1); cpgslw(1); cpgsci(grey);
    cpgline(localsize, x, theory);
    cpgsls(2); cpgslw(3); cpgsci(red);
    cpgline(localsize, x, temperature[old]);
#endif

    /* evolve */

    for (step=0; step < nsteps; step++) {
        /* boundary conditions: keep endpoint temperatures fixed. */

        if (rank==0)
        temperature[old][0] = fixedlefttemp;
        if (rank==(size-1))
        temperature[old][localsize-1] = fixedrighttemp;
#pragma omp parallel default(none) shared(temperature,localsize,new,old,dt,dx)
{
#pragma omp for schedule(static,4)        
        for (i=1; i<localsize; i++) {
            temperature[new][i] = temperature[old][i] + dt*kappa/(dx*dx) *
                (temperature[old][i+1] - 2.*temperature[old][i] + 
                 temperature[old][i-1]) ;
        }
}
	ierr = MPI_Sendrecv(&temperature[new][localsize-2],1,MPI_FLOAT,rightn,TAG,&temperature[new][0],1,MPI_FLOAT,leftn,TAG,MPI_COMM_WORLD,&status);
	ierr = MPI_Sendrecv(&temperature[new][1],1,MPI_FLOAT,leftn,TAG,&temperature[new][localsize-1],1,MPI_FLOAT,rightn,TAG,MPI_COMM_WORLD,&status);
        
	time += dt;

#ifdef PGPLOT
        if (step % plotsteps == 0) {
            cpgbbuf();
            cpgeras();
            cpgsls(2); cpgslw(12); cpgsci(red);
            cpgline(localsize, x, temperature[new]);
        }
#endif

        /* update correct solution */

        sigma = sqrt(2.*kappa*time + sigmao*sigmao);
        a = ao*sigmao/sigma;
        for (i=0; i<localsize; i++) {
            theory[i] = a*exp(-(x[i]*x[i]) / (2.*sigma*sigma));
        }

#ifdef PGPLOT
        if (step % plotsteps == 0) {
            cpgsls(1); cpgslw(6); cpgsci(white);
            cpgline(localsize, x, theory);
            cpgebuf();
        }
#endif
        error = 0.;
        for (i=1;i<localsize-1;i++) {
            error += (theory[i] - temperature[new][i])*(theory[i] - temperature[new][i]);
        }
        error = sqrt(error);

            //printf("Step = %d, Time = %g, Error = %g\n", step, time, error);

        old = new;
        new = 1 - old;
    }

    /*
     * free data
     */

    free(temperature[1]);
    free(temperature[0]);
    free(temperature);
    free(x);
    free(theory);
    }	
    MPI_Finalize();
    t2=clock();
    float seconds = ((float)t2-(float)t1)/CLOCKS_PER_SEC;
    printf("%f\n",seconds);
    return 0;
}
