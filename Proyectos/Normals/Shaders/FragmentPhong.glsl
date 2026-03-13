#version 460 core

in vec4 vertexColor; 
out vec4 outColor;

in vec3 fragmentPosition;
in vec3 normal;

uniform vec3 eye; 


struct Light 
{
	vec4 position;
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
	return max(dot(norm, lightV), 0.0) * m.diffuse * l.diffuse; 
}

vec4 Specular(Light l, Material m, vec3 lightV, vec3 viewV, vec3 norm)
{
	vec3 refl = reflect(- lightV, norm); 
	vec4 spec = vec4(0.0);

	if(dot(lightV, norm) > 0.0)
	{
		float specular = pow(max(dot(viewV, refl), 0.0), m.shininess);
		spec = specular * m.specular * l.specular;
	}
	return spec;
	//return clamp(spec, 0.0,1.0);
}





void main()
{
	vec3 norm = normalize( normal );
	vec3 lightV = normalize( vec3(light.position) - fragmentPosition); 
	vec3 viewV = normalize( eye - fragmentPosition ); 
	
	//Calculamos ADS
	vec4 ADS =  Ambient(light, material) +
				Diffuse(light, material, lightV, norm) +
				Specular(light, material, lightV, viewV, norm);


	outColor = clamp(ADS, 0.0,1.0);

}