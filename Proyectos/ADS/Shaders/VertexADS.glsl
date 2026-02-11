#version 460 core

layout (location = 0) in vec4 vPosition;
layout (location = 1) in vec4 vColor;

out vec4 vertexColor;
uniform float time;
uniform mat4 camera;
uniform mat4 projection;
uniform mat4 model;


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
uniform vec3 eye;

vec3 Normal = vec3(0.0, 1.0, 0.0);
vec3 norm = normalize( Normal );
vec3 lightv = normalize (light.position - vPosition)
vec3 viewv = normalize( vec3(0.,0.,0.) - vPosition );
vec3 refl = reflect( vec3(0.,0.,0.) - lightv, norm );

vec4 Ambient(struct Light light, struct Material material)
{
	return light.ambient * material.ambient;
}

vec4 Diffuse(struct Light light, struct Material material, vec3 Normal)
{
	vec4 diffuse = max(0.0, dot(lightv,  norm)) * material.diffuse * light.diffuse;
	return diffuse;
}

vec4 Specular(struct Light light, struct Material material, vec3 eye, vec3 Normal)
{
	vec3 specular = vec3( 0.0, 0.0, 0.0 );
	if (dot(lightv,viewv) > 0.0)
	{
		specular = pow(max(0.0, dot(viewv, refl)),
						material.shininess) * material.specular * 
						light.specular;
	}
	return specular;
	
	//vec4 resultMultSpecular = -light.specular * material.specular;
	//vec3 refl = reflect(-DirectionLight, Normal);
	//float resultDot = pow(max(dot(DirectionView, refl), 0.0), material.shininess);
	//return resultMultSpecular * resultDot;
}

vec4 ADS(Light light, Material material, vec3 Normal, vec3 eye )
{
	return Ambient(light, material) + Diffuse(light, material, Normal) + Specular(light, material, eye, Normal);
}






void main ()
{  		
	

	vec4 WorldSpace = camera * model * vPosition;



	//transpuesta de la matriz
	mat4 matForNormal = transpose(inverse(camera * model));


	//Normal del plano
	vec3 newNormal = normalize((matForNormal * vec4(Normal, 0.0)).xyz);


	vec3 SpaceLight = (camera * vec4(light.position, 1.0)).xyz; //La posicion de la luz en el espacio
	vec3 DirectionLight = normalize(SpaceLight - WorldSpace.xyz); //La dirección de la luz
	vec3 DirectionView = normalize(-WorldSpace.xyz); //Hacia donde va a pegar la luz


	//ADS
	vertexColor = ADS(light, material, newNormal, eye);


	//gl_Position = projection * WorldSpace;
	gl_Position = projection * camera * model * vPosition;
	vertexColor = vec4(1.0,0.0,0.0,1.0);
	
}

