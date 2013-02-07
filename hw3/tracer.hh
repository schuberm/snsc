//tracer.hh
#ifndef TRACERH
#define TRACERH
#include <fstream>
#include <iostream>
#include <cmath>
#include <stdlib.h>

class Tracer {
	public:
		Tracer(float x1, float x2);
		void init(float x0, float y0, float vx0, float vy0);
		void swapBefAft();
		void randForce(float hi, float lo);
		void timeStep(float dt);
		void toFile(std::ofstream& f);
		void toScreen();
		~Tracer();
	private:
		int before;
		int active;
		float* fx;
		float* fy;
		float* vx;
		float* vy;
		float* x;
		float* y;
		float* xlim;
		float* ylim;		
		float m;
};

#endif
