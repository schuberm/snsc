CXX = g++
CXXFLAGS = -Wall -g -O0
IFLAGS = -I/usr/local/include
LDFLAGS = -L/usr/local/lib
DEPS =
OBJ = 
LIBS = -lgsl -lgslcblas

%.o: %.cc
	$(CXX) $(LDFLAGS) $(IFLAGS) $(CXXFLAGS) -c -o $@ $<

randcomp.o: randcomp.cc

lcgmt.o: lcgmt.cc

array.o: array.cc

radius.o: radius.cc

#gsl example
randcomp: randcomp.o
	$(CXX) $(LDFLAGS) $(IFLAGS) $(CXXFLAGS) -o $@ $^ $(LIBS)
	./randcomp

#lcgmt
lcgmt: lcgmt.o array.o
	$(CXX) $(LDFLAGS) $(IFLAGS) $(CXXFLAGS) -o $@ $^ $(LIBS)
	./lcgmt
	python paircomp.py

#radius
radius: radius.o array.o
	$(CXX) $(LDFLAGS) $(IFLAGS) $(CXXFLAGS) -o $@ $^ $(LIBS)
	./radius
	python anglecomp.py

clean:
	rm -rf *.o randcomp lcgmt radius

