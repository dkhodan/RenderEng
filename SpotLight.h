#pragma once
#include "PointLight.h"

class SpotLight : PointLight
{
public:
	SpotLight();
	~SpotLight();

	SpotLight(GLfloat red, GLfloat green, GLfloat blue,
		GLfloat ambient_intensity, GLfloat diffuse_intensity,
		GLfloat x, GLfloat y, GLfloat z,
		GLfloat x_dir, GLfloat y_dir, GLfloat z_dir,
		GLfloat con, GLfloat linear, GLfloat exp,
		GLfloat edg);

	void UseLight(GLfloat ambient_intensity_location, GLfloat ambient_colour_location,
		GLfloat diffuse_intensity_location, GLfloat light_position_location, GLuint direction_location,
		GLfloat constant_location, GLfloat linear_location, GLfloat exponent_location,
		GLuint edge_location);

	void SetFlash(glm::vec3 pos, glm::vec3 dir);

private:
	glm::vec3 direction;
	GLfloat edge;
	GLfloat procEdge;
};

