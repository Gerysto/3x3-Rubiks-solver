# WebGL2 template

A simple WebGL2 template for rendering `.obj` files with basic mouse-controlled rotation.

## Features

- Load and display `.obj` 3D models
- Rotate the model with mouse movement
- Basic lighting using the Phong reflection model

## Installation

1. Clone this repository:
```bash
git clone https://github.com/Gerysto/WebGL2-template.git
```

2. Open `index.html` in a browser with WebGL2 support.
  *(you may need to run it on a local server)*

## Usage

- Drag the mouse to rotate the loaded model
- Replace the sample model `Patrick.obj` with one of your choosing
    - Remember to also change the model's url in `index.html`:
    ``` js
    const model_url = "Patrick.obj";
    ```
## License

This project is licensed under the [MIT License](LICENSE).