//output.hh

#ifndef __OUTPUT_HH_INCLUDED
#define __OUTPUT_HH_INCLUDED

void outputInitial(std::ofstream &theoryFile, const std::string &header, const int &headersize, const int &numSteps, const int &plotEvery, const int &numPoints);

void outputBasic(std::ofstream &basicFile, const int &step, const float &time, const float &error, const float &rhoint);

#endif
