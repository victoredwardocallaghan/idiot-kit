#ifndef SHADERS_H
#define SHADERS_H

#include <GLFW/glfw3.h>

GLuint getShaderProgram(void);

void build_glsl(const GLchar** vertex_path, const GLchar** frag_path);

#endif
