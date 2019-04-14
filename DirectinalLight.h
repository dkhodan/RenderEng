#pragma once
#include "Light.h"

class DirectinalLight : public Light
{
public:
	DirectinalLight();

	DirectinalLight(GLfloat red, GLfloat green, GLfloat blue, 
					GLfloat ambient_intensity, GLfloat diffuse_intensity,
					GLfloat x, GLfloat y, GLfloat z);
	void UseLight(GLfloat ambient_intensity_location, GLfloat ambient_colour_location, GLfloat diffuse_intensity_location, GLfloat light_direction_location);
	~DirectinalLight();

private:
	glm::vec3 direction;

};

