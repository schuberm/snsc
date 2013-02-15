#include "diffusion.hh"
#include "cf.hh"
#include "del2op.hh"

Diffusion::Diffusion(float x1, float x2, float D, int numPoints){
	squaren=numPoints;
	theory=0;
	before=1;
	active=2;
	error=0.0;
	Dconst = D;
	rho=create3d(3,(squaren+2),(squaren+2));
	x=create1d(squaren+2);
	dx = (x2 - x1)/(squaren - 1);
	dt = dx*dx*D/5;
	for( int i = 0; i < squaren+2; i++ ) {
		x[i] = x1 + (i - 0.5)*dx;
	}
}

void Diffusion::init(float a0, float sigma0){
	for( int i = 0; i < squaren+2; i++ ) {
		for( int j = 0; j < squaren+2; j++ ) {
			rho[active][i][j] = a0*exp( -(pow(x[i],2) + pow(x[j],2))/(2*pow(sigma0,2)) );
		}
	}
}

void Diffusion::periodic(){
	for( int i = 0; i < squaren+2; i++ ) {
		rho[before][0][i]           = rho[before][squaren][i];
		rho[before][squaren+1][i] = rho[before][1][i];
		rho[before][i][0]           = rho[before][i][squaren];
		rho[before][i][squaren+1] = rho[before][i][1];
	}
}

void Diffusion::timeStep(){
	rhoint = 0.0; 
	std::swap( before, active);
	for( int i = 1; i < squaren+1; i++ ) {
		for( int j = 1; j < squaren+1; j++ ) {
			//(dx*dx) left out of del2op due to error bug
			rho[active][i][j] = rho[before][i][j]
				+ dt*Dconst/(dx*dx)*del2op(rho[before],i,j);
			rhoint += rho[active][i][j];
		}
	}
	rhoint *= pow(dx,2);        
}

void Diffusion::analytical(float D, float time, float sigma0, float a0, int numImages, int x1, int x2){
	float sigma = sqrt( 2*D*time + pow(sigma0,2) );
	float a     = a0 * pow(sigma0/sigma,2);
	for( int i = 0; i < squaren+2; i++ ) {
		for( int j = 0; j < squaren+2; j++ ) {
			float rhoValue = 0.0;
			for( int k = -numImages; k <= numImages; k++ ) {
				for( int l = -numImages; l <= numImages; l++ ) {
					float ximage = x[i] - k*(x2 - x1);
					float yimage = x[j] - l*(x2 - x1);
					rhoValue += a*exp(-(pow(ximage,2)+pow(yimage,2))
							/(2*pow(sigma,2)));
				}
			}
			rho[theory][i][j] = rhoValue;
		}
	}
}

void Diffusion::calcError(){
	error = 0.0;
	for (int i = 1; i <= squaren; i++ ) {
		for( int j = 1; j <= squaren; j++ ) {
			error += pow( rho[theory][i][j]-rho[active][i][j] , 2 );
		}
	}
	error = sqrt(error);
}

void Diffusion::initToFile(std::ofstream& f,const int &numSteps, const int &plotEvery){
	const int  headersize = 5*16;
	const int  cheadersize = 61;
	const char cheader[cheadersize+1] = "\x93NUMPY\1\0\x46\0{'descr': '<f4', 'fortran_order': False, 'shape': (";
	std::string header( cheader, cheader+cheadersize );

	f << header
		<< numSteps/plotEvery << ","
		<< squaren+2        << ","
		<< squaren+2        << "), }";
	int npadding = headersize - f.tellp() - 1;
	std::string padding = std::string( npadding, ' ' );
	f << padding << "\n";

}

void Diffusion::toFile(std::ofstream& f){
	assert(f.is_open());
	f.write( (char*)(rho[before][0]), 
			(squaren+2)*(squaren+2)*sizeof(float) );
}

void Diffusion::toScreen(float time, int step){
std::cout << "Step = "  << step  << ", "
<< "Time = "  << time  << ", "
<< "Error = " << error << ", "
<< "Integrated density = " << rhoint
<< std::endl;
} 

float** Diffusion::getRho(){
	return rho[active];
}

float Diffusion::getRhoij(int i, int j){
	return rho[active][i][j];	
} 

float* Diffusion::getx(){
	return x;
}

float Diffusion::getxi(int i){
	return x[i];
}

float Diffusion::getdx(){
	return dx;
}

float Diffusion::getdt(){
	return dt;
}

float Diffusion::geterror(){
	return error;
}

Diffusion::~Diffusion(){
	free3d(rho);
	free1d(x);
}
