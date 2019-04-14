#pragma once
#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <GL\glew.h>
#include "DirectinalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "CommonValues.h"

class Shader
{
public:
	Shader();
	void CreateFromString(const char* vertexCode, const char* fragmentCode);
	void CreateFromFiles(const char* vertexLocation, const char* fragmentLocation);
	std::string ReadFile(const char* fileLocation);
	GLuint GetProjectionLocation();
	GLuint GetModelLocation();
	GLuint GetViewLocation();
	GLuint GetAmbientIntensityLocation();
	GLuint GetAmbientColour();
	GLuint GetDiffuseIntensity();
	GLuint GetLightDirection();
	GLuint GetSpecularIntensity();
	GLuint GetShininess();
	GLuint GetEyePosition();
	void UseShader();
	void ClearShader();
	void SetDirectionalLight(DirectinalLight* d_light);
	void SetPointLights(PointLight* p_light, unsigned int light_count);
	void SetSpotLights(SpotLight* s_light, unsigned int light_count);
	~Shader();

private:
	int point_light_count;
	int spot_light_count;
	GLuint shaderID, uniformProjection, uniformModel, uniformView,
		uniformSpecularIntensity, uniformShininnes, uniformEyePosition;
	GLuint uniform_point_light_count;
	GLuint uniform_spot_light_count;

	struct
	{
		GLuint uniform_colour;
		GLuint uniform_ambient_intensity;
		GLuint uniform_diffuse_intensity;

		GLuint uniform_light_position;
		GLuint uniform_constant;
		GLuint uniform_linear;
		GLuint uniform_exponent;

		GLuint uniform_direction;
		GLuint uniform_edge;
	} uniform_spot_light[MAX_SPOT_LIGHTS];

	struct
	{
		GLuint uniform_colour;
		GLuint uniform_ambient_intensity;
		GLuint uniform_diffuse_intensity;

		GLuint uniform_light_direction;

	} uniform_direction_light;

	struct
	{
		GLuint uniform_colour;
		GLuint uniform_ambient_intensity;
		GLuint uniform_diffuse_intensity;

		GLuint uniform_light_position;
		GLuint uniform_constant;
		GLuint uniform_linear;
		GLuint uniform_exponent;
	} uniform_point_light[MAX_POINT_LIGHTS];

	void CompileShader(const char* vertexCode, const char* fragmentCode);
	void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);
};

