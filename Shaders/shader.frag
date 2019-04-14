#version 330

in vec4 vCol;
in vec3 normal_vector;
in vec3 frag_pos;
out vec4 colour;

const int MAX_POINT_LIGHTS = 3;
const int MAX_SPOT_LIGHT = 3;

struct Light
{
	vec3 colour;
	float ambient_intensity;
	float diffuse_intensity;
};

struct DirectionalLight
{
	Light base;
	vec3 light_direction;
};

struct PointLight
{
	Light base;
	vec3 position;
	float constant;
	float linear;
	float exponent;
};

struct SpotLight
{
	PointLight base;
	vec3 direction;
	float edge;
};

struct Material
{
	float specular_intensity;
	float shininess;
};

uniform int point_light_count;
uniform int spot_light_count;


uniform DirectionalLight directional_light;
uniform PointLight point_lights[MAX_POINT_LIGHTS];
uniform SpotLight spot_lights[MAX_SPOT_LIGHT];
uniform Material material;

uniform vec3 eye_position;

vec4 calculate_light_by_direction(Light light, vec3 direction)
{
	vec4 ambient_colour = vec4(light.colour, 1.0f) * light.ambient_intensity;
	float diffuse_factor = max(dot(normalize(normal_vector), normalize(direction)), 0.0f);
	vec4 diffuse_colour = vec4(light.colour, 1.0f) * light.diffuse_intensity * diffuse_factor;
	vec4 specular_colour = vec4(0, 0, 0, 0);

	if(diffuse_factor > 0.0f)
	{
		vec3 frag_to_eye = normalize(eye_position - frag_pos);
		vec3 reflected_vertex = normalize(reflect(direction, normalize(normal_vector)));

		float specular_factor = dot(frag_to_eye, reflected_vertex);
		if(specular_factor > 0.0f)
		{
			specular_factor = pow(specular_factor, material.shininess); 
			specular_colour = vec4(light.colour * material.specular_intensity * specular_factor, 1.0f);
		}
	}
	return (ambient_colour + diffuse_colour + specular_colour);
}

vec4 calculate_directional_light()
{
	return calculate_light_by_direction(directional_light.base, directional_light.light_direction);
}

vec4 calc_point_light(PointLight p_light)
{
	vec3 direction = frag_pos - p_light.position;
		float distance = length(direction);
		direction = normalize(direction);
		
		vec4 colour = calculate_light_by_direction(p_light.base, direction);
		float attenuation = p_light.exponent * distance * distance + 
							p_light.linear * distance +
							p_light.constant;
							
		return (colour / attenuation);
}

vec4 calc_spot_light(SpotLight sLight)
{
	vec3 rayDirection = normalize(frag_pos - sLight.base.position);
	float slFactor = dot(rayDirection, sLight.direction);
	
	if(slFactor > sLight.edge)
	{
		vec4 colour = calc_point_light(sLight.base);
		
		return colour * (1.0f - (1.0f - slFactor)*(1.0f/(1.0f - sLight.edge)));
		
	} else {
		return vec4(0, 0, 0, 0);
	}
}

vec4 calculate_spot_lights()
{
	vec4 totalColour = vec4(0, 0, 0, 0);
	for(int i = 0; i < spot_light_count; i++)
	{		
		totalColour += calc_spot_light(spot_lights[i]);
	}
	
	return totalColour;
}


vec4 calculate_point_light()
{
	vec4 total_colour = vec4(0,0,0,0);
	for(int i = 0; i < point_light_count; i++)
	{
		total_colour += calc_point_light(point_lights[i]);
	}
	return total_colour;
}



void main()
{
	vec4 final_color = calculate_directional_light();
	final_color += calculate_point_light();
	final_color += calculate_spot_lights();
	
	colour = final_color;
}