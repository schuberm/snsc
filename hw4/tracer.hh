//tracer.hh
//2d tracer class that can couple with diffusion class
#ifndef TRACERH
#define TRACERH
#include <fstream>
#include <iostream>
#include <cmath>
#include <stdlib.h>
#include "interpolation.h"

class Tracer {
	public:
		Tracer(float x1, float x2);
		void init(float x0, float y0, float vx0, float vy0);
		void randForce(float hi, float lo);
		void coupledForce(float** rho, float* xgrid, int nx, float* ygrid, int ny);
		void timeStep(float dt);
		void initToFile(std::ofstream& f,const int &numSteps, const int &plotEvery);		
		void toFile(std::ofstream& f);
		void toScreen(float time);
		float getx();
		float gety();
		float getvx();
		float getvy();
		~Tracer();
	private:
		int before;
		int active;
		float fx;
		float fy;
		float* vx;
		float* vy;
		float* x;
		float* y;
		float* xlim;
		float* ylim;		
		float m;
};

#endif
