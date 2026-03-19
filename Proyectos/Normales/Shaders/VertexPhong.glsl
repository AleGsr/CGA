#version 460 core

layout (location = 0) in vec4 vPosition;
layout (location = 1) in vec3 vNormal;

out vec3 fragmentPosition;
out vec3 normal;

uniform float time;

uniform mat4 camera;
uniform mat4 projection;
uniform mat4 model;

float Ondas (float x, float z, float amplitud, float fase, float frecuencia)
{
	return amplitud * cos(frecuencia * (x*x + z*z) + fase);
}

void main ()
{  

	float amplitud = 0.1;
	float frecuencia = 10.0;
	float fase = time;

	vec4 newPosition = vPosition;

	newPosition.y = Ondas(newPosition.x, newPosition.z, amplitud, fase, frecuencia);

	//Posición del espacio al mundo
	vec4 worldPos = model * newPosition;
	fragmentPosition = worldPos.xyz;

	//Normales con derivadas parciales
	float onda = frecuencia * (newPosition.x * newPosition.x + newPosition.z * newPosition.z) + fase;
	float dydx = -amplitud * sin(onda) * frecuencia * 2.0 * newPosition.x;
	float dydz = -amplitud * sin(onda) * frecuencia * 2.0 * newPosition.z;
	vec3 newNormal = normalize(vec3(-dydx, 1.0, -dydz));

	normal = normalize(mat3(transpose(inverse(model))) * newNormal);


	//Posicion final
	gl_Position = projection * camera * worldPos;


}



