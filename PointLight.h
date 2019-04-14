#pragma once
#include "Light.h"

class PointLight : public Light
{
public:
	PointLight();
	PointLight(GLfloat red, GLfloat green, GLfloat blue, 
				GLfloat ambient_intensity, GLfloat diffuse_intensity,
				GLfloat x, GLfloat y, GLfloat z,
				GLfloat con, GLfloat linear, GLfloat exp);
	~PointLight();

	void UseLight(GLfloat ambient_intensity_location, GLfloat ambient_colour_location, 
					GLfloat diffuse_intensity_location, GLfloat light_position_location,
					GLfloat constant_location, GLfloat linear_location, GLfloat exponent_location);

protected:
	glm::vec3 position;
	GLfloat constant;
	GLfloat linear;
	GLfloat exponent;
};

