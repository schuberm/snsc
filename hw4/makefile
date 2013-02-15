CXX = g++
CXXFLAGS = -Wall -g -O0
LDFLAGS =
DEPS = del2op.hh cf.hh diffusion.hh tracer.hh interpolation.h
OBJ = del2op.o cf.o diffusion.o difftest.o tracertest.o combotest.o coupled.o

%.o: %.cc
	$(CXX) $(CXXFLAGS) -c -o $@ $<

cf.o: cf.cc cf.hh

combotest.o: combotest.cc diffusion.hh tracer.hh

del2op.o: del2op.cc del2op.hh

difftest.o: difftest.cc diffusion.hh

diffusion.o: diffusion.cc diffusion.hh cf.hh del2op.hh

output.o: output.cc output.hh

tracer.o: tracer.cc tracer.hh

tracertest.o: tracertest.cc tracer.hh

#test diffusion.hh
difftest: difftest.o diffusion.o cf.o del2op.o
	$(CXX) $(CXXFLAGS) -o $@ $^
	./difftest

#test tracer.hh
tracertest: tracertest.o tracer.o cf.o interpolation.o
	$(CXX) $(CXXFLAGS) -o $@ $^
	./tracertest > output-tracer.txt
	python < tracertest.py	

#test tracer+diffusion
combotest: combotest.o tracer.o diffusion.o cf.o del2op.o interpolation.o
	$(CXX) $(CXXFLAGS) -o $@ $^
	if command -v valgrind &>/dev/null; then\
		valgrind --tool=memcheck -v ./combotest;\
	else\
		./combotest;\
	fi

#test coupled via interpolation
coupled: coupled.o tracer.o diffusion.o cf.o del2op.o interpolation.o
	$(CXX) $(CXXFLAGS) -o $@ $^
	./coupled > particle.txt
	python < tracerplot.py

clean:
	rm -rf *.o difftest tracertest combotest coupled

