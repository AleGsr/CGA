#version 460 core

layout (location = 0) in vec4 vPosition;
layout (location = 1) in vec4 vColor;

out vec4 vertexColor;
uniform float time;
uniform mat4 camera;
uniform mat4 projection;
uniform mat4 model;
uniform vec3 eye;

struct Light 
{
	vec3 position;
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
};

struct Material
{
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	float shininess;
};

uniform struct Light light;
uniform struct Material material;



vec4 Ambient(Light l, Material m)
{
	return m.ambient* l.ambient; 
}

vec4 Diffuse(Light l, Material m, vec3 lightV, vec3 norm)
{
	return max(0.0, dot(lightV, norm)) * m.diffuse * l.diffuse; 
}

vec4 Specular(Light l, Material m, vec3 lightV, vec3 viewV, vec3 refl)
{
	vec4 spec = vec4(0.0);
	if(dot(lightV, viewV) > 0.0)
	{
		spec = pow(max(0.0, dot(viewV, refl)), m.shininess) * 
		m.specular * l.specular;
	}
	return clamp(spec, 0.0,1.0);
}


void main ()
{  
	vec3 Normal = vec3(0.0, 1.0, 0.0);
	vec3 norm = normalize( Normal );
	vec3 lightV = normalize( light.position - vPosition.xyz); 
	vec3 viewV = normalize( eye - vPosition.xyz ); 
	vec3 refl = reflect(vec3(0.0,0.0,0.0) - lightV, norm); 


    vec4 newPosition = vPosition;
	mat4 matForNormal = transpose(inverse(camera * model));
	vec4 newNormal = matForNormal * vec4(norm, 0.0);



	newPosition = projection * camera * newPosition;
	
	vertexColor = Ambient(light, material) 
			    + Diffuse(light, material, lightV, norm); 
		      //+ Specular(light, material, lightV, viewV, refl);

	gl_Position = newPosition;  //equivale a hacer return gl_Position	
}

vec4 worldPos = model * vPosition;
    fragPos = worldPos.xyz;
    mat3 normalMatrix = transpose(inverse(mat3(model)));
    fragNormal = normalize(normalMatrix * vNormal);

	gl_Position = projection * camera * worldPos;  