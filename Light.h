#pragma once
#include <glm/glm.hpp>
#include <GL/glew.h>


class Light
{
public:
	Light();
	Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat ambient, GLfloat light_xDir, GLfloat light_yDir, GLfloat light_zDir, GLfloat diffuse_intensity);
	void UseLight(GLfloat ambientIntensityLocation, GLfloat ambientColourLocation, GLfloat diffuseIntensityLocation, GLfloat lightDirectionLocation);
	~Light();
	void UpdateLightLocation(glm::vec3 dir);

private:
	glm::vec3 colour;
	GLfloat ambientIntensity;

	glm::vec3 light_direction;
	GLfloat diffuse_intensity;
};

