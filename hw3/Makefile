Compiler = g++
Compile_flgs = -std=c++11 -Wall

all: opts

opts: opts.o
	$(Compiler) $(Compile_flgs) opts.o -o $@

opts.o: opts.cc
	$(Compiler) $(Compile_flgs) -c opts.cc
	
clean:
	rm -f *.o *~ opts
	