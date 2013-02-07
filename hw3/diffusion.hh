//diffusion.hh
#ifndef DIFFUSIONH
#define DIFFUSIONH
#include <fstream>
#include <iostream>
#include <cmath>

class Diffusion {
	public:
		Diffusion(float x1, float x2, float D, int numPoints);
		void init(float a0, float sigma0); // set initial field
		void swapBefAft();
		void periodic();
		void timeStep(float D);           // solve diff. equation over dt
		void analytical(float D, float time, float sigma0, float a0, int numImages, int x1, int x2);
		void calcError();
		void toFile(std::ofstream& f);          // write to file (binary,no npyheader)
		void toScreen();                   // report a line to screen
		float** getRho();
		float getRhoij(int i, int j);         // get a value of the field
		float* getx();
		float getxi(int i);
		float getdx();
		float getdt();
		float geterror();
		float rhoint;
		~Diffusion();
	private:
		int squaren;
		int theory;
		int before;
		int active;
		float dx;
		float dt;
		float*** rho;
		float* x;
		float error;
};

#endif
