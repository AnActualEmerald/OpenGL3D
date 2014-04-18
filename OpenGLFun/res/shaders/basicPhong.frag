#version 330


struct BaseLight
{
	vec3 color;
	float intensity;
};

struct DirectionalLight
{
	BaseLight base;
	vec3 dir;

};


uniform sampler2D diffuse;
uniform vec3 ambientLight;
uniform DirectionalLight dirLight;

varying vec2 texCoord0;
varying vec3 normal0;

vec4 calcLight(BaseLight base, vec3 dir, vec3 normal)
{
	float diffuseFact = dot(normal, -dir);
	
	vec4 diffuseCol = vec4(0, 0, 0, 0);
	
	if(diffuseFact > 0)
	{
		diffuseCol = vec4(base.color, 1) * base.intensity * diffuseFact;
	}
	
	return diffuseCol;
}

vec4 calcDirLight(DirectionalLight light, vec3 normal)
{
	return calcLight(light.base, -light.dir, normal);
}

void main()
{
	vec4 totalLight = vec4(ambientLight, 1);
	vec4 texCol = texture2D(diffuse, texCoord0); 
	
	vec3 norm = normalize(normal0);
	totalLight += calcDirLight(dirLight, norm);
	
	gl_FragColor = (texCol * totalLight);
	
}