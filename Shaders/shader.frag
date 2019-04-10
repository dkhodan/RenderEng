#version 330

in vec4 vCol;
in vec3 normal_vector;
in vec3 frag_pos;
out vec4 colour;

struct DirectionalLight
{
	vec3 colour;
	float ambientIntensity;
	vec3 light_direction;
	float diffuse_intensity;
};

struct Material
{
	float specular_intensity;
	float shininess;
};

uniform DirectionalLight directionalLight;
uniform Material material;

uniform vec3 eye_position;

void main()
{
vec4 ambientColour = vec4(directionalLight.colour, 1.0f) * directionalLight.ambientIntensity;
	
float diffuse_factor = max(dot(normalize(normal_vector), normalize(directionalLight.light_direction)), 0.0f);
	
vec4 diffuse_colour = vec4(directionalLight.colour, 1.0f) * directionalLight.diffuse_intensity * diffuse_factor;

vec4 specular_colour = vec4(0, 0, 0, 0);

if(diffuse_factor > 0.0f)
{
	vec3 frag_to_eye = normalize(eye_position - frag_pos);
	vec3 reflected_vertex = normalize(reflect(directionalLight.light_direction, normalize(normal_vector)));

	float specular_factor = dot(frag_to_eye, reflected_vertex);
	if(specular_factor > 0.0f)
	{
		specular_factor = pow(specular_factor, material.shininess); 
		specular_colour = vec4(directionalLight.colour * material.specular_intensity * specular_factor, 1.0f);
	}
}
	
	colour = vCol * (ambientColour + diffuse_colour + specular_colour);
}