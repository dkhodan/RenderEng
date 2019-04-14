#include "Mesh.h"
#include <iostream>

GL_Mesh::GL_Mesh()
{
	VAO = 0;
	VBO = 0;
	IBO = 0;
	indexCount = 0;
}

void GL_Mesh::CreateMesh(GLfloat *vertices, unsigned int *indices, unsigned int numOfVertices, unsigned int numOfIndices)
{
	indexCount = numOfIndices;

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * numOfIndices, indices, GL_STATIC_DRAW);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * numOfVertices, vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 6, 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 6, (void*)(sizeof(vertices[0]) * 3));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}

void GL_Mesh::RenderMesh()
{
	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void GL_Mesh::ClearMesh()
{
	if (IBO != 0)
	{
		glDeleteBuffers(1, &IBO);
		IBO = 0;
	}

	if (VBO != 0)
	{
		glDeleteBuffers(1, &VBO);
		VBO = 0;
	}

	if (VAO != 0)
	{
		glDeleteVertexArrays(1, &VAO);
		VAO = 0;
	}

	indexCount = 0;
}

void GL_Mesh::ControlMesh(bool * keys, float DeltaTime)
{
	if (keys[GLFW_KEY_LEFT_SHIFT] == true && keys[GLFW_KEY_X] == true && keys[GLFW_KEY_LEFT] == true)
	{
		if (mesh_scale.x <= 0.1f)
			return;

		mesh_scale -= glm::vec3(0.001f, 0.f, 0.f);
	}

	if (keys[GLFW_KEY_LEFT_SHIFT] == true && keys[GLFW_KEY_X] == true && keys[GLFW_KEY_RIGHT] == true)
	{
		mesh_scale += glm::vec3(0.001f, 0.f, 0.f);
	}

	if (keys[GLFW_KEY_LEFT_SHIFT] == true && keys[GLFW_KEY_C] == true && keys[GLFW_KEY_LEFT] == true)
	{
		if (mesh_scale.y <= 0.1f)
			return;

		mesh_scale -= glm::vec3(0.0f, 0.001f, 0.f);
	}

	if (keys[GLFW_KEY_LEFT_SHIFT] == true && keys[GLFW_KEY_C] == true && keys[GLFW_KEY_RIGHT] == true)
	{
		mesh_scale += glm::vec3(0.0f, 0.001f, 0.f);
	}
 }

glm::mat4 GL_Mesh::GetMeshTransformMatrix()
{
	mesh_model = glm::mat4(1.f);
	mesh_model = glm::translate(mesh_model, glm::vec3(1.0f, 1.0f, 1.0f));
	mesh_model = glm::scale(mesh_model, mesh_scale);
	return this->mesh_model;
}


GL_Mesh::~GL_Mesh()
{
	ClearMesh();
}
