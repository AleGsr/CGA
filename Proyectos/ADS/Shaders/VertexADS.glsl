#version 460 core

layout (location = 0) in vec4 vPosition;
layout (location = 1) in vec4 vColor;

out vec4 vertexColor;
uniform float time;
uniform mat4 cam;
uniform mat4 projection;



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





vec4 Ambient(struct Light l, struct Material m)
{
	return light.ambient * material.ambient;
}

vec4 Diffuse(struct Light l, struct Material m, vec3 Normal)
{
	vec4 resultMultDiffuse = light.diffuse * material.diffuse;
	vec3 resultDot = dot(light.position, Normal);
	return resultMultDiffuse * resultDot;
}

vec4 Specular(struct Light l, struct Material m, vec3 eye, vec3 Normal)
{
	vec4 resultMultSpecular = -light.specular * material.specular;
	vec3 refl = reflect(vec3(0.0,0.0,0.0), Normal);
	vec3 resultDot = dot(eye, refl);
	return resultMultSpecular * resultDot;
}

vec4 ADS()
{
	return Ambient(l, m) + Diffuse(l, m, Normal) + Specular(l, m, eye, Normal);
}


vec3 Normal = vec3(0.0, 1.0, 0.0);
out vec4 outColor;


void main ()
{  		
	mat4 model = rotate(mat4(1.0), time, vec3(0.0, 1.0, 0.0));
	vec4 worldPos = model * vPosition;
	gl_Position = projection * camera * worldPos;
	mat3 normalMat = transpose(inverse(mat3(camera * model)));

	vec3 baseNormal = vec3(0.0,1.0,0.0);
    vec3 N = normalize(normalMat * baseNormal);

	vec3 L = normalize(light.position - worldPos.xyz);
    vec3 V = normalize(eye - worldPos.xyz);




	//Operaciones de transformaciones
	//outColor = ADS();
	//vec4 newPosition = vPosition;
	//Aplicar al vertice las transformaciones
	//Primero new pos con todas las transformaciones = myPosition, después calculo de ADS
	//gl_Position = newPosition;  //equivale a hacer return gl_Position	
}