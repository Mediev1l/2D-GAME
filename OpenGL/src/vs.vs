#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 color;

out vec4 Color;
void main()
{
	gl_Position = vec4(aPos, 1.0f);
	Color = vec4(color,1.0f);
}