#pragma once
#include "Light.h"

class PointLight : public Light
{
public:
	PointLight();
	~PointLight();

private:
	glm::vec3 position;
	GLfloat constant;
	GLfloat linear;
	GLfloat exponent;
};
