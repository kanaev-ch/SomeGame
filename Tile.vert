#version 330 core
layout (location = 0) in vec3 aPos;//position of tile
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTex;//texture coordinates

//output to fragment shader
out vec3 color;
out vec2 texCoord;

uniform mat4 view;//matrix for tile position

uniform mat4 camMatrix;//matrix for camera look at

void main()
{
	gl_Position = camMatrix * view * vec4(aPos, 1.0f);

	color = aColor;

	texCoord = aTex;
}