#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

class GL_Mesh
{
public:
	GL_Mesh();

	void CreateMesh(GLfloat *vertices, unsigned int *indices, unsigned int numOfVertices, unsigned int numOfIndices);
	void RenderMesh();
	void ClearMesh();
	void ControlMesh(bool* keys, float DeltaTime);
	glm::mat4 GetMeshTransformMatrix();
	int counter = 0;
	~GL_Mesh();

private:
	GLuint VAO, VBO, IBO;
	GLsizei indexCount;
	glm::mat4 mesh_model = glm::mat4(1.f);
	glm::vec3 mesh_scale = glm::vec3(1.f);
};

