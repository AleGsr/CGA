#version 460 core

in vec4 vertexColor;
out vec4 outColor;
uniform float time;

struct Light
{
	vec3 position;
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
};


struct Material
{
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	float shininess;
};

uniform Light light;
uniform Material material;
uniform vec3 eye;

vec3 Normal = vec3(0.0,1.0,0.0);




vec4 Ambient(struct Light l, struct material m)
{
	return light.ambient * material.ambient;
}



void main()
{
	outColor = vertexColor;
}