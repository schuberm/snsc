// 
// diffuse.cc
//
//

#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <algorithm>

#include "cf.hh"
#include "del2op.hh"

int main( int argc, char *argv[] ) 
{
	// Simulation parameters 
	const float x1 = -12;
	const float x2 = 12;
	const float D = 1;
	const int numPoints = 128;
	const int numSteps = 100;

	// Parameters of the initial density 
	const float a0 = 0.5/M_PI;

	// Data structures    
	float *x;
	float ***rho;
	float time;
	float dt, dx;
	float error=0.0;
	float rhoint;
	float rhodiff;
	int theory, before, active;

	// Compute derived parameters 
	dx = (x2 - x1)/(numPoints - 1);
	dt = dx*dx*D/5;

	//
	// Allocate data, including ghost cells: before and active timestep.
	// theory doesn't need ghost cells, but we include it for simplicity
	//
	x = create1d(numPoints+2);
	rho = create3d(3,numPoints+2,numPoints+2);

	theory = 0;
	before = 1;
	active = 2;

	// Setup initial conditions
	time = 0;
	for( int i = 0; i < numPoints+2; i++ ) {
		x[i] = x1 + (i + 0.5)*dx;
	}
	for( int i = 0; i < numPoints+2; i++ ) {
		for( int j = 0; j < numPoints+2; j++ ) {
				rho[active][i][j] = a0*i+a0*j;
			}
	}

	for( int step = 1; step <= numSteps; step++ ) {

		std::swap( before, active );

		// Impose periodic boundary conditions
		for( int i = 0; i < numPoints+2; i++ ) {
			rho[before][0][i]           = rho[before][numPoints][i];
			rho[before][numPoints+1][i] = rho[before][1][i];
			rho[before][i][0]           = rho[before][i][numPoints];
			rho[before][i][numPoints+1] = rho[before][i][1];
		}

		rhoint = 0.0; 
		rhodiff =0.0;
		for( int i = 1; i < numPoints+1; i++ ) {
			for( int j = 1; j < numPoints+1; j++ ) {
				//(dx*dx) left out of del2op due to error bug
				rho[active][i][j] = rho[before][i][j]
					+ dt*D/(dx*dx)*del2op(rho[before],i,j);
				rhoint += rho[active][i][j];
				rhodiff += rho[active][i][j]-rho[before][i][j];
			}
		}
		rhoint *= pow(dx,2);        

		time += dt;

		std::cout << "Step = "  << step  << ", "
			<< "Time = "  << time  << ", "
			<< "Error = " << error << ", "
			<< "Integrated density = " << rhoint 
			<< "Rho change =" << rhodiff 
			<< std::endl;
	}

	// Free the memory used for the data 
	free3d(rho);
	free1d(x);

	return 0;
}
