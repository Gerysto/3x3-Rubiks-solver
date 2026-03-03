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

# Include auto-generated header dependencies
-include $(DEPS)
