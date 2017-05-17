#version 330 core

in vec3 position;
in vec2 texCoords;
in vec3 normal;
in mat4 model;


uniform mat4 projection;
uniform mat4 view;
uniform vec3 lightPosition;

out DATA 
{
	vec2 uv;
	vec3 normal;
	vec3 lightDirection;
	vec3 cameraDirection;
} vs_out;

void main()
 {
	vec4 transformedPosition = model * vec4(position, 1.0);
	gl_Position = projection *  view * transformedPosition;
	vs_out.uv = texCoords;
	vs_out.normal = (model * vec4(normal, 0.0)).xyz;
	vs_out.lightDirection = lightPosition - transformedPosition.xyz;
	vs_out.cameraDirection = (inverse(view) * vec4(0, 0, 0, 1)).xyz - transformedPosition.xyz;
}