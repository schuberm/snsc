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
			rin[i*(xsize)+j]=((double)(r[index]));
			gin[i*(xsize)+j]=((double)(g[index]));
			bin[i*(xsize)+j]=((double)(b[index]));
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

	fftw_destroy_plan(fftr);
	fftw_destroy_plan(fftg);
	fftw_destroy_plan(fftb);
	
      for(int i=0; i<xsize;i++){
		for(int j=0; j<ysize;j++){
			if( rout[i*(xsize)+j]>xsize/8){
			rout[i*(xsize)+j]=0.0;
			}
			if( gout[i*(xsize)+j]>xsize/8){
			gout[i*(xsize)+j]=0.0;
			}
			if( bout[i*(xsize)+j]>xsize/8){
			bout[i*(xsize)+j]=0.0;
			}
		}
	}

	
	unsigned char* rchar = new unsigned char [xsize*ysize];
	unsigned char* gchar = new unsigned char [xsize*ysize];
	unsigned char* bchar = new unsigned char [xsize*ysize];
	
	fftw_plan fftr2 = fftw_plan_r2r_2d(xsize,ysize,rout,rin,FFTW_HC2R,FFTW_HC2R,FFTW_MEASURE);
	fftw_plan fftg2 = fftw_plan_r2r_2d(xsize,ysize,gout,gin,FFTW_HC2R,FFTW_HC2R,FFTW_MEASURE);
	fftw_plan fftb2 = fftw_plan_r2r_2d(xsize,ysize,bout,bin,FFTW_HC2R,FFTW_HC2R,FFTW_MEASURE);
	//fftw_plan p = fftw_plan_dft_r2c_2d(xsize,ysize,red,out,FFTW_MEASURE);

	fftw_execute(fftr2);
	fftw_execute(fftg2);
	fftw_execute(fftb2);

	delete [] rout;
	delete [] gout;
	delete [] bout;
	
	for(int i=0; i<xsize;i++){
		for(int j=0; j<ysize;j++){
			int index = i*xsize+j;
			rchar[i*(xsize)+j]=(unsigned char)(xsize*rin[index]);
			gchar[i*(xsize)+j]=(unsigned char)(xsize*gin[index]);
			bchar[i*(xsize)+j]=(unsigned char)(xsize*bin[index]);
		}
	}

	output.open ( file_out_name.c_str ( ), ios::binary );

	if ( !output )
	{
		cout << "\n";
		cout << "PPMB_WRITE: Fatal error!\n";
		cout << "  Cannot open the output file " << file_out_name << ".\n";
		return true;
	}
	error = ppmb_write_header ( output,xsize, ysize, 255 );

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
	error = ppmb_write_data ( output, xsize, ysize, rchar, gchar, bchar );

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

	return 0;
}
