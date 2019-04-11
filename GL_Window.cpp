#include "GL_Window.h"

GL_Window::GL_Window()
{
	width = 800;
	height = 600;
	x_change = 0.f;
	y_change = 0.f;
	mouse_first_moved = true;
}

GL_Window::GL_Window(GLint windowWidth, GLint windowHeight)
{
	width = windowWidth;
	height = windowHeight;

	for (auto key : keys)
	{
		key = 0;
	}
}

int GL_Window::Initialise()
{
	if (!glfwInit())
	{
		printf("Error Initialising GLFW");
		glfwTerminate();
		return 1;
	}

	// Setup GLFW Windows Properties
	// OpenGL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Core Profile
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// Allow forward compatiblity
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	// Create the window
	mainWindow = glfwCreateWindow(width, height, "Test GL_Window", NULL, NULL);
	if (!mainWindow)
	{
		printf("Error creating GLFW window!");
		glfwTerminate();
		return 1;
	}

	// Get buffer size information
	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	// Set the current context
	glfwMakeContextCurrent(mainWindow);

	CreateCallbacks();
	glfwSetInputMode(mainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Allow modern extension access
	glewExperimental = GL_TRUE;

	GLenum error = glewInit();
	if (error != GLEW_OK)
	{
		printf("Error: %s", glewGetErrorString(error));
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}

	glEnable(GL_DEPTH_TEST);

	// Create Viewport
	glViewport(0, 0, bufferWidth, bufferHeight);

	glfwSetWindowUserPointer(mainWindow, this);
}

void GL_Window::handleKeys(GLFWwindow* window, int key, int code, int action, int mode)
{
	GL_Window* gl_window = static_cast<GL_Window*>(glfwGetWindowUserPointer(window));

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			gl_window->keys[key] = true;
			std::cout << "Pressed: " << key << std::endl;
		}
		else if (action == GLFW_RELEASE)
		{
			gl_window->keys[key] = false;
			std::cout << "Released: " << key << std::endl;
		}
	}
}

void GL_Window::handleMouse(GLFWwindow* window, double xPos, double yPos)
{
	GL_Window* gl_window = static_cast<GL_Window*>(glfwGetWindowUserPointer(window));

	if (gl_window->mouse_first_moved)
	{
		gl_window->last_x = xPos;
		gl_window->last_y = yPos;
		gl_window->mouse_first_moved = false;
	}

	gl_window->x_change = xPos - gl_window->last_x;
	gl_window->y_change = gl_window->last_y - yPos;

	gl_window->last_x = xPos;
	gl_window->last_y = yPos;

	std::cout << "x: " << gl_window->x_change << ", y: " << gl_window->y_change << std::endl;
}

void GL_Window::CreateCallbacks()
{
	glfwSetKeyCallback(mainWindow, handleKeys);
	glfwSetCursorPosCallback(mainWindow, handleMouse);
}

GL_Window::~GL_Window()
{
	glfwDestroyWindow(mainWindow);
	glfwTerminate();
}


GLfloat GL_Window::GetXChange()
{
	GLfloat change = x_change;
	x_change = 0;
	return change;
}

GLfloat GL_Window::GetYChange()
{
	GLfloat change = y_change;
	y_change = 0;
	return change;
}