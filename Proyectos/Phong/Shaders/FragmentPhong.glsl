#version 460 core

in vec4 vertexColor; 
out vec4 outColor;

in vec3 fragPos;
in vec3 fragNormal;

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



void main()
{
	vec3 Normal = vec3(0.0, 1.0, 0.0);
	vec3 norm = normalize( Normal );
	vec3 lightV = normalize( light.position - fragPos); 
	vec3 viewV = normalize( eye - fragPos); 
	vec3 refl = reflect(-lightV, norm); 




	outColor = Ambient(light, material) 
			    + Diffuse(light, material, lightV, norm); 
		        + Specular(light, material, lightV, viewV, refl);
}