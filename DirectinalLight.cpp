#include "DirectinalLight.h"


DirectinalLight::DirectinalLight() : Light()
{
	light_direction = glm::vec3(0.0f, -1.0f, 0.0f);
}

DirectinalLight::DirectinalLight(GLfloat red, GLfloat green, GLfloat blue, 
								 GLfloat ambient_intensity, GLfloat diffuse_intensity,
								 GLfloat x, GLfloat y, GLfloat z) : Light(red, green, blue, ambient_intensity, diffuse_intensity)
{
	light_direction = glm::vec3(x, y, z);
}

void DirectinalLight::UseLight(GLfloat ambient_intensity_location, GLfloat ambient_colour_location, GLfloat diffuse_intensity_location, GLfloat light_direction_location)
{
	glUniform3f(ambient_colour_location, colour.x, colour.y, colour.z);
	glUniform1f(ambient_intensity_location, ambient_intensity);
	glUniform3f(light_direction_location, light_direction.x, light_direction.y, light_direction.z);
	glUniform1f(diffuse_intensity_location, diffuse_intensity);
}


DirectinalLight::~DirectinalLight()
{
}
