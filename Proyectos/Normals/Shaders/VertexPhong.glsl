#version 460 core

layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec3 vNormal;

out vec3 fragmentPosition;
out vec3 normal;

uniform float time;

uniform mat4 camera;
uniform mat4 projection;
uniform mat4 model;


void main ()
{  

	//Posición del espacio al mundo
	vec4 worldPosition = model * vec4(vPosition, 1.0);
	fragmentPosition = vec3(worldPosition);

	//Transformamos la normal
	normal = normalize(mat3(transpose(inverse(model)))* vNormal);

	//Posicion final
	gl_Position = projection * camera * worldPosition;


}



