CXX = g++
CXXFLAGS = -Wall -g -O0
IFLAGS = -I/usr/local/include
LDFLAGS = -L/usr/local/lib
DEPS =
OBJ = 
LIBS = -llapacke -llapack -lblas -lgfortran

%.o: %.cc
	$(CXX) $(LDFLAGS) $(IFLAGS) $(CXXFLAGS) -c -o $@ $<

lptest.o: lptest.cc

eigofA.o: eigofA.cc

#lapacke example
lptest: lptest.o
	$(CXX) $(LDFLAGS) $(IFLAGS) $(CXXFLAGS) -o $@ $^ $(LIBS)
	./lptest

eigofA: eigofA.o
	$(CXX) $(LDFLAGS) $(IFLAGS) $(CXXFLAGS) -o $@ $^ $(LIBS)
	./eigofA
	python eigplot.py

clean:
	rm -rf *.o lptest eigofA

