#version 460 core

layout (location = 0) in vec4 vPosition;
layout (location = 1) in vec4 vNormal;

out vec4 fragmentPosition;
out vec4 normal;

uniform float time;

uniform mat4 camera;
uniform mat4 projection;
uniform mat4 model;


void main ()
{  

	//Posición del espacio al mundo
	vec4 worldPosition = model * vPosition;
	fragmentPosition = worldPosition;

	//Transformamos la normal
	mat4 matForNormal = transpose(inverse(camera * model));
	normal = normalize(matForNormal * vNormal);

	//Posicion final
	vec4 newPosition = projection * camera * vec4(fragmentPosition, 1.0);
	gl_Position = newPosition;


}



