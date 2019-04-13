#include "Light.h"

Light::Light()
{
	colour = glm::vec3(1.0f, 1.0f, 1.0f);
	ambient_intensity = 1.f;
	light_direction = glm::vec3(0.0f, -1.0f, 0.0f);
	diffuse_intensity = 0.0f;
}

Light::Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat ambient, GLfloat diffuse_intensity) 
	:	colour(glm::vec3(red, green, blue)),
		ambient_intensity(ambient),
		diffuse_intensity(diffuse_intensity)
{}

void Light::UpdateLightLocation()
{
	if (direction_switch)
	{

		if (angle >= 360.f) 
		{
			direction_switch = false;
			return;
		}
		angle += 0.1f;
		light_direction +=glm::vec3(glm::cos(glm::radians(angle)), glm::sin(glm::radians(angle)), 0.f);
	}
	else
	{
		if (angle <= 0.1f)
		{
			direction_switch = true;
			return;
		}
		angle -= 0.1f;
		light_direction -= glm::vec3(glm::cos(glm::radians(angle)), glm::sin(glm::radians(angle)), 0.f);
	}
}

Light::~Light()
{
}
