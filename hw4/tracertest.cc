// 
// tracertest.cc
//


#include "tracer.hh"

int main( int argc, char *argv[] ) 
{
	// Simulation parameters 
	const float x1 = -1;
	const float x2 = 12;
	const float x0 = 11;
	const float y0 = 11;
	const float vx0 = 1;
	const float vy0 = 1;
	const int numSteps = 100;
	const float dt = 0.1;

	const float hi = 2.0;
	const float lo = -2.0;

	//test file
	std::ofstream testFile("testbin.bin", std::ios::binary );	
	//Create instance of Tracer object
	Tracer particle(x1,x2);
	
	//set initial conditions	
	particle.init(x0,y0,vx0,vy0);

	for( int step = 1; step <= numSteps; step++ ) {
		
		// random forcing
		particle.randForce( hi, lo);		
		// move forward in time
		particle.timeStep(dt);
		//
		particle.toFile(testFile);
		//
		particle.toScreen();
		//
		//time+=field.getdt();		
	}
	testFile.close();
	//Destroy instance of Tracer object
	return 0;
}
