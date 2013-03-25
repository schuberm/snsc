CXX = g++
CXXFLAGS = -Wall -g -O0
IFLAGS = -I/usr/local/include
LDFLAGS = -L/usr/local/lib
DEPS =
OBJ = 
LIBS = -lfftw3 -lm 

%.o: %.cc
	$(CXX) $(LDFLAGS) $(IFLAGS) $(CXXFLAGS) -c -o $@ $<

1dFFT.o: 1dFFT.cc

ppmb_io.o: ppmb_io.cpp

ppmb_io_prb.o: ppmb_io_prb.cpp

doubleGauss.o: doubleGauss.cc

check.o: check.cc
debug.o: debug.cc
singleGauss.o: singleGauss.cc
filter.o: filter.cc
#fftw example
fft: 1dFFT.o
	$(CXX) $(LDFLAGS) $(IFLAGS) $(CXXFLAGS) -o $@ $^ $(LIBS)

#ppmb example
ppmb: ppmb_io_prb.o ppmb_io.o
	$(CXX) $(LDFLAGS) $(IFLAGS) $(CXXFLAGS) -o $@ $^ $(LIBS)

dG: doubleGauss.o ppmb_io.o
	$(CXX) $(LDFLAGS) $(IFLAGS) $(CXXFLAGS) -o $@ $^ $(LIBS)
	./dG
	display 2gauss.ppm

check: check.o ppmb_io.o
	$(CXX) $(LDFLAGS) $(IFLAGS) $(CXXFLAGS) -o $@ $^ $(LIBS)
	./check
	display 2gauss.ppm

sG:singleGauss.o ppmb_io.o
	$(CXX) $(LDFLAGS) $(IFLAGS) $(CXXFLAGS) -o $@ $^ $(LIBS)
	./sG	
	display 2gauss.ppm

filter:filter.o ppmb_io.o
	$(CXX) $(LDFLAGS) $(IFLAGS) $(CXXFLAGS) -o $@ $^ $(LIBS)
	./filter	
	display 2gauss.ppm

debug: debug.o ppmb_io.o
	$(CXX) $(LDFLAGS) $(IFLAGS) $(CXXFLAGS) -o $@ $^ $(LIBS)
	./debug	
	display 2gauss.ppm

clean:
	rm -rf *.o ppmb dG fft core check debug sG filter
