#include "Shader.h"

Shader::Shader()
{
	shaderID = 0;
	uniformModel = 0;
	uniformProjection = 0;
	point_light_count = 0;
}

void Shader::CreateFromString(const char* vertexCode, const char* fragmentCode)
{
	CompileShader(vertexCode, fragmentCode);
}

void Shader::CreateFromFiles(const char* vertexLocation, const char* fragmentLocation)
{
	std::string vertexString = ReadFile(vertexLocation);
	std::string fragmentString = ReadFile(fragmentLocation);
	const char* vertexCode = vertexString.c_str();
	const char* fragmentCode = fragmentString.c_str();

	CompileShader(vertexCode, fragmentCode);
}

std::string Shader::ReadFile(const char* fileLocation)
{
	std::string content;
	std::ifstream fileStream(fileLocation, std::ios::in);

	if (!fileStream.is_open()) {
		printf("Failed to read %s! File doesn't exist.", fileLocation);
		return "";
	}

	std::string line = "";
	while (!fileStream.eof())
	{
		std::getline(fileStream, line);
		content.append(line + "\n");
	}

	fileStream.close();
	return content;
}

void Shader::CompileShader(const char* vertexCode, const char* fragmentCode)
{
	shaderID = glCreateProgram();

	if (!shaderID)
	{
		printf("Error creating shader program!\n");
		return;
	}

	AddShader(shaderID, vertexCode, GL_VERTEX_SHADER);
	AddShader(shaderID, fragmentCode, GL_FRAGMENT_SHADER);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glLinkProgram(shaderID);
	glGetProgramiv(shaderID, GL_LINK_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shaderID, sizeof(eLog), NULL, eLog);
		printf("Error linking program: '%s'\n", eLog);
		return;
	}

	glValidateProgram(shaderID);
	glGetProgramiv(shaderID, GL_VALIDATE_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shaderID, sizeof(eLog), NULL, eLog);
		printf("Error validating program: '%s'\n", eLog);
		return;
	}

	uniformProjection = glGetUniformLocation(shaderID, "projection");
	uniformModel = glGetUniformLocation(shaderID, "model");
	uniformView = glGetUniformLocation(shaderID, "view");
	uniform_direction_light.uniform_colour = glGetUniformLocation(shaderID, "directional_light.base.colour");
	uniform_direction_light.uniform_ambient_intensity = glGetUniformLocation(shaderID, "directional_light.base.ambient_intensity");
	uniform_direction_light.uniform_light_direction = glGetUniformLocation(shaderID, "directional_light.light_direction");
	uniform_direction_light.uniform_diffuse_intensity = glGetUniformLocation(shaderID, "directional_light.base.diffuse_intensity");
	uniformSpecularIntensity = glGetUniformLocation(shaderID, "material.specular_intensity");
	uniformShininnes = glGetUniformLocation(shaderID, "material.shininess");
	uniformEyePosition = glGetUniformLocation(shaderID, "eye_position");
	uniform_point_light_count = glGetUniformLocation(shaderID, "point_light_count");

	for (size_t i = 0; i < MAX_POINT_LIGHTS; i++)
	{
		char locBuff[100] = { '\0' };
		snprintf(locBuff, sizeof(locBuff), "point_lights[%d].base.colour", i);
		uniform_point_light[i].uniform_colour = glGetUniformLocation(shaderID, locBuff);

		snprintf(locBuff, sizeof(locBuff), "point_lights[%d].base.ambient_intensity", i);
		uniform_point_light[i].uniform_ambient_intensity = glGetUniformLocation(shaderID, locBuff);

		snprintf(locBuff, sizeof(locBuff), "point_lights[%d].base.diffuse_intensity", i);
		uniform_point_light[i].uniform_diffuse_intensity = glGetUniformLocation(shaderID, locBuff);

		snprintf(locBuff, sizeof(locBuff), "point_lights[%d].position", i);
		uniform_point_light[i].uniform_light_position = glGetUniformLocation(shaderID, locBuff);

		snprintf(locBuff, sizeof(locBuff), "point_lights[%d].constant", i);
		uniform_point_light[i].uniform_constant = glGetUniformLocation(shaderID, locBuff);

		snprintf(locBuff, sizeof(locBuff), "point_lights[%d].linear", i);
		uniform_point_light[i].uniform_linear = glGetUniformLocation(shaderID, locBuff);

		snprintf(locBuff, sizeof(locBuff), "point_lights[%d].exponent", i);
		uniform_point_light[i].uniform_exponent = glGetUniformLocation(shaderID, locBuff);
	}

	uniform_spot_light_count = glGetUniformLocation(shaderID, "point_light_count");

	for (size_t i = 0; i < MAX_SPOT_LIGHTS; i++)
	{
		char locBuff[100] = { '\0' };
		snprintf(locBuff, sizeof(locBuff), "spot_lights[%d].base.base.colour", i);
		uniform_spot_light[i].uniform_colour = glGetUniformLocation(shaderID, locBuff);

		snprintf(locBuff, sizeof(locBuff), "spot_lights[%d].base.base.ambient_intensity", i);
		uniform_spot_light[i].uniform_ambient_intensity = glGetUniformLocation(shaderID, locBuff);

		snprintf(locBuff, sizeof(locBuff), "spot_lights[%d].base.base.diffuse_intensity", i);
		uniform_spot_light[i].uniform_diffuse_intensity = glGetUniformLocation(shaderID, locBuff);

		snprintf(locBuff, sizeof(locBuff), "spot_lights[%d].base.position", i);
		uniform_spot_light[i].uniform_light_position = glGetUniformLocation(shaderID, locBuff);

		snprintf(locBuff, sizeof(locBuff), "spot_lights[%d].base.constant", i);
		uniform_spot_light[i].uniform_constant = glGetUniformLocation(shaderID, locBuff);

		snprintf(locBuff, sizeof(locBuff), "spot_lights[%d].base.linear", i);
		uniform_spot_light[i].uniform_linear = glGetUniformLocation(shaderID, locBuff);

		snprintf(locBuff, sizeof(locBuff), "spot_lights[%d].base.exponent", i);
		uniform_spot_light[i].uniform_exponent = glGetUniformLocation(shaderID, locBuff);

		snprintf(locBuff, sizeof(locBuff), "spot_lights[%d].direction", i);
		uniform_spot_light[i].uniform_direction = glGetUniformLocation(shaderID, locBuff);

		snprintf(locBuff, sizeof(locBuff), "spot_lights[%d].edge", i);
		uniform_spot_light[i].uniform_edge = glGetUniformLocation(shaderID, locBuff);
	}
}


void Shader::UseShader()
{
	glUseProgram(shaderID);
}

void Shader::ClearShader()
{
	if (shaderID != 0)
	{
		glDeleteProgram(shaderID);
		shaderID = 0;
	}

	uniformModel = 0;
	uniformProjection = 0;
}

void Shader::SetDirectionalLight(DirectinalLight * d_light)
{
	d_light->UseLight(uniform_direction_light.uniform_ambient_intensity, 
						uniform_direction_light.uniform_colour, 
						uniform_direction_light.uniform_diffuse_intensity, 
						uniform_direction_light.uniform_light_direction);
}

void Shader::SetPointLights(PointLight * p_light, unsigned int light_count)
{
	if (light_count > MAX_POINT_LIGHTS) light_count = MAX_POINT_LIGHTS;

	glUniform1i(uniform_point_light_count, light_count);

	for (size_t i = 0; i < light_count; i++)
	{
		p_light[i].UseLight(uniform_point_light[i].uniform_ambient_intensity, uniform_point_light[i].uniform_colour,
			uniform_point_light[i].uniform_diffuse_intensity, uniform_point_light[i].uniform_light_position,
			uniform_point_light[i].uniform_constant, uniform_point_light[i].uniform_linear, uniform_point_light[i].uniform_exponent);
	}
}

void Shader::SetSpotLights(SpotLight * s_light, unsigned int light_count)
{
	if (light_count > MAX_SPOT_LIGHTS) light_count = MAX_SPOT_LIGHTS;

	glUniform1i(uniform_spot_light_count, light_count);

	for (size_t i = 0; i < light_count; i++)
	{
		s_light[i].UseLight(uniform_spot_light[i].uniform_ambient_intensity, uniform_spot_light[i].uniform_colour,
			uniform_spot_light[i].uniform_diffuse_intensity, uniform_spot_light[i].uniform_light_position, uniform_spot_light[i].uniform_direction,
			uniform_spot_light[i].uniform_constant, uniform_spot_light[i].uniform_linear, uniform_spot_light[i].uniform_exponent,
			uniform_spot_light[i].uniform_edge);
	}
}


void Shader::AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType)
{
	GLuint theShader = glCreateShader(shaderType);

	const GLchar* theCode[1];
	theCode[0] = shaderCode;

	GLint codeLength[1];
	codeLength[0] = strlen(shaderCode);

	glShaderSource(theShader, 1, theCode, codeLength);
	glCompileShader(theShader);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(theShader, sizeof(eLog), NULL, eLog);
		printf("Error compiling the %d shader: '%s'\n", shaderType, eLog);
		return;
	}

	glAttachShader(theProgram, theShader);
}

GLuint Shader::GetViewLocation()
{
	return uniformView;
}

GLuint Shader::GetAmbientIntensityLocation()
{
	return uniform_direction_light.uniform_ambient_intensity;
}

GLuint Shader::GetAmbientColour()
{
	return uniform_direction_light.uniform_colour;
}

GLuint Shader::GetEyePosition()
{
	return uniformEyePosition;
}

GLuint Shader::GetDiffuseIntensity()
{
	return uniform_direction_light.uniform_diffuse_intensity;
}

GLuint Shader::GetLightDirection()
{
	return uniform_direction_light.uniform_light_direction;
}

GLuint Shader::GetProjectionLocation()
{
	return uniformProjection;
}
GLuint Shader::GetModelLocation()
{
	return uniformModel;
}

GLuint Shader::GetSpecularIntensity()
{
	return uniformSpecularIntensity;
}

GLuint Shader::GetShininess()
{
	return uniformShininnes;
}


Shader::~Shader()
{
	ClearShader();
}
