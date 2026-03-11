#version 460 core

layout (location = 0) in vec4 vPosition;
layout (location = 1) in vec2 vTexCoord;

uniform mat4 model;
uniform mat4 camera;
uniform mat4 projection;

uniform vec2 tiles;
uniform float indexX;
uniform float indexY;


float sizeTileX;
float sizeTileY;


out vec2 texCoord;

void main()
{
	texCoord = vTexCoord;

	//Se calcula el tamaño de cada tile
	sizeTileX = texCoord.x / tiles.x;
	sizeTileY = texCoord.y / tiles.y;

	float sizeX = (1.0/tiles.x);
	float sizeY = (1.0/tiles.y);
	
	//Se aplica el tamaño al tile
	texCoord.x = (sizeTileX + (sizeX * indexX)) + tiles.x;
	texCoord.y = (sizeTileY + (sizeY * indexY)) + tiles.y;



	gl_Position = projection * camera * model * vPosition;

}