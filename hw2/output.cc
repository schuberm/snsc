#include <iostream>
#include <fstream>
#include "output.hh"

void outputInitial(std::ofstream &theoryFile, const std::string &header, const int &headersize, const int &numSteps, const int &plotEvery, const int &numPoints){
	theoryFile << header
		<< numSteps/plotEvery << ","
		<< numPoints+2        << ","
		<< numPoints+2        << "), }";
	int npadding = headersize - theoryFile.tellp() - 1;
	std::string padding = std::string( npadding, ' ' );
	theoryFile << padding << "\n";
}

void outputBasic(std::ofstream &basicFile, const int &step, const float &time, const float &error, const float &rhoint){
	basicFile	<< "Step = "  << step  << ", "
                        << "Time = "  << time  << ", "
                        << "Error = " << error << ", "
                        << "Integrated density = " << rhoint
                        << std::endl;
}
