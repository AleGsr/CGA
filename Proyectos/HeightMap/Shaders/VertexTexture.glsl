#version 460 core

layout (location = 0) in vec4 vPosition;
layout (location = 1) in vec2 vTexCoord;

uniform mat4 model;
uniform mat4 camera;
uniform mat4 projection;

uniform sampler2D texture1;

//Combinando model y camera da el model view


out vec2 texCoord;

void main()
{
	vec4 heightColor = texture(texture1, vTexCoord);
	float Luminosity = 	 0.299 *heightColor.r + 0.587 *heightColor.g + 0.114 * heightColor.b;
	vec4 newPosition = vPosition;
	newPosition.y += Luminosity; 
	gl_Position = projection * camera * model * newPosition;

}