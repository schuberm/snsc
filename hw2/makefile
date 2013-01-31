CXX = g++
CFLAGS = -Wall
LDFLAGS =
DEPS = del2op.hh analytical2dDiff.hh cf.hh output.hh icbc.hh
OBJ = diffuse.o constrho.o linrho.o linrho2.o icbctest.o del2op.o analytical2dDiff.o cf.o output.o icbc.o

%.o: %.cc $(DEPS)
	$(CXX) $(CFLAGS) -c -o $@ $<

testall: diffuse.o del2op.o analytical2dDiff.o cf.o output.o icbc.o
	$(CXX) $(CFLAGS) -o $@ $^
	./testall
	diff -q original-output.txt output.txt
	diff -q original-data.npy data.npy
	diff -q original-theory.npy theory.npy
	rm -rf *o test

#test del2op
constrho: constrho.o del2op.o cf.o
	$(CXX) $(CFLAGS) -o $@ $^
	./constrho  > constrho-output.txt
	grep -o "Rho change.*" constrho-output.txt
	rm -rf *o constrho

linrho: linrho.o del2op.o cf.o
	$(CXX) $(CFLAGS) -o $@ $^
	./linrho  > linear-output.txt
	grep -o "Rho change.*" linear-output.txt
	rm -rf *o linrho

linrho2: linrho2.o del2op.o cf.o analytical2dDiff.o
	$(CXX) $(CFLAGS) -o $@ $^
	./linrho2  > linear-output.txt
	grep -o "Rho change.*" linear-output.txt
	rm -rf *o linrho2

#test initial and boundary conditions
icbctest: icbctest.o del2op.o cf.o icbc.o
	$(CXX) $(CFLAGS) -o $@ $^
	./icbctest  > icbctest-output.txt
	#grep -o "Rho change.*" icbctest-output.txt
	rm -rf *o icbc

clean:
	rm -rf *o diffuse testall constrho linrho linrho2 icbctest

