#version 460 core

layout (location = 0) in vec4 vPosition;
layout (location = 1) in vec2 vTexCoord;

uniform mat4 model;
uniform mat4 camera;
uniform mat4 projection;

uniform sampler2D texture1;
uniform float height;


out vec2 texCoord;

void main()
{
	texCoord = vTexCoord;
	vec4 heightColor = texture(texture1, texCoord);
	float Luminosity = 	 0.2126 * heightColor.r + 0.7152 *heightColor.g + 0.0722 * heightColor.b;
	vec4 newPosition = vPosition;
	newPosition.y += Luminosity * height; 
	gl_Position = projection * camera * model * newPosition;

}