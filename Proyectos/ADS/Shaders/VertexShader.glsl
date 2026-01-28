#version 460 core

layout (location = 0) in vec4 vPosition;
layout (location = 1) in vec4 vColor;

out vec4 vertexColor;
uniform float time;
uniform mat4 cam;


struct Light 
{
	vec3 position;
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
}

struct Material
{
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
}

uniform Light light;
uniform Material material;

vec4 Ambient(struct Light l, struct Material m)
{

}

vfec4 Diffuse()
{

}

vec4 Specular()
{
	
}

vec4 ADS()
{
	return Ambient() + Diffuse() + Specular();
}

vec3 Normal = vec3(0.0, 1.0, 0.0);

out vec4 outColor;


void main ()
{  		
	vertexColor = vColor;
	vec4 newPosition = vPosition;
	newPosition.x = newPosition.x + cos(time);
	gl_Position = newPosition;  //equivale a hacer return gl_Position	
}