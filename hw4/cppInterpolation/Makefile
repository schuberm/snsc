CXX=g++
CXXFLAGS=-Wall -O3
LDFLAGS=
LDLIBS=

OBJS= array.o interpolation_test.o interpolation.o

all: interpolation_test

interpolation_test: $(OBJS)
	$(CXX) $(LDFLAGS) -o $@ $^ $(LDLIBS) 

array.o: array.cc array.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

interpolation.o: interpolation.cc interpolation.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

interpolation_test.o: interpolation_test.cc array.h interpolation.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

test: interpolation_test
	./interpolation_test

clean:
	\rm -f $(OBJS)
