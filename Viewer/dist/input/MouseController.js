export class MouseController {
    constructor(camera, canvas) {
        this.mouseX = 0;
        this.mouseY = 0;
        this.camera = camera;
        this.canvas = canvas;
        this.mouse_pressed = false;
        this.canvas.addEventListener("pointerdown", () => this.mouse_pressed = true);
        this.canvas.addEventListener("pointerup", () => this.mouse_pressed = false);
        this.canvas.addEventListener("pointermove", (e) => {
            const new_X = e.clientX - this.canvas.offsetLeft;
            const new_Y = e.clientY - this.canvas.offsetTop;
            if (this.mouse_pressed) {
                this.camera.angleY += -(new_X - this.mouseX);
                this.camera.angleX += (new_Y - this.mouseY);
            }
            this.mouseX = new_X;
            this.mouseY = new_Y;
        });
        this.canvas.addEventListener("wheel", (e) => {
            e.preventDefault();
            if (e.deltaY < 0 && this.camera.fov > 20) {
                //console.log("Zoom in: ", e.deltaY);
                this.camera.fov /= 1.2;
            }
            else if (e.deltaY > 0 && this.camera.fov < 130) {
                //console.log("Zoom out!", e.deltaY);
                this.camera.fov *= 1.2;
            }
        });
    }
}
