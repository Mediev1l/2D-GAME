#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
uniform sampler2D texture1;
uniform float offsetX;

void main()
{
	//FragColor = texture(texture1,TexCoord);
	vec4 texColor = texture(texture1, vec2(TexCoord.x*offsetX,TexCoord.y));
    FragColor = texColor;
}