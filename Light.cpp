#include "Light.h"



Light::Light()
{
	colour = glm::vec3(1.0f, 1.0f, 1.0f);
	ambientIntensity = 1.f;

	light_direction = glm::vec3(0.0f, -1.0f, 0.0f);
	diffuse_intensity = 0.0f;
}

void Light::UpdateLightLocation(glm::vec3 dir)
{
	if (light_direction.x < 4.0f)
	{
		light_direction.x += dir.x;
	}
	else
	{
		light_direction.x = 0;
	}


	if (light_direction.y > -4.0f)
	{
		light_direction.y -= dir.y;
	}
	else
	{
		light_direction.y = 3.0f;
	}
}

Light::Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat ambient, GLfloat light_xDir, GLfloat light_yDir, GLfloat light_zDir, GLfloat diffuse_intensity)
{
	colour = glm::vec3(red, green, blue);
	ambientIntensity = ambient;
	light_direction.x = light_xDir;
	light_direction.y = light_yDir;
	light_direction.z = light_zDir;

	this->diffuse_intensity = diffuse_intensity;
}

void Light::UseLight(GLfloat ambientIntensityLocation, GLfloat ambientColourLocation, GLfloat diffuseIntensityLocation, GLfloat lightDirectionLocation)
{
	glUniform3f(ambientColourLocation, colour.x, colour.y, colour.z);
	glUniform1f(ambientIntensityLocation, ambientIntensity);
	glUniform3f(lightDirectionLocation, light_direction.x, light_direction.y, light_direction.z);
	glUniform1f(diffuseIntensityLocation, diffuse_intensity);
}

Light::~Light()
{
}
