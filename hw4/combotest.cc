// 
// combotest.cc
//

#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <algorithm>

#include "diffusion.hh"
#include "tracer.hh"

int main( int argc, char *argv[] ) 
{
	// Simulation parameters 
	const float x1 = -12;
	const float x2 = 12;
	const float D = 1;
	const float x0 = 11;
	const float y0 = 11;
	const float vx0 = 1;
	const float vy0 = 1;
	const int numSteps = 2;
	const int numPoints = 128;
	const int numImages = 2;

	// Parameters of the initial density 
	const float a0 = 0.5/M_PI;
	const float sigma0 = 1;
	
	//test file
	std::ofstream testFile("testbin.bin", std::ios::binary );	
	
	//Create instance of Diffusion object
	Diffusion field(x1,x2,D,numPoints);
	Tracer particle(x1,x2);
	
	//set initial conditions	
	particle.init(x0,y0,vx0,vy0);
	field.init(a0,sigma0);

	float time = 0.0;
	
	for( int step = 1; step <= numSteps; step++ ) {
		
		// Impose periodic boundary conditions
		field.periodic();
		// move forward in time
		field.timeStep();
		particle.timeStep(field.getdt());
		//
		field.analytical(D,time,sigma0,a0,numImages,x1,x2);
		//
		field.calcError();
		//
		field.toFile(testFile);
		//
		field.toScreen(time,step);
		//
		time+=field.getdt();
		
	}
	testFile.close();
	//Destroy instance of Diffusion object
	return 0;
}
