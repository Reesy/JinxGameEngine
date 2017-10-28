#version 330 core
layout (location = 0) in vec3 position; // The position variable has attribute position 0
layout (location = 1) in vec3 normal;
out vec4 vertexColor; // Specify a color output to the fragment shader

uniform mat4 projection;
uniform mat4 model;
uniform mat4 view;
uniform vec3 inColor;

void main()
{
	vertexColor = vec4(inColor,1.0); 
	 gl_Position = projection * model * vec4(position.xy, 0.0, 1.0);
}