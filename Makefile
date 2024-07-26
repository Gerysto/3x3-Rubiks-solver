compile:

	g++ -c cube.cc
	g++ -c state.cc
	g++ -c main.cc
	
	g++ cube.o state.o main.o -o bin/program.exe
	rm -f *.o

	./bin/program.exe

	