#shader vertex
#version 330 

layout (location = 0) in vec4 position; 
layout (location = 1) in vec3 color;

out vec4 Color;

void main()
{
	gl_Position = position;
	Color = vec4(color, 1.0f);
};

#shader fragment
#version 330

out vec4 FragColor;
in vec4 Color;


void main()
{
	FragColor = Color;
};