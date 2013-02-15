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
	x[before]=x0;
	y[before]=y0;
	vx[before]=vx0;
	vy[before]=vy0;
	fx=0.0;
	fy=0.0;
	x[active]=x0;
	y[active]=y0;
	vx[active]=vx0;
	vy[active]=vy0;
	m=1.0;
}

void Tracer::randForce(float hi, float lo){
	fx=lo + (float)rand()/((float)RAND_MAX/(hi-lo));
	fy=lo + (float)rand()/((float)RAND_MAX/(hi-lo));
}

void Tracer::coupledForce(float** rho, float* xgrid, int nx, float* ygrid, int ny){
	float rho_interp = 0.0;
	float a=15.0;
	float alpha=1.0;
	rho_interp = interpolation(rho, xgrid, nx, ygrid, ny, x[before], y[before]);
	fx=x[before]-alpha*(1+a*rho_interp)*vx[before];
	fy=0-alpha*(1+a*rho_interp)*vy[before];
}

void Tracer::timeStep(float dt){
	std::swap( before, active);
	vx[active]=dt*fx/m+vx[before];
	vy[active]=dt*fy/m+vy[before];
	x[active]=dt*vx[before]+x[before];
	y[active]=dt*vy[before]+y[before];
	if (x[active]>xlim[1])
		x[active]=x[active]-abs(xlim[1])-abs(xlim[0]);
	if (y[active]>ylim[1])
		y[active]=y[active]-abs(ylim[1])-abs(ylim[0]);;
	if (x[active]<xlim[0])
		x[active]=x[active]-abs(xlim[0])-abs(xlim[1]);
	if (y[active]<ylim[0])
		y[active]=y[active]-abs(ylim[0])-abs(ylim[1]);
}

void Tracer::initToFile(std::ofstream& f,const int &numSteps, const int &plotEvery){
	const int  headersize = 5*16;
	const int  cheadersize = 61;
	const char cheader[cheadersize+1] = "\x93NUMPY\1\0\x46\0{'descr': '<f4', 'fortran_order': False, 'shape': (";
	std::string header( cheader, cheader+cheadersize );

	f << header
		<< numSteps/plotEvery << ","
		<< 1        << ","
		<< 1        << "), }";
	int npadding = headersize - f.tellp() - 1;
	std::string padding = std::string( npadding, ' ' );
	f << padding << "\n";

}

void Tracer::toFile(std::ofstream& f){
	f.write( (char*) (&x[active]), x[active]*sizeof(float) );
	f.write( (char*) (&y[active]), y[active]*sizeof(float) );
//	f.write( (char*) vx[active], vx[active]*sizeof(float) );
//	f.write( (char*) vy[active], vy[active]*sizeof(float) );
//	f.write( (char*) fx, fx*sizeof(float) );
//	f.write( (char*) fy, fy*sizeof(float) );
}

void Tracer::toScreen(float time){
	std::cout << time << "\t" << x[active] << "\t" << y[active] << std::endl;
}

float Tracer::getx(){
	return x[active];
}

float Tracer::gety(){
	return y[active];
}

float Tracer::getvx(){
	return vx[active];
}

float Tracer::getvy(){
	return vy[active];
}

Tracer::~Tracer(){
	delete[] x;
	delete[] y;
	delete[] vx;
	delete[] vy;
	delete[] xlim;
	delete[] ylim;
}

