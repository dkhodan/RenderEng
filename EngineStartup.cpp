#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include "Window.h"
#include "Mesh.h"
#include "Shader.h"
#include "Camera.h"
#include "DirectinalLight.h"
#include "Material.h"
#include "SpotLight.h"

#include "CommonValues.h"
#include "PointLight.h"

#define AMBIENT_INTENSITY
#define DIFFUSE_INTENSITY
#define RGB
#define DIRECTION

const float toRadians = 3.14159265f / 180.0f;

GL_Window mainWindow;
std::vector<GL_Mesh*> meshList;
std::vector<Shader> shaderList;
Camera camera;
DirectinalLight main_light;
PointLight point_lights[MAX_POINT_LIGHTS];
SpotLight spot_lights[MAX_SPOT_LIGHTS];

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
	unsigned int indices[] =
	{
		//front 
		0, 3, 4, 
		4, 5, 0,

		//back
		1, 2, 7,
		7, 6, 1,

		//top 
		1, 0, 3,
		1, 2, 3,

		//bottom
		4, 5, 6, 
		6, 7, 4,

		//left
		1, 0, 5,
		1, 6, 5,

		//right
		2, 3, 4,
		2, 7, 4
	};

	GLfloat vertices[] = {
		-1.0, 1.0f, -1.0f,		0.0f, 0.0f, 0.0f,  // top right back		0
		-1.0f, 1.0f, 1.0f,		0.0f, 0.0f, 0.0f,  // top right front		1
		1.0f, 1.0f, 1.0f,		0.0f, 0.0f, 0.0f,  // bottom right back		2
		1.0f, 1.0f, -1.0f,		0.0f, 0.0f, 0.0f,  // bottom right front	3
		1.0f, -1.0f, -1.0f,		0.0f, 0.0f, 0.0f,  // bottom left back		4
		-1.0f, -1.0f, -1.0f,	0.0f, 0.0f, 0.0f,  // bottom left front		5
		-1.0f, -1.0f, 1.0f,		0.0f, 0.0f, 0.0f,  // top left back			6
		1.0f, -1.0f, 1.0f,		0.0f, 0.0f, 0.0f,  // top left front		7
	};

	unsigned int floorIndices[] = {
		0, 2, 1,
		1, 2, 3
	};

	GLfloat floorVertices[] = {
		-10.0f, 0.0f, -10.0f,	0.0f, 0.0f, 0.0f,
		10.0f, 0.0f, -10.0f,	0.0f, 0.0f, 0.0f,
		-10.0f, 0.0f, 10.0f,	0.0f, 0.0f, 0.0f,
		10.0f, 0.0f, 10.0f,		0.0f, 0.0f, 0.0f
	};

	calc_average_normals(indices, 36, vertices, 24, 6, 3);
	calc_average_normals(floorIndices, 6, floorVertices, 24, 6, 3);

	GL_Mesh *obj1 = new GL_Mesh();
	obj1->CreateMesh(vertices, indices, 48, 36);
	meshList.push_back(obj1);

	GL_Mesh *obj3 = new GL_Mesh();
	obj3->CreateMesh(floorVertices, floorIndices, 24, 6);
	meshList.push_back(obj3);
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
	camera = Camera(glm::vec3(0.0f, 3.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f, 0.0f, 2.0f, 0.5f);

	shiny_material = Material(0.3f, 32);

	main_light = DirectinalLight(RGB 1.0f, 1.0f, 1.0f,
								AMBIENT_INTENSITY 0.1f, DIFFUSE_INTENSITY 0.2f,
								DIRECTION 0.f, 0.f, -1.f);
	
	unsigned int point_light_count = 0;
	
	point_lights[0] = PointLight(0.0f, 1.0f, 1.0f,
									0.0f, 1.0f,
									-8.0f, -4.0f, -8.0f,
									0.3f, 0.2f, 0.1f);
	point_light_count++;

	point_lights[1] = PointLight(1.0f, 0.0f, 1.0f,
									0.0f, 1.0f,
									8.0f, -4.0f, 8.0f,
									0.9f, 0.9f, 0.9f);
	point_light_count++;

	unsigned int spot_light_count = 0;
	spot_lights[0] = SpotLight(1.0f, 1.0f, 1.0f,
								0.0f, 1.0f, 
								6.0f, 1.5f, 0.0f,
								-100.0f, -4.0f, 0.0f,
								1.0f, 0.0f, 0.0f,
								20.0f);
	spot_light_count++;

	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0,
		uniformSpecularIntensity = 0, uniformShininess = 0, uniformEyePosition = 0;

	glm::mat4 projection = glm::perspective(glm::radians(70.0f), (GLfloat)mainWindow.getBufferWidth() / (GLfloat)mainWindow.getBufferHeight(), 0.01f, 1000.0f);
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
		uniformEyePosition = shaderList[0].GetEyePosition();
		uniformSpecularIntensity = shaderList[0].GetSpecularIntensity();
		uniformShininess = shaderList[0].GetShininess();


		spot_lights[0].SetFlash(camera.GetCameraPosition(), camera.GetCameraDirection());

		shaderList[0].SetDirectionalLight(&main_light);
		shaderList[0].SetPointLights(point_lights, point_light_count);
		shaderList[0].SetSpotLights(spot_lights, spot_light_count);
		//main_light.UpdateLightLocation();

		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculate_view_matrix()));
		glUniform3f(uniformEyePosition, camera.GetCameraPosition().x, camera.GetCameraPosition().y, camera.GetCameraPosition().z);
		meshList[0]->ControlMesh(mainWindow.getHandleKeys(), DeltaTime);

		glm::mat4 model = meshList[0]->GetMeshTransformMatrix();
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		shiny_material.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[0]->RenderMesh();


		model = glm::mat4(1.f);
		model = glm::translate(model, glm::vec3(0.0f, -2.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		shiny_material.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[1]->RenderMesh();

		glUseProgram(0);
		mainWindow.swapBuffers();
	}
	return 0;
}