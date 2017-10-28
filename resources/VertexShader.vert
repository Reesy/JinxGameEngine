#version 330 core
layout (location = 0) in vec3 position; // The position variable has attribute position 0
layout (location = 1) in vec2 texCoord;


uniform bool hasTexture;
uniform vec3 inColor;
uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;

uniform sampler2D ourTexture;

out vec4 vertexColor; // Specify a color output to the fragment shader

void main()
{
	if(hasTexture == true){
		gl_Position = projection * view * model * vec4(position, 1.0);
		vertexColor = texture(ourTexture, texCoord);
	}else{
		gl_Position = projection * view * model * vec4(position, 1.0);
		vertexColor = vec4(inColor, 1.0); 
	}
}