CXX = g++
CXXFLAGS = -Wall -g -O0
LDFLAGS =
DEPS =
OBJ = 

%.o: %.cc
	$(CXX) $(CXXFLAGS) -c -o $@ $<

sumone.o: sumone.cc

sumreverse.o: sumreverse.cc	

sumone: sumone.o
	$(CXX) $(CXXFLAGS) -o $@ $^
	./sumone

sumreverse: sumreverse.o
	$(CXX) $(CXXFLAGS) -o $@ $^
	./sumreverse

clean:
	rm -rf *.o sumone sumreverse

