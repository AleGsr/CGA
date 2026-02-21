#version 460 core

layout (location = 0) in vec4 vPosition;
//layout (location = 1) in vec4 vColor;

uniform float time;
uniform mat4 camera;
uniform mat4 projection;

float Frequency(float x, float z, float amplitud, float phase, float frecuencia)
{
	return amplitud * cos(phase + frecuencia * (x*x + z*z));
}

void main ()
{  
    vec4 newPosition = vPosition;

	float amplitud = 0.12;
	float phase = time;
	float frecuencia = 4.5;


	newPosition.y = Frequency(newPosition.x, newPosition.z, amplitud, phase, frecuencia);


	newPosition = projection * camera * newPosition;
	
	gl_Position = newPosition;  //equivale a hacer return gl_Position	
}
