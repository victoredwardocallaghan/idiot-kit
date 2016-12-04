
// Copyright 2016, Edward O'Callaghan <funfunctor@folklore1984.net>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "winsys.h"
#include "shaders.h"

GLuint VBO, VAO;
GLFWwindow * window;

void idk(void)
{
	/* Set up vertex data (and buffer(s)) and attribute pointers */
	GLfloat vertices[] = {
		// Positions        
		 0.5f, -0.5f, 0.0f,  // Bottom Right
		-0.5f, -0.5f, 0.0f,  // Bottom Left
		 0.0f,  0.5f, 0.0f   // Top 
	};
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	/* Bind the Vertex Array Object first;
	 * then bind and set vertex buffer(s) and attribute pointer(s).
	 */
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	/* Position attribute */
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0); /* Unbind VAO */
}



// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	glfwSetWindowShouldClose(window, GL_TRUE);
}

void init()
{
	int width = 640; int height = 480; // XXX just hack in for now

	if (glfwInit() != GL_TRUE) {
		fprintf(stderr, "Failed to initialize GLFW");
		exit(1);
	}

	// Set all the required options for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	window = glfwCreateWindow(width, height, "OpenGL", NULL, NULL /*monitor, window*/);
	glfwMakeContextCurrent(window);

	if (!window) {
		glfwTerminate();
		exit(1);
	}

	/* hook some callbacks */
	glfwSetKeyCallback(window, key_callback);
//	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Set to true so GLEW knows to use a modern approach while wrangling func ptrs and exts
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	glewInit();

	// Define the viewport dimensions
	glViewport(0, 0, width, height);
	// Setup OpenGL options
	//glEnable(GL_CULL_FACE);
	// Blending is needed for Glyph rendering!!!
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void finit()
{
	/* Properly de-allocate all resources once they've outlived their purpose */
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	glfwDestroyWindow(window);
	glfwTerminate();
}


void draw_loop(void)
{
	GLuint shaderProgram = getShaderProgram();

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Be sure to activate the shader
		glUseProgram(shaderProgram);

		// Update the uniform color
		GLfloat timeValue = glfwGetTime();
		GLfloat greenValue = (sin(timeValue) / 2) + 0.5;
		GLint vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
		glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

		// Draw the triangle
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);

		glfwSwapBuffers(window);
    }
}
