CXX = g++
CXXFLAGS = -Wall -g -O0
IFLAGS = -I/usr/local/include
LDFLAGS = -L/usr/local/lib
DEPS =
OBJ = 
LIBS = -lgsl -lgslcblas

%.o: %.cc
	$(CXX) $(LDFLAGS) $(IFLAGS) $(CXXFLAGS) -c -o $@ $<

evolve.o: evolve.cc

#gsl example
evolve: evolve.o
	$(CXX) $(LDFLAGS) $(IFLAGS) $(CXXFLAGS) -o $@ $^ $(LIBS)
	./evolve > output.txt
	python qplot.py

clean:
	rm -rf *.o evolve

