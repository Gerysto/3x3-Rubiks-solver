# Rubik’s Cube Solver

## Overview

This project is a 3×3 Rubik’s Cube solver with two main parts:

1. **CubeLogic (C++)** – Defines the Rubik's cube's state representation and movement logic and implements a solving algorithm based on Thistlethwaite reductions. Can be run independently.

2. **Viewer (TypeScript + WebGL2)** – 3D visualization of the cube. Currently, the cube can be displayed and rotated using Euler angles.

The goal is to eventually integrate both parts using WebAssembly so the user can interact with the cube's state and solver through the browser. 

## Features

* [x] Fully implemented cube logic and solver (C++)
* [x] 3D cube visualization (WebGL2)
* [x] Rotate the cube using Euler angles in the viewer
* [x] Integrate solver and viewer using WebAssembly
* [ ] Move-based interactions in the viewer
* [x] Animate solving sequences in the 3D view
* [x] Scramble and user-input functionality

## Project Structure

* `CubeLogic/` – Cube state and solving algorithm in C++
* `Viewer/` – 3D cube renderer using TypeScript + WebGL

## Installation & Usage

### Requirements
- C++ compiler
- Node.js and npm for the viewer *(only if you want to recompile)*
- Web browser with WebGL support 

### Using the C++ Solver

As mentioned before, the C++ solver can be used independently of the viewer.

```bash
cd CubeLogic

# Compile (uses g++)
make all

# Run the binary
make run
```
_Tip: Modify `main.cpp` to test custom scrambles and states._

### Using the Viewer

*Note: still in progress*

```bash
cd Viewer

# Install dependencies
npm install

# Compile the TypeScript code
npx tsc

# Run on a static server (for example using python)
python3 -m http.server 8080
```

- Open a browser at `http://localhost:8080`

## License

This project is licensed under the MIT License.
