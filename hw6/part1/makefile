CXX = g++
CXXFLAGS = -Wall -g -O0
IFLAGS = -I/usr/local/include
LDFLAGS = -L/usr/local/lib
DEPS =
OBJ = 
LIBS = -lgsl -lgslcblas

%.o: %.cc
	$(CXX) $(LDFLAGS) $(IFLAGS) $(CXXFLAGS) -c -o $@ $<

intexample.o: intexample.cc

intcomp.o: intcomp.cc

#gsl example
intexample: intexample.o
	$(CXX) $(LDFLAGS) $(IFLAGS) $(CXXFLAGS) -o $@ $^ $(LIBS)
	./intexample

mcexample: mcexample.o
	$(CXX) $(LDFLAGS) $(IFLAGS) $(CXXFLAGS) -o $@ $^ $(LIBS)
	./mcexample

intcomp: intcomp.o
	$(CXX) $(LDFLAGS) $(IFLAGS) $(CXXFLAGS) -o $@ $^ $(LIBS)
	./intcomp

clean:
	rm -rf *.o intexample mcexample intcomp

