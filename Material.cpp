#include "Material.h"

Material::Material(GLfloat specular_intensity, GLfloat shininess) : specular_intesity(specular_intensity), shininess(shininess) {}


Material::~Material()
{
}

void Material::UseMaterial(GLfloat specularIntensity, GLfloat shine)
{
	glUniform1f(specularIntensity, specular_intesity);
	glUniform1f(shine, shininess);
}
