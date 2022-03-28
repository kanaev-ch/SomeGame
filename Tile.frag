#version 330 core
out vec4 FragColor;//output colors

//input from vertex shader
in vec3 color;
in vec2 texCoord;

uniform sampler2D tex0;//textur coordinates

void main()
{
	//FragColor = vec4(color, 1.0f);//if only color draw without texture
	FragColor = texture(tex0, texCoord);//draw with texture
}