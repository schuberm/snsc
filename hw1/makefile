CXX = g++
CFLAGS = -Wall
LDFLAGS =
DEPS = cf.hh genGaussian.hh printGaussian.hh
OBJ = main.o cf.o genGaussian.o printGaussian.o

%.o: %.cc $(DEPS)
	$(CXX) $(CFLAGS) -c -o $@ $<

main: $(OBJ)
	$(CXX) $(CFLAGS) -o $@ $^
clean:
	rm -rf *o main

