#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include "GL_Window.h"
#include "GL_Mesh.h"
#include "Shader.h"
#include "Camera.h"
#include "Light.h"
#include "Material.h"

const float toRadians = 3.14159265f / 180.0f;

GL_Window mainWindow;
std::vector<GL_Mesh*> meshList;
std::vector<Shader> shaderList;
Camera camera;
Light mainLight;
Material shiny_material;
Material dull_material;

GLfloat DeltaTime = 0.0f;
GLfloat LastTime = 0.0f;

// Vertex Shader
static const char* vShader = "Shaders/shader.vert";

// Fragment Shader
static const char* fShader = "Shaders/shader.frag";

void calc_average_normals(unsigned int * indices, unsigned int indiceCount, GLfloat * vertices, unsigned int verticeCount,
	unsigned int vLength, unsigned int normalOffset)
{
	for (size_t i = 0; i < indiceCount; i += 3)
	{
		unsigned int in0 = indices[i] * vLength;
		unsigned int in1 = indices[i + 1] * vLength;
		unsigned int in2 = indices[i + 2] * vLength;
		glm::vec3 v1(vertices[in1] - vertices[in0], vertices[in1 + 1] - vertices[in0 + 1], vertices[in1 + 2] - vertices[in0 + 2]);
		glm::vec3 v2(vertices[in2] - vertices[in0], vertices[in2 + 1] - vertices[in0 + 1], vertices[in2 + 2] - vertices[in0 + 2]);
		glm::vec3 normal = glm::cross(v1, v2);
		normal = glm::normalize(normal);

		in0 += normalOffset; in1 += normalOffset; in2 += normalOffset;
		vertices[in0] += normal.x; vertices[in0 + 1] += normal.y; vertices[in0 + 2] += normal.z;
		vertices[in1] += normal.x; vertices[in1 + 1] += normal.y; vertices[in1 + 2] += normal.z;
		vertices[in2] += normal.x; vertices[in2 + 1] += normal.y; vertices[in2 + 2] += normal.z;
	}

	for (size_t i = 0; i < verticeCount / vLength; i++)
	{
		unsigned int nOffset = i * vLength + normalOffset;
		glm::vec3 vec(vertices[nOffset], vertices[nOffset + 1], vertices[nOffset + 2]);
		vec = glm::normalize(vec);
		vertices[nOffset] = vec.x; vertices[nOffset + 1] = vec.y; vertices[nOffset + 2] = vec.z;
	}
}

void CreateObjects()
{
	unsigned int indices[] = {
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2
	};

	GLfloat vertices[] = {
		//	x      y      z		nx	  ny    nz
		-1.0f, -1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.0f, -1.0f, 1.0f,		0.0f, 0.0f, 0.0f,
		1.0f, -1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,		0.0f, 0.0f, 0.0f
	};

	calc_average_normals(indices, 12, vertices, 24, 8, 5);

	GL_Mesh *obj1 = new GL_Mesh();
	obj1->CreateMesh(vertices, indices, 24, 12);
	meshList.push_back(obj1);

	GL_Mesh *obj2 = new GL_Mesh();
	obj2->CreateMesh(vertices, indices, 24, 12);
	meshList.push_back(obj2);
}

void CreateShaders()
{
	Shader *shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);
}

int main()
{

	mainWindow = GL_Window(1366, 768);
	mainWindow.Initialise();

	CreateObjects();
	CreateShaders();
	camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 2.0f, 0.5f);

	shiny_material = Material(1.0f, 32);
	dull_material = Material(0.3f, 4);

	mainLight = Light(0.0f, 1.0f, 1.0f, 0.1f,
						-3.0f, 3.5f, 0.0f, 0.7f);


	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformAmbientIntensity = 0, uniformAmbientColour = 0, uniformLightDirection = 0, uniformDiffuseIntensity = 0,
		uniformSpecularIntensity = 0, uniformShininess = 0, uniformEyePosition = 0;
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 100.0f);

	// Loop until window closed
	while (!mainWindow.getShouldClose())
	{
		GLfloat now = glfwGetTime();
		DeltaTime = now - LastTime;
		LastTime = now;
		// Get + Handle User Input
		glfwPollEvents();

		camera.keys_control(mainWindow.getHandleKeys(), DeltaTime);
		camera.mouse_control(mainWindow.GetXChange(), mainWindow.GetYChange());

		// Clear the window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shaderList[0].UseShader();
		uniformModel = shaderList[0].GetModelLocation();
		uniformProjection = shaderList[0].GetProjectionLocation();
		uniformView = shaderList[0].GetViewLocation();
		uniformAmbientIntensity = shaderList[0].GetAmbientIntensityLocation();
		uniformAmbientColour = shaderList[0].GetAmbientColour();
		uniformLightDirection = shaderList[0].GetLightDirection();
		uniformDiffuseIntensity = shaderList[0].GetDiffuseIntensity();
		uniformEyePosition = shaderList[0].GetEyePosition();
		uniformSpecularIntensity = shaderList[0].GetSpecularIntensity();
		uniformShininess = shaderList[0].GetShininess();

		mainLight.UseLight(uniformAmbientIntensity, uniformAmbientColour, uniformDiffuseIntensity, uniformLightDirection);
		//mainLight.UpdateLightLocation(glm::vec3(0.001f, 0.001f, 0.0f));

		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculate_view_matrix()));
		glUniform3f(uniformEyePosition, camera.GetCameraPosition().x, camera.GetCameraPosition().y, camera.GetCameraPosition().z);
		

		glm::mat4 model = glm::mat4(1.f);

		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		shiny_material.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[0]->RenderMesh();

		model = glm::mat4(1.f);
		model = glm::translate(model, glm::vec3(0.0f, 4.0f, -2.5f));
		//model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		shiny_material.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[1]->RenderMesh();

		glUseProgram(0);

		mainWindow.swapBuffers();
	}

	return 0;
}