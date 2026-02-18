#version 460 core

in vec2 texCoord;
out vec4 outColor;

uniform sampler2D texture0;
uniform sampler2D texture1;
uniform float mixerV;

void main()
{
	vec4 text01 = texture(texture0, texCoord);
	vec4 text02 = texture(texture1, texCoord);
	outColor = mix(text01, text02, mixerV);
}