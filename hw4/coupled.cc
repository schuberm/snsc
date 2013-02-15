// 
// coupled.cc
//

#include "diffusion.hh"
#include "tracer.hh"

int main( int argc, char *argv[] ) 
{
	// Simulation parameters 
	const float x1 = -5;
	const float x2 = 5;
	const float D = 1;
	const float x0 = 0;
	const float y0 = 0;
	const float vx0 = 0;
	const float vy0 = 10;
	const int numSteps = 5000;
	const int numPoints = 128;
	const int numImages = 2;
	const int plotEvery = 50;	

	// Parameters of the initial density 
	const float a0 = 0.5/M_PI;
	const float sigma0 = 1;

	//Create instance of Diffusion object
	Diffusion field(x1,x2,D,numPoints);
	Tracer particle(x1,x2);

	//set initial conditions	
	particle.init(x0,y0,vx0,vy0);
	field.init(a0,sigma0);

	//test file
	std::ofstream fieldFile("rhofield.npy", std::ios::binary );
	field.initToFile(fieldFile,numSteps,plotEvery);
	field.toFile(fieldFile);
	std::ofstream particleFile("particle.npy", std::ios::binary );
	field.initToFile(particleFile,numSteps,plotEvery);
	field.toFile(particleFile);

	float time = 0.0;

	for( int step = 1; step <= numSteps; step++ ) {

		// Impose periodic boundary conditions
		field.periodic();
		// calulate forces
		particle.coupledForce(field.getRho(), field.getx(), numPoints+2, field.getx(), numPoints+2);
		// move forward in time
		field.timeStep();
		particle.timeStep(field.getdt());
		//
		if(step % plotEvery == 0){
			field.analytical(D,time,sigma0,a0,numImages,x1,x2);
			//
			field.calcError();
			//
			field.toFile(fieldFile);
			particle.toFile(particleFile);
			particle.toScreen(time);
		}
		//
		//field.toScreen(time,step);
		//
		time+=field.getdt();

	}
	fieldFile.close();
	particleFile.close();
	return 0;
}
