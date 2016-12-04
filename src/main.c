#include "winsys/winsys.h"
#include "winsys/shaders.h"

// Shaders
const GLchar* vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 position;\n"
    "layout (location = 1) in vec3 color;\n"
    "out vec3 ourColor;\n"
    "void main()\n"
    "{\n"
    "gl_Position = vec4(position, 1.0);\n"
    "ourColor = color;\n"
    "}\0";

const GLchar* fragmentShaderSource = "#version 330 core\n"
    "out vec4 color;\n"
    "uniform vec4 ourColor;\n"
    "void main()\n"
    "{\n"
    "color = ourColor;\n"
    "}\n\0";

int main()
{
	init();
	idk();
	build_glsl(&vertexShaderSource, &fragmentShaderSource);
	draw_loop();
	finit();

	return 0;
}
