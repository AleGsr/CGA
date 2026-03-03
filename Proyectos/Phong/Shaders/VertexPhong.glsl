#version 460 core

layout (location = 0) in vec4 vPosition;
layout (location = 1) in vec3 vNormal;


uniform mat4 camera;
uniform mat4 projection;
uniform mat4 model;

out vec3 fragPos;
out vec3 fragNormal;


void main ()
{  
    vec4 worldPos = model * vPosition;
    fragPos = worldPos.xyz;
    mat3 normalMatrix = transpose(inverse(mat3(model)));
    fragNormal = normalize(normalMatrix * vNormal);

	gl_Position = projection * camera * worldPos;  //equivale a hacer return gl_Position	
}

