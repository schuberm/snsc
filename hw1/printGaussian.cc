//test.cc
#include <iostream>
#include <fstream>
#include "printGaussian.hh"
using namespace std;

void printGaussian(const int &n, float **gaussian)
{
	ofstream myfile ("data.txt");
	if (myfile.is_open())
	{
		for(int i=0; i<n; i++)
		{
			for(int j=0; j<n; j++)
			{
			myfile << gaussian[i][j];
			myfile << "\t";
			}
			myfile << "\n";	
		}
		myfile.close();
	}
	else cout <<"Unable to open file";
}

