//
// processppm.cc - blurs an input ppm image.
//
// usage: processppm INPUT-PPM OUTPUT-PPM BLUR-RADIUS NUMBER-OF-THREADS
//
#include "ppm.h"
#include <omp.h>
#include <cmath>
#include <cstdlib>
#include <iostream>

int main(int argc, char** argv) 
{
    using std::endl;
    using std::cerr;

    if (argc!=5)  {
        cerr << argv[0] << ": Incorrect arguments" << endl
             << "Usage:" << endl
             << "  " << argv[0] 
             << " INPUT-PPM OUTPUT-PPM BLUR-RADIUS NUMBER-OF-THREADS"
             << endl;
        return 1;
    }

    const int nth = atoi(argv[4]);

    // create ppm object
    Ppm ppm;

    // read file
    int error = ppm.read(argv[1], nth);

    if (error != 0) {

        cerr << "Aborting" << endl;
        return 6;

    } else {

        // create new ppm object
        Ppm ppm2(ppm.getHeight(), ppm.getWidth());

        // blur
        const int dia = atoi(argv[3]);
        const float sigma = dia/3.0;
       #pragma omp parallel for num_threads(nth)
        for (int r=0;r<ppm.getHeight();r++) {
            for (int c=0;c<ppm.getWidth();c++) {
                float red = 0.0;
                float green = 0.0;
                float blue = 0.0;
                for (int dr=-dia;dr<=dia;dr++) {
                    for (int dc=-dia;dc<=dia;dc++) {
                        int r2 = r+dr;
                        int c2 = c+dc;
                        if (r2>=0 and r2<ppm.getHeight() and
                            c2>=0 and c2<ppm.getWidth() ) {
                            float factor = exp(-(dc*dc+dr*dr)/(2.0*sigma))/(2*M_PI*sigma);
                            red   += factor*ppm.getRed()[r2][c2];
                            green += factor*ppm.getGreen()[r2][c2];
                            blue  += factor*ppm.getBlue()[r2][c2];
                        }
                    }
                }
                if (red>255) red=255;
                if (green>255) green=255;
                if (blue>255) blue=255;
                ppm2.getRed()[r][c] = red;
                ppm2.getGreen()[r][c] = green;
                ppm2.getBlue()[r][c] = blue;
            }
        }        

        ppm2.write(argv[2], nth);
    }

    return 0; 
}
