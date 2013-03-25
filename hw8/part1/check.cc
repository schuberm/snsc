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

	unsigned char *rtest = new unsigned char [xsize*ysize];

	for(int i=0; i<xsize;i++){
		for(int j=0; j<ysize;j++){
			int index = i*xsize+j;
			rin[i*(xsize)+j]=(double)(r[index]);
			gin[i*(xsize)+j]=(double)(g[index]);
			bin[i*(xsize)+j]=(double)(b[index]);
			rtest[i*(xsize)+j]=(unsigned char)(rin[index]);
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
	error = ppmb_write_header ( output, xsize, ysize, 255 );

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
	error = ppmb_write_data ( output, xsize, ysize, rtest, g, b );

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


	delete [] r;
	delete [] g;
	delete [] b;

	return 0;
}
