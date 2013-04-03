CXX=g++
CXXFLAGS = -O3 -march=native -fopenmp
LDFLAGS=-fopenmp
all: blurppm

blurppm: ppm.o blurppm.o
	$(CXX) $(LDFLAGS) -g -o $@ $^

clean:
	\rm -f ppm.o blurppm.o

ppm.o: ppm.cc ppm.h bytedef.h array3d.h
blurppm.o: blurppm.cc ppm.h bytedef.h
