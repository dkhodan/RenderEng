#pragma once

#include "stdio.h"

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <algorithm>
#include <iostream>

class GL_Window
{
public:
	GL_Window();

	GL_Window(GLint windowWidth, GLint windowHeight);

	int Initialise();

	GLint getBufferWidth() { return bufferWidth; }
	GLint getBufferHeight() { return bufferHeight; }

	bool getShouldClose() { return glfwWindowShouldClose(mainWindow); }
	bool* getHandleKeys() { return keys; }
	GLfloat GetXChange();
	GLfloat GetYChange();

	void swapBuffers() { glfwSwapBuffers(mainWindow); }

	~GL_Window();

private:
	GLFWwindow * mainWindow;

	GLint width, height;
	GLint bufferWidth, bufferHeight;
	bool keys[256];
	GLfloat last_x;
	GLfloat last_y;
	GLfloat x_change;
	GLfloat y_change;
	bool mouse_first_moved;


private:
	void CreateCallbacks();
	static void handleKeys(GLFWwindow* window, int key, int code, int action, int mode);
	static void handleMouse(GLFWwindow* window, double xPox, double yPos);
};