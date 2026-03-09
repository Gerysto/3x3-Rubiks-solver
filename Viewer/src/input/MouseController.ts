import {Camera} from '../engine/Camera.js';

export class MouseController {
    
    camera: Camera;
    canvas: HTMLCanvasElement;
    mouse_pressed: boolean;
    mouseX: number = 0;
    mouseY: number = 0;
    
    constructor(camera: Camera, canvas: HTMLCanvasElement) {
        this.camera = camera
        this.canvas = canvas;
        this.mouse_pressed = false;

        canvas.addEventListener("mousedown", () => this.mouse_pressed = true);
        canvas.addEventListener("mouseup"  , () => this.mouse_pressed = false);

        canvas.addEventListener("mousemove", this.MouseMoveHandler);
    }

    MouseMoveHandler(event: MouseEvent) {
        const new_X = event.clientX - this.canvas.offsetLeft;
        const new_Y = event.clientY - this.canvas.offsetTop;

        if (this.mouse_pressed) {
            this.camera.angleY += -(new_X-this.mouseX);
            this.camera.angleX +=  (new_Y-this.mouseY);
        }

        this.mouseX = new_X;
        this.mouseY = new_Y;
    
    }
}