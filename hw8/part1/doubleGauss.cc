# include <cstdlib>
# include <iostream>
# include <iomanip>
# include <fstream>
# include <ctime>
# include <fftw3.h>
# include <complex>
using namespace std;

# include "ppmb_io.hpp"

int main ()
{
	string file_in_name;
	string file_out_name;
	
	unsigned char *b;
	bool error;
	ifstream file_in;
	ofstream output;
	unsigned char *g;
	int maxrgb;
	unsigned char *r;
	int xsize;
	int ysize;

	file_in_name="gauss256.ppm";
	file_out_name="2gauss.ppm";


	file_in.open ( file_in_name.c_str ( ) );

	if ( !file_in ) 
	{
		cout << "\n";
		cout << "TEST02 - Fatal error!\n";
		cout << "  Could not open the file " << file_in_name << "\n";
		return true;
	}

	error = ppmb_read_header ( file_in, xsize, ysize, maxrgb );

	r = new unsigned char[ xsize * ysize ];
	g = new unsigned char[ xsize * ysize ];
	b = new unsigned char[ xsize * ysize ];

	error = ppmb_read_data ( file_in, xsize, ysize, r, g, b );

	if ( error )
	{
		cout << "\n";
		cout << "  PPMB_READ_DATA failed!\n";
		return error;
	}

	cout << "\n";
	cout << "  The data was read successfully.\n";
	file_in.close();

	double* rin = new double [xsize*ysize];
	double* gin = new double [xsize*ysize];
	double* bin = new double [xsize*ysize];
	double* rout = new double [xsize*ysize];
	double* gout = new double [xsize*ysize];
	double* bout = new double [xsize*ysize];


	for(int i=0; i<xsize;i++){
		for(int j=0; j<ysize;j++){
			int index = i*xsize+j;
			rin[i*(xsize)+j]=(double)(r[index]);
			gin[i*(xsize)+j]=(double)(g[index]);
			bin[i*(xsize)+j]=(double)(b[index]);
		}
	}
	
	delete [] r;
	delete [] g;
	delete [] b;
	
	fftw_plan fftr = fftw_plan_r2r_2d(xsize,ysize,rin,rout,FFTW_R2HC,FFTW_R2HC,FFTW_MEASURE);
	fftw_plan fftg = fftw_plan_r2r_2d(xsize,ysize,gin,gout,FFTW_R2HC,FFTW_R2HC,FFTW_MEASURE);
	fftw_plan fftb = fftw_plan_r2r_2d(xsize,ysize,bin,bout,FFTW_R2HC,FFTW_R2HC,FFTW_MEASURE);
	//fftw_plan p = fftw_plan_dft_r2c_2d(xsize,ysize,red,out,FFTW_MEASURE);

	fftw_execute(fftr);
	fftw_execute(fftg);
	fftw_execute(fftb);

	delete [] rin;
	delete [] gin;
	delete [] bin;
	
	unsigned char* rchar = new unsigned char [xsize*ysize];
	unsigned char* gchar = new unsigned char [xsize*ysize];
	unsigned char* bchar = new unsigned char [xsize*ysize];
	
	for(int i=0; i<xsize;i++){
		for(int j=0; j<ysize;j++){
			int index = i*xsize+j;
			rchar[i*(xsize)+j]=(unsigned char)(rout[index]);
			gchar[i*(xsize)+j]=(unsigned char)(gout[index]);
			bchar[i*(xsize)+j]=(unsigned char)(bout[index]);
		}
	}
	
	unsigned char* r2char = new unsigned char[ 4*xsize * ysize ];
	unsigned char* g2char = new unsigned char[ 4*xsize * ysize ];
	unsigned char* b2char = new unsigned char[ 4*xsize * ysize ];
	double* r2 = new double [4*xsize*ysize];
	double* g2 = new double [4*xsize*ysize];
	double* b2 = new double [4*xsize*ysize];
	double* r2out = new double [4*xsize*ysize];
	double* g2out = new double [4*xsize*ysize];
	double* b2out = new double [4*xsize*ysize];
	
	for(int i=0; i<2*xsize;i++){
		for(int j=0; j<2*ysize;j++){
				r2[i*(2*xsize)+j]=0.0;
				g2[i*(2*xsize)+j]=0.0;
				b2[i*(2*xsize)+j]=0.0;
			}
	}
/*	for(int i=0; i<xsize;i++){
		for(int j=0; j<ysize;j++){
		if (j<ysize/2 && i<xsize/2){
				r2[i*(2*xsize)+j]=rout[i*xsize+j];
				g2[i*(2*xsize)+j]=gout[i*xsize+j];
				b2[i*(2*xsize)+j]=bout[i*xsize+j];
			}
		if (j>=ysize/2 && i<xsize/2){
				r2[i*(2*xsize)+j+3*ysize/2]=rout[i*xsize+j];
				g2[i*(2*xsize)+j+3*ysize/2]=gout[i*xsize+j];
				b2[i*(2*xsize)+j+3*ysize/2]=bout[i*xsize+j];
			}
		if (j<ysize/2 && i>=xsize/2 && i<xsize){
				r2[i*(2*xsize)+2*xsize*3*ysize/2+j]=rout[i*xsize+j];
				g2[i*(2*xsize)+2*xsize*3*ysize/2+j]=gout[i*xsize+j];
				b2[i*(2*xsize)+2*xsize*3*ysize/2+j]=bout[i*xsize+j];
			}
		if (j>=ysize/2 && i>=xsize/2 && j<ysize && i<xsize){
				r2[i*(2*xsize)+2*xsize*3*ysize/2+j+3*ysize/2]=rout[i*xsize+j];
				g2[i*(2*xsize)+2*xsize*3*ysize/2+j+3*ysize/2]=gout[i*xsize+j];
				b2[i*(2*xsize)+2*xsize*3*ysize/2+j+3*ysize/2]=bout[i*xsize+j];
			}
		
		}
	}
*/	
	for(int i=0; i<xsize;i++){
		for(int j=0; j<ysize;j++){
		if (j<ysize/2 && i<xsize/2){
				r2[i*(2*xsize)+j]=rout[i*xsize+j];
				g2[i*(2*xsize)+j]=gout[i*xsize+j];
				b2[i*(2*xsize)+j]=bout[i*xsize+j];
			}
		if (j>=ysize/2 && i<xsize/2 ){
				r2[i*(2*xsize)+ysize+ysize/2+j]=rout[i*xsize+j];
				g2[i*(2*xsize)+ysize+ysize/2+j]=gout[i*xsize+j];
				b2[i*(2*xsize)+ysize+ysize/2+j]=bout[i*xsize+j];
			}
		if (j<ysize/2 && i>=xsize/2 ){
				r2[(i+xsize+xsize/2)*(2*xsize)+j]=rout[i*xsize+j];
				g2[(i+xsize+xsize/2)*(2*xsize)+j]=gout[i*xsize+j];
				b2[(i+xsize+xsize/2)*(2*xsize)+j]=bout[i*xsize+j];
			}
		if (j>=ysize/2 && i>=xsize/2 ){
				r2[(i+xsize+xsize/2)*(2*xsize)+ysize+ysize/2+j]=rout[i*xsize+j];
				g2[(i+xsize+xsize/2)*(2*xsize)+ysize+ysize/2+j]=gout[i*xsize+j];
				b2[(i+xsize+xsize/2)*(2*xsize)+ysize+ysize/2+j]=bout[i*xsize+j];
			}
		
		}
	}

	fftw_destroy_plan(fftr);
	fftw_destroy_plan(fftg);
	fftw_destroy_plan(fftb);

	fftw_plan fftr2 = fftw_plan_r2r_2d(2*xsize,2*ysize,r2,r2out,FFTW_HC2R,FFTW_HC2R,FFTW_MEASURE);
	fftw_plan fftg2 = fftw_plan_r2r_2d(2*xsize,2*ysize,g2,g2out,FFTW_HC2R,FFTW_HC2R,FFTW_MEASURE);
	fftw_plan fftb2 = fftw_plan_r2r_2d(2*xsize,2*ysize,b2,b2out,FFTW_HC2R,FFTW_HC2R,FFTW_MEASURE);
	//fftw_plan p = fftw_plan_dft_r2c_2d(xsize,ysize,red,out,FFTW_MEASURE);

	fftw_execute(fftr2);
	fftw_execute(fftg2);
	fftw_execute(fftb2);

	delete [] rout;
	delete [] gout;
	delete [] bout;

	for(int i=0; i<2*xsize;i++){
		for(int j=0; j<2*ysize;j++){	
				r2out[i*(2*xsize)+j]=(xsize*ysize)*r2out[i*(2*xsize)+j];
				g2out[i*(2*xsize)+j]=(xsize*ysize)*g2out[i*(2*xsize)+j];
				b2out[i*(2*xsize)+j]=(xsize*ysize)*b2out[i*(2*xsize)+j];
				r2char[i*(2*xsize)+j]=(unsigned char)(r2out[i*(2*xsize)+j]);
				g2char[i*(2*xsize)+j]=(unsigned char)(g2out[i*(2*xsize)+j]);
				b2char[i*(2*xsize)+j]=(unsigned char)(b2out[i*(2*xsize)+j]);
		}
	}	
	fftw_destroy_plan(fftr2);
	fftw_destroy_plan(fftg2);
	fftw_destroy_plan(fftb2);
	
	output.open ( file_out_name.c_str ( ), ios::binary );

	if ( !output )
	{
		cout << "\n";
		cout << "PPMB_WRITE: Fatal error!\n";
		cout << "  Cannot open the output file " << file_out_name << ".\n";
		return true;
	}
	error = ppmb_write_header ( output,2*xsize, 2*ysize, 255 );

	if ( error )
	{
		cout << "\n";
		cout << "PPMB_WRITE: Fatal error!\n";
		cout << "  PPMB_WRITE_HEADER failed.\n";
		return true;
	}
	//
	//  Write the data.
	//
	error = ppmb_write_data ( output, 2*xsize, 2*ysize, r2char, g2char, b2char );

	if ( error )
	{
		cout << "\n";
		cout << "PPMB_WRITE: Fatal error!\n";
		cout << "  PPMB_WRITE_DATA failed.\n";
		return true;
	}
	//
	//  Close the file.
	//
	output.close ( );

	//ppmb_write(file_out_name, xsize,ysize,(unsigned char*)((rin)),(unsigned char*)((double*)(g)),(unsigned char*)((double*)(b)));

	delete [] r2;
	delete [] g2;
	delete [] b2;
	delete [] r2out;
	delete [] g2out;
	delete [] b2out;
	delete [] r2char;
	delete [] g2char;
	delete [] b2char;


	return 0;
}
