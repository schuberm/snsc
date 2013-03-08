CXX = g++
CXXFLAGS = -Wall -g -O0
IFLAGS = -I/usr/local/include
LDFLAGS = -L/usr/local/lib
DEPS =
OBJ = 
LIBS = -lgsl -lgslcblas

%.o: %.cc
	$(CXX) $(LDFLAGS) $(IFLAGS) $(CXXFLAGS) -c -o $@ $<

odeexample.o: odeexample.cc

lorenz.o: lorenz.cc

#gsl example
odeexample: odeexample.o
	$(CXX) $(LDFLAGS) $(IFLAGS) $(CXXFLAGS) -o $@ $^ $(LIBS)
	./odeexample

lorenz: lorenz.o
	$(CXX) $(LDFLAGS) $(IFLAGS) $(CXXFLAGS) -o $@ $^ $(LIBS)
	./lorenz > output.txt
	python plotlorenz.py

clean:
	rm -rf *.o odeexample lorenz

