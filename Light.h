#pragma once
#include <glm/glm.hpp>
#include <GL/glew.h>

class Light
{
public:
	Light();
	Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat ambient_intensity, GLfloat diffuse_intensity);
	~Light();
	void UpdateLightLocation();

protected:
	glm::vec3 colour;
	glm::vec3 light_direction;
	GLfloat ambient_intensity;
	GLfloat diffuse_intensity;

private:
	float angle = 0.001;
	bool direction_switch = true;
};

