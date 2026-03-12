import {Camera} from '../engine/Camera.js';

export class MouseController {
    
    camera: Camera;
    canvas: HTMLCanvasElement;
    mouse_pressed: boolean;
    mouseX: number = 0;
    mouseY: number = 0;
    
    constructor(camera: Camera, canvas: HTMLCanvasElement) {
        this.camera = camera;
        this.canvas = canvas;

        this.mouse_pressed = false;

        this.canvas.addEventListener("mousedown", () => this.mouse_pressed = true);
        this.canvas.addEventListener("mouseup"  , () => this.mouse_pressed = false);

        this.canvas.addEventListener("mousemove", (e) => {
            const new_X = e.clientX - this.canvas.offsetLeft;
            const new_Y = e.clientY - this.canvas.offsetTop;

            if( e.shiftKey && this.mouse_pressed) {
                camera.fov += 5*(new_X - this.mouseX)/this.canvas.width;

                this.mouseX = new_X;
                this.mouseY = new_Y;
                return;
            }

            if (this.mouse_pressed) {
                this.camera.angleY += -(new_X-this.mouseX);
                this.camera.angleX +=  (new_Y-this.mouseY);
            }

            this.mouseX = new_X;
            this.mouseY = new_Y;
        });
    }
}