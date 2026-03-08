CXX := g++
CXXFLAGS := -O2 -MMD -MP

SRCS := $(wildcard src/*.cc)
OBJS := $(SRCS:src/%.cc=bin/%.o)
DEPS := $(OBJS:.o=.d)

TARGET := bin/program.exe

# Default target
all: $(TARGET)

# Link step
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $@

# Compile step (pattern rule)
bin/%.o: src/%.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean target
clean:
	rm -f bin/*.o bin/*.d $(TARGET)

# Run target
run: $(TARGET)
	./$(TARGET)

wasm:
	emcc src/cube.cc src/mathlib.cc src/move_sequence.cc src/orientation.cc src/solver.cc src/state.cc -o bin/cube_lib.js -s MODULARIZE=1 -s EXPORT_NAME="createModule" --bind

	cp bin/cube_lib.js ../Viewer/libs/cube_lib.js
	cp bin/cube_lib.wasm ../Viewer/libs/cube_lib.wasm

# Include auto-generated header dependencies
-include $(DEPS)
