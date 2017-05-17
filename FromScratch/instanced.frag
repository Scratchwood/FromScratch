#version 330 core

out vec4 out_color;

uniform sampler2D textureSampler;
uniform vec4 lightColor;
uniform float reflectivity;
uniform float shineDamper;

in DATA 
{
	vec2 uv;
	vec3 normal;
	vec3 lightDirection;
	vec3 cameraDirection;
} fs_in;

void main()
{
	vec3 normal = normalize(fs_in.normal);
	vec3 lightDir = normalize(fs_in.lightDirection);
	vec3 cameraDir = normalize(fs_in.cameraDirection);

	float brightness = max(dot(normal, lightDir), 0.1);
	vec4 diffuseColor = lightColor * brightness;

	vec3 reflected = reflect(-lightDir, normal);
	
	float specularFactor = max(dot(reflected, cameraDir), 0.0);
	float dampFactor = pow(specularFactor, shineDamper);

	vec4 specularColor = lightColor * reflectivity * dampFactor;

	out_color = texture(textureSampler, fs_in.uv) * diffuseColor + specularColor;
}