#include "PointLight.h"

PointLight::PointLight() : Light()
{
	position = glm::vec3(0.f, 0.f, 0.f);
	constant = 1.0f;
	linear = 0.0f;
	exponent = 0.0f;
}

PointLight::PointLight(GLfloat red, GLfloat green, GLfloat blue, 
						GLfloat ambient_intensity, GLfloat diffuse_intensity, 
						GLfloat x, GLfloat y, GLfloat z, 
						GLfloat con, GLfloat linear, GLfloat exp) : Light(red, green, blue, ambient_intensity, diffuse_intensity)
{
	position = glm::vec3(x, y, z);
	this->constant = con;
	this->linear = linear;
	this->exponent = exp;
}

PointLight::~PointLight()
{
}

void PointLight::UseLight(GLfloat ambient_intensity_location, GLfloat ambient_colour_location, 
							GLfloat diffuse_intensity_location, GLfloat light_position_location,
							GLfloat constant_location, GLfloat linear_location, GLfloat exponent_location)
{
	glUniform3f(ambient_colour_location, colour.x, colour.y, colour.z);
	glUniform1f(ambient_intensity_location, ambient_intensity);
	glUniform1f(diffuse_intensity_location, diffuse_intensity);

	glUniform3f(light_position_location, position.x, position.y, position.z);
	glUniform1f(constant_location, constant);
	glUniform1f(linear_location, linear);
	glUniform1f(exponent_location, exponent);
}
