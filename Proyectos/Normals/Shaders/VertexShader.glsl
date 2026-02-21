#version 460 core

layout (location = 0) in vec4 vPosition;
layout (location = 1) in vec4 vColor;

out vec4 vertexColor;
uniform float time;
uniform mat4 cam;


void main ()
{  	
	//Plano con ondas
	mat4 modelView = view * model;
	vec4 newPosition = vPosition;
	newPosition.y 0 Func(vPosition.x, vPosition.z, amplitud, fase, frecuencia);

	//Calculo de normal para las ondas
	vec3 Vtx = vec3 (1.0, DyDx (newPosition.x, newPosition.z), 0); //tangente en X
	vec3 Vtz = vec3 (0.0, DyDz (newPosition.x, newPosition.z), 1); //tangente en Z

	vec3 normal = cross(Vtz, Vtx); //Normal de ondas sin transformaciones


	//Transformaciones a las normales
	mat4 matForNormal = transpose(inverse(modelView));
	vec3 newNormal = (matForNormal * vec4(normal,0.0)).xyz;
	newPosition = modelView * newPosition;


	//Calculamos ADS
	outColor = ADS(newposition, newNormal, ...);

	//Emitimos vertice
	gl_Position = projection * newPosition;  //equivale a hacer return gl_Position	
}