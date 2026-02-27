#version 460 core

layout (location = 0) in vec4 vPosition;
layout (location = 1) in vec4 vColor;

out vec4 vertexColor;
uniform float time;
uniform mat4 cam;
uniform mat4 projection;
uniform mat4 model;
uniform vec3 eye;

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

uniform struct Light light;
uniform struct Material material;

vec3 Normal = vec3(0.0, 1.0, 0.0);
vec3 norm = normalize( Normal );
vec3 lightV = normalize( light.position - vPosition); //Posibles cambios: vPosition a vec3 myPosition
vec3 viewV = normalize( vec3(0.0,0.0,0.0) - vPosition); //Posibles cambios: vPosition a vec3 myPosition
vec3 refl = reflect(vec3(0.0,0.0,0.0) - lightV, norm);


vec4 Ambient(Light l, Material m)
{
	return m.ambient* l.ambient; 
}

vec4 Diffuse(Light l, Material m, vec3 lightV, vec3 norm)
{
	return max(0.0, dot(lightV, norm)) * m.diffuse * l.diffuse; 
}

vec4 Specular(Light l, Material m, vec3 viewV, vec3 refl)
{
	return pow(max(0.0, dot(viewV, refl)), m.shininess) * m.specular * l.specular;
}

vec4 ADS(Light l, Material m, vec3 lightV, vec3 norm, vec3 viewV, vec3 refl)
{
	return Ambient(m, l) + Diffuse(l, m, lightV, norm) + Specular(l, m, viewV, refl);
}



void main ()
{  
	vec4 newPosition = vPosition;
	vertexColor = vColor;

	newPosition = projection * camera * newPosition;
	gl_Position = newPosition;  //equivale a hacer return gl_Position	
}