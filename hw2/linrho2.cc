// 
// diffuse.cc
//
//

#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <algorithm>
#include <stdlib.h>

#include "cf.hh"
#include "del2op.hh"
#include "analytical2dDiff.hh"

void outputInitial(std::ofstream &theoryFile, const std::string &header, const int &headersize, const int &numSteps, const int &plotEvery, const int &numPoints){
	theoryFile << header
		<< numSteps/plotEvery << ","
		<< numPoints+2        << ","
		<< numPoints+2        << "), }";
	int npadding = headersize - theoryFile.tellp() - 1;
	std::string padding = std::string( npadding, ' ' );
	theoryFile << padding << "\n";
}

int main( int argc, char *argv[] ) 
{
	// Simulation parameters 
	const float x1 = -12;
	const float x2 = 12;
	const float D = 1;
	const int numPoints = 128;
	const int numSteps = 4800;
	const int plotEvery = 150;

	// Parameters of the initial density 
	const float a0 = 0.5/M_PI;
	const float sigma0 = 1;

	// Parameter for the theoretical prediction 
	const int numImages = 2;

	// Output files
	const std::string dataFilename = "data.npy";
	const std::string theoryFilename = "theory.npy";

	// Header data for npy files
	const int  headersize = 5*16;
	const int  cheadersize = 61;
	const char cheader[cheadersize+1] 
		= "\x93NUMPY\1\0\x46\0{'descr': '<f4', 'fortran_order': False, 'shape': (";
	const std::string header( cheader, cheader+cheadersize );

	// Data structures    
	float *x;
	float ***rho;
	float time;
	float dt, dx;
	float error=0.0;
	float rhoint;
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

	//
	// Write out data for graphics with python+numpy+matplotlib
	//
	std::ofstream theoryFile( theoryFilename.c_str(), std::ios::binary );
	std::ofstream dataFile  ( dataFilename.c_str(),   std::ios::binary );
	outputInitial(theoryFile, header, headersize, numSteps, plotEvery,numPoints);
	/*
	   theoryFile << header 
	   << numSteps/plotEvery << "," 
	   << numPoints+2        << "," 
	   << numPoints+2        << "), }";
	   int npadding = headersize - theoryFile.tellp() - 1;
	   std::string padding = std::string( npadding, ' ' );
	   theoryFile << padding << "\n";
	 */
	theoryFile.write( (char*)(rho[active][0]), 
			(numPoints+2)*(numPoints+2)*sizeof(float) );
	/*
	   dataFile << header 
	   << numSteps/plotEvery << "," 
	   << numPoints+2        << "," 
	   << numPoints+2        << "), }" 
	   << padding            << '\n';
	 */
	outputInitial(dataFile, header, headersize, numSteps, plotEvery,numPoints);
	dataFile.write( (char*)(rho[active][0]), 
			(numPoints+2)*(numPoints+2)*sizeof(float) );

	// Time evolution
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
		for( int i = 1; i < numPoints+1; i++ ) {
			for( int j = 1; j < numPoints+1; j++ ) {
				//(dx*dx) left out of del2op due to error bug
				rho[active][i][j] = rho[before][i][j]
					+ dt*D/(dx*dx)*del2op(rho[before],i,j);
				rhoint += rho[active][i][j];
			}
		}
		rhoint *= pow(dx,2);        

		time += dt;

		if( step % plotEvery == 0 ) {

			// Update correct(theory) solution            
			rho[theory]=analytical2dDiff(D,time,sigma0,a0,numPoints,numImages,x,x1,x2);
			error = 0.0;           
			for( int i = 1; i <= numPoints; i++ ) {
				for( int j = 1; j <= numPoints; j++ ) {
					error += pow( rho[theory][i][j]-rho[active][i][j] , 2 );
				}
			}
			error = sqrt(error);

			// Write out data for graphics
			theoryFile.write( (char*)(rho[theory][0]), 
					(numPoints+2)*(numPoints+2)*sizeof(float) );
			dataFile.write( (char*)(rho[active][0]), 
					(numPoints+2)*(numPoints+2)*sizeof(float) );
		}

		std::cout << "Step = "  << step  << ", "
			<< "Time = "  << time  << ", "
			<< "Error = " << error << ", "
			<< "Integrated density = " << rhoint 
			<< std::endl;
	}

	// Close files
	theoryFile.close();
	dataFile.close();

	// Free the memory used for the data 
	free3d(rho);
	free1d(x);

	return 0;
}
