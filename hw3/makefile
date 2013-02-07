CXX = g++
CFLAGS = -Wall -g -O0
LDFLAGS =
DEPS = del2op.hh cf.hh diffusion.hh tracer.hh
OBJ = del2op.o cf.o diffusion.o difftest.o tracertest.o combotest.o

%.o: %.cc $(DEPS)
	$(CXX) $(CFLAGS) -c -o $@ $<

#test diffusion.hh
difftest: difftest.o diffusion.o cf.o del2op.o
	$(CXX) $(CFLAGS) -o $@ $^
	./difftest

#test tracer.hh
tracertest: tracertest.o tracer.o cf.o
	$(CXX) $(CFLAGS) -o $@ $^
	./tracertest > output.txt

#test tracer+diffusion
combotest: combotest.o tracer.o diffusion.o cf.o del2op.o
	$(CXX) $(CFLAGS) -o $@ $^
	if command -v valgrind &>/dev/null; then\
		valgrind --tool=memcheck -v ./combotest;\
	else\
		./combotest;\
	fi

clean:
	rm -rf *o difftest tracertest combotest

