// ppm.h - header file for ppm with prototype declarations 
#ifndef _PPM_HH_
#define _PPM_HH_

#include "bytedef.h"

class Ppm {
  public:
    Ppm();
    Ppm(int ah, int aw);
    ~Ppm();
    byte**  getRed();    // get 2d array of red values
    byte**  getGreen();  // get 2d array of green values
    byte**  getBlue();   // get 2d array of blue values
    int     getHeight(); // height of the image
    int     getWidth();  // width of the image
    int     read (const char* name, int nth=1); // read from file
    int     write(const char* name, int nth=1); // write to file
  private:
    int     h;      // height of the image
    int     w;      // width of the image
    byte*** rgb;    // 3d array of the red values, green values, blue values
    byte   max;     // maximal value of the above
};

#endif
