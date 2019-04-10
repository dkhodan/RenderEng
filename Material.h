#pragma once

#include "GL/glew.h"

class Material
{
public:
	Material() = default;
	Material(GLfloat specular_intensity, GLfloat shininess);
	~Material();

	void UseMaterial(GLfloat specular_intensity, GLfloat shininess);

private:
	GLfloat specular_intesity;
	GLfloat shininess;
};

