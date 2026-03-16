CXX := g++
CXXFLAGS := -O2 -MMD -MP
#CXXFLAGS := -g -O0 -MMD -MP # For debugging

# 1. Definició de fonts
ALL_SRCS  := $(wildcard src/*.cc)
SRCS_CPP  := $(filter-out src/cube_controller.cc, $(ALL_SRCS))
SRCS_WASM := $(filter-out src/main.cc, $(ALL_SRCS))

# 2. Definició d'objectes (només per a la versió CPP)
# Fem servir SRCS_CPP per generar la llista d'objectes
OBJS := $(SRCS_CPP:src/%.cc=bin/%.o)
DEPS := $(OBJS:.o=.d)

TARGET_CPP := bin/program.exe

.PHONY: cpp wasm clean run

# Target per defecte
cpp: $(TARGET_CPP)
	

# Pas d'enllaç (Linking) per a C++
$(TARGET_CPP): $(OBJS)
	@mkdir -p bin
	$(CXX) $(OBJS) -o $@

# Pas de compilació (Pattern rule)
bin/%.o: src/%.cc
	@mkdir -p bin
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Target per a WebAssembly (Emscripten acostuma a compilar tot de cop)
wasm:
	@mkdir -p bin
	emcc $(SRCS_WASM) \
		-o bin/cube_lib.js \
		-s MODULARIZE=1 \
		-s EXPORT_ES6=1 \
		-s EXPORT_NAME="createModule" \
		-s ALLOW_MEMORY_GROWTH=1 \
		--preload-file data/ \
		--bind
	cp bin/cube_lib.js ../Viewer/libs/cube_lib.js
	cp bin/cube_lib.wasm ../Viewer/libs/cube_lib.wasm
	cp bin/cube_lib.data ../Viewer/cube_lib.data

clean:
	rm -rf bin/*.o bin/*.d $(TARGET_CPP) bin/cube_lib.js bin/cube_lib.wasm

run: cpp
	./$(TARGET_CPP)

-include $(DEPS)