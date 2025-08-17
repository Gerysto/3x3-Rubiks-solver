compile:
	g++ bin/cube.o -c src/cube.cc 
	g++ bin/state.o -c src/state.cc 
	g++ bin/move_sequence.o -c src/move_sequence.cc 
	g++ bin/orientation.o -c src/orientation.cc 
	g++ bin/main.o -c src/main.cc 
	g++ bin/solver.o -c src/solver.cc 

	g++ bin/solver.o bin/cube.o bin/state.o bin/move_sequence.o bin/orientation.o bin/main.o -o bin/program.exe
clean:
	rm -f *.o *.exe
run:
	./bin/program.exe

	