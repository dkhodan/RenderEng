#pragma once

#include <GL\glew.h>

class GL_Mesh
{
public:
	GL_Mesh();

	void CreateMesh(GLfloat *vertices, unsigned int *indices, unsigned int numOfVertices, unsigned int numOfIndices);
	void RenderMesh();
	void ClearMesh();

	~GL_Mesh();

private:
	GLuint VAO, VBO, IBO;
	GLsizei indexCount;
};

