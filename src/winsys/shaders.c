
// Copyright 2016, Edward O'Callaghan <funfunctor@folklore1984.net>

#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "shaders.h"

// XXX how unfortant for now
GLuint shaderProgram;

GLuint getShaderProgram(void)
{
	return shaderProgram;
}

/**
 * Compile & Link our shader program
 */
void build_glsl(const GLchar** vertex_path, const GLchar** frag_path)
{
	/* Vertex shader */
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, vertex_path, NULL);
	glCompileShader(vertexShader);

	/* Check for compile time errors */
	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		fprintf(stderr, "ERROR::SHADER::VERTEX::COMPILATION_FAILED %s\n", infoLog);
	}

	/* Fragment shader */
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, frag_path, NULL);
	glCompileShader(fragmentShader);

	/* Check for compile time errors */
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		fprintf(stderr, "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED %s\n", infoLog);
	}


	/* Link shaders */
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	/* Check for linking errors */
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		fprintf(stderr, "ERROR::SHADER::PROGRAM::LINKING_FAILED %s\n", infoLog);
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}
