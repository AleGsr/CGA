#version 460 core

layout (location = 0) in vec4 vPosition;
layout (location = 1) in vec2 vTexCoord;

uniform mat4 model;
uniform mat4 camera;
uniform mat4 projection;
uniform float height;

uniform sampler2D textureHeight;

//Combinando model y camera da el model view


out vec2 texCoord;

void main()
{
	
	float Luminosidad = dot(vec3(0.299, 0.587, 0.114));
	float altura = Luminosidad

	texCoord = vTexCoord;
	gl_Position = projection * camera * model * vPosition;

}