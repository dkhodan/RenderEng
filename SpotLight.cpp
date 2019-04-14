#include "SpotLight.h"



SpotLight::SpotLight() : PointLight()
{
	direction = glm::vec3(0.0f, -1.0f, 0.0f);
	edge = 0.0f;
	procEdge = cosf(glm::radians(edge));
}


SpotLight::~SpotLight()
{
}

SpotLight::SpotLight(GLfloat red, GLfloat green, GLfloat blue,
	GLfloat ambient_intensity, GLfloat diffuse_intensity,
	GLfloat x, GLfloat y, GLfloat z,
	GLfloat x_dir, GLfloat y_dir, GLfloat z_dir,
	GLfloat con, GLfloat linear, GLfloat exp, GLfloat edg) : PointLight(red, green, blue,
																			ambient_intensity, diffuse_intensity,
																			x, y, z,
																			con, linear, exp)
{
	direction = glm::normalize(glm::vec3(x_dir, y_dir, z_dir));
	edge = edg;
	procEdge = cosf(glm::radians(edge));
}

void SpotLight::UseLight(GLfloat ambient_intensity_location, GLfloat ambient_colour_location, GLfloat diffuse_intensity_location, 
							GLfloat light_position_location, GLuint direction_location, GLfloat constant_location, 
							GLfloat linear_location, GLfloat exponent_location, GLuint edge_location)
{
	glUniform3f(ambient_colour_location, colour.x, colour.y, colour.z);
	glUniform1f(ambient_intensity_location, ambient_intensity);
	glUniform1f(diffuse_intensity_location, diffuse_intensity);

	glUniform3f(light_position_location, position.x, position.y, position.z);
	glUniform1f(constant_location, constant);
	glUniform1f(linear_location, linear);
	glUniform1f(exponent_location, exponent);

	glUniform3f(direction_location, direction.x, direction.y, direction.z);
	glUniform1f(edge_location, procEdge);
}

void SpotLight::SetFlash(glm::vec3 pos, glm::vec3 dir)
{
	position = pos;
	direction = dir;
}
