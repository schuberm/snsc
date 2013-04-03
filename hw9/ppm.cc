// ppm.cc - implementation for ppm
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <omp.h>
#include "ppm.h"
#include "array3d.h"

Ppm::Ppm()
{
    h = 0;
    w = 0;
    rgb = 0;
    max = 255;
}

Ppm::Ppm(int ah, int aw)
{
    h = ah;
    w = aw;
    rgb = allocate3d<byte>(3,h,w);
    max = 255;
}

//
// free the internal structure of the ppm
//
Ppm::~Ppm() 
{
    deallocate3d(rgb);
}

//
// get 2d array of red values
//
byte** Ppm::getRed()
{
    return rgb[0];
}

//
// get 2d array of green values
//
byte** Ppm::getGreen()
{
    return rgb[1];
}

//
// get 2d array of blue values
//
byte** Ppm::getBlue()
{
     return rgb[2];
}

//
// get the width of the image
//
int Ppm::getWidth()
{
    return w;
}

//
// get height of the image
//
int Ppm::getHeight()
{
    return h;
}

//
// Read a ppm (with lots of error checking)
//
int Ppm::read(const char* name, const int nth)
{
    if (name == 0 or name[0] == '\0') {
        std::cerr << "ERROR: nothing to read ppm to or from." << std::endl;
        return 1;
    }

    // open the file
    std::ifstream f(name, std::ios::binary);

    if (not f.is_open()) {
        std::cerr << "ERROR: file " << name
                  << "could not be opened" << std::endl;
        return 1;
    }

    // check the header
  
    const int MAGICBYTES = 3;   
    char magic[MAGICBYTES] = {'P','6','\n'};
    char check[MAGICBYTES] = {'-','-','-'};

    f.read(check, MAGICBYTES);

    for (int i = 0; i < MAGICBYTES; i++) {
        if (magic[i] != check[i]) {
            std::cerr << "ERROR: header incorrect" << std::endl;;
            return 2;
        }
    }

    // read the line with width and height information
    const int maxlinelen = 256; 
    char line[maxlinelen]; 

    do {
        f.getline(line, maxlinelen);        
    } while (line[0] == '#' and not f.eof() ); // skip comment lines

    // check if a non-comment line was found
    if (f.eof()) {
        std::cerr <<  "ERROR: reading past eof" << std::endl;
        return 3;
    }

    // we get here if a non-comment line was found, from which we'll
    // read the width and height now
 
    unsigned int neww, newh;
    sscanf(line, "%d%d", &neww, &newh);

    const int RIDICULOUSLY_LARGE_SIZE = 1e8;
    if (neww > RIDICULOUSLY_LARGE_SIZE or newh > RIDICULOUSLY_LARGE_SIZE) {
        std::cerr << "ERROR: sizes improbably large (" << neww << " x " << newh << ")" << std::endl;
        return 4;
    }

    // read the next non-comment line, which has the maximum value of
    // the color values
    do {
        f.getline(line, maxlinelen);        
    } while (line[0] == '#' and not f.eof() ); // skip comments

    // check if a non-comment line was found
    if (f.eof()) {
        std::cerr << "ERROR: reading past eof" << std::endl;
        return 4;
    }

    // if so, extract maximum.
    int newmax;
    sscanf(line, "%d", &newmax);

    if (newmax > 255 or newmax < 0) {
        std::cerr << "ERROR: max value out of bounds (" << max 
                  << " not in [0:255])" << std::endl;
        return 4;
    }

    // should check file size first at this point. LATER   
    byte*** newrgb = allocate3d<byte>(newh,neww,3);

    if (newrgb == 0) {
        std::cerr << "ERROR: could not allocate memory for image" << std::endl;
        return 6;
    }

    // read pixel data
    f.read((char*)(&newrgb[0][0][0]), 3*newh*neww);

    if (f.eof()) {
        std::cerr << "ERROR: reading past eof\n";
        return 6;
    }

    // copy (transpose) so all r, and b values are together and store in object
    w = neww;
    h = newh;
    deallocate3d(rgb);
    rgb = allocate3d<byte>(3,h,w);
    for (int color=0;color<3;color++)
        #pragma omp parallel for num_threads(nth)
        for (int r=0;r<h;r++)
            for (int c=0;c<w;c++) 
                rgb[color][r][c] = newrgb[r][c][color];
    deallocate3d(newrgb);

    // signal that all's well.
    return 0;
}

//
// Write the ppm.
//
int Ppm::write(const char* name, const int nth)
{
    std::ofstream f(name,std::ios::binary);

    if (not f.is_open()) {
        std::cerr << "ERROR: file " << name 
                  << " could not be opened" << std::endl;
        return 1;
    }

    f << "P6\n" << w << ' ' << h << '\n' << unsigned(max) << '\n';

    if (not f.good()) {
        std::cerr << "ERROR: file " << name << " could not be written to.\n";
    }

    // transpose before writing
    byte*** newrgb = allocate3d<byte>(h,w,3);
    for (int color=0;color<3;color++)
        #pragma omp parallel for num_threads(nth)
        for (int r=0;r<h;r++)
            for (int c=0;c<w;c++) 
                newrgb[r][c][color] = rgb[color][r][c];

    // write to file
    f.write((char*)(&newrgb[0][0][0]), 3*h*w);
    deallocate3d(newrgb);

    if (f.eof() or not f.good()) {
        std::cerr << "ERROR: in writing " << name << std::endl;
        return 6;
    }

    // signal that all's well.
    return 0;
}
