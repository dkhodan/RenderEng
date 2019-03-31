#pragma once

#include "stdio.h"

#include <GL\glew.h>
#include <GLFW\glfw3.h>

class GL_Window
{
public:
	GL_Window();

	GL_Window(GLint windowWidth, GLint windowHeight);

	int Initialise();

	GLint getBufferWidth() { return bufferWidth; }
	GLint getBufferHeight() { return bufferHeight; }

	bool getShouldClose() { return glfwWindowShouldClose(mainWindow); }

	void swapBuffers() { glfwSwapBuffers(mainWindow); }

	~GL_Window();

private:
	GLFWwindow * mainWindow;

	GLint width, height;
	GLint bufferWidth, bufferHeight;
};