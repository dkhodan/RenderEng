#pragma once
#include "Light.h"

class DirectinalLight : public Light
{
public:
	DirectinalLight();

	DirectinalLight(GLfloat red, GLfloat green, GLfloat blue, 
					GLfloat ambient, GLfloat diffuse_intensity, 
					GLfloat light_xDir, GLfloat light_yDir, GLfloat light_zDir);
	void UseLight(GLfloat ambientIntensityLocation, GLfloat ambientColourLocation, GLfloat diffuseIntensityLocation, GLfloat lightDirectionLocation);
	~DirectinalLight();

private:
	glm::vec3 direction;

};

