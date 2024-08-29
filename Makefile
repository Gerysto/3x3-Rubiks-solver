compile:

	g++ -c src/cube.cc
	g++ -c src/state.cc
	g++ -c src/move_sequence.cc
	g++ -c src/orientation.cc
	g++ -c src/main.cc
	g++ -c src/solver.cc

	g++ solver.o cube.o state.o move_sequence.o orientation.o main.o -o bin/program.exe

	rm -f *.o

	./bin/program.exe

	