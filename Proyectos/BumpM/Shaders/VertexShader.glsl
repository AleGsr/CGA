#version 460 core

layout (location = 0) in vec4 vPosition;
layout (location = 1) in vec2 vTexCoord;

out vec3 fragmentPosition;
out vec2 texCoord;

uniform float time;

uniform mat4 camera;
uniform mat4 projection;
uniform mat4 model;


void main ()
{  

	vec4 worldPos = model * vPosition;
	fragmentPosition = worldPos.xyz;

	texCoord = vTexCoord;

	//Posicion final
	gl_Position = projection * camera * worldPos;


}



