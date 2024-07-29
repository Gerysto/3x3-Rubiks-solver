compile:

	g++ -c src/cube.cc
	g++ -c src/state.cc
	g++ -c src/move_sequence.cc
	g++ -c src/orientation.cc
	g++ -c src/main.cc
	
	g++ cube.o state.o main.o -o bin/program.exe
	rm -f *.o

	./bin/program.exe

	