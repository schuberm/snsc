//tracer.cc
#include "tracer.hh"

Tracer::Tracer(float x1, float x2){
	xlim = new float [2];
	ylim = new float [2];
	xlim[0] = x1;
	ylim[0] = x1;
	xlim[1] = x2;
	ylim[1] = x2;
	before = 0;
	active = 1;
}

void Tracer::init(float x0, float y0, float vx0, float vy0){
	x = new float [2];
	y = new float [2];
	vx = new float [2];
	vy = new float [2];
	fx = new float [2];
	fy = new float [2];
	x[before]=x0;
	y[before]=y0;
	vx[before]=vx0;
	vy[before]=vy0;
	fx[before]=0.0;
	fy[before]=0.0;
	x[active]=x0;
	y[active]=y0;
	vx[active]=vx0;
	vy[active]=vy0;
	fx[active]=0.0;
	fy[active]=0.0;	
	m=1.0;
}

void Tracer::swapBefAft(){
	std::swap( before, active );
}

void Tracer::randForce(float hi, float lo){
	fx[before]=lo + (float)rand()/((float)RAND_MAX/(hi-lo));
	fy[before]=lo + (float)rand()/((float)RAND_MAX/(hi-lo));
}

void Tracer::timeStep(float dt){
	fx[active]=fx[before];
	fy[active]=fy[before];
	vx[active]=dt*fx[active]/m+vx[before];
	vy[active]=dt*fy[active]/m+vy[before];
	x[active]=dt*vx[before]+x[before];
	y[active]=dt*vy[before]+y[before];
	if (x[active]>xlim[1])
		x[active]=x[active]-2*xlim[1];
	if (y[active]>ylim[1])
		y[active]=y[active]-2*ylim[1];
	if (x[active]<xlim[0])
		x[active]=x[active]-2*xlim[0];
	if (y[active]<ylim[0])
		y[active]=y[active]-2*ylim[0];
}

void Tracer::toFile(std::ofstream& f){
	f.write( (char*) &x[active], x[active]*sizeof(float) );
	f.write( (char*) &y[active], y[active]*sizeof(float) );
	f.write( (char*) &vx[active], vx[active]*sizeof(float) );
	f.write( (char*) &vy[active], vy[active]*sizeof(float) );
	f.write( (char*) &fx[active], fx[active]*sizeof(float) );
	f.write( (char*) &fy[active], fy[active]*sizeof(float) );
}

void Tracer::toScreen(){
	std::cout << x[active] << "\t" << y[active] << std::endl;
}

Tracer::~Tracer(){
	delete[] x;
	delete[] y;
	delete[] vx;
	delete[] vy;
	delete[] fx;
	delete[] fy;
	delete[] xlim;
	delete[] ylim;
}

