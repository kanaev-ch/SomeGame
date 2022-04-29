#version 330 core
out vec4 FragColor;//output colors

//input from vertex shader
in vec3 color;
in vec2 texCoord;

//intermediate var for output if discard pixel
vec4 texColor;

//Vectors of colors for tile
vec3 red = vec3(1.0f, 0.0f, 0.0f);
vec3 green = vec3(0.0f, 1.0f, 0.0f);
vec3 blue = vec3(0.0f, 0.0f, 1.0f);

//Uniform for changing color of tile
uniform int switch_clr = 7;

//texture coordinates
uniform sampler2D tex0;

//uniform ON or OFF color or texture of object
//uniform bool tex_or_clr = true;

void main()
{
	/*if (tex_or_clr == false)
		FragColor = vec4(color, 1.0f);//if only color draw without texture
	else*/
	//FragColor = texture(tex0, texCoord);//draw with texture


	//choose color of tile
	switch (switch_clr)
	{
	case 1: texColor = texture(tex0, texCoord) * vec4(red, 1.0f); break;
	case 2: texColor = texture(tex0, texCoord) * vec4(green, 1.0f); break;
	case 4: texColor = texture(tex0, texCoord) * vec4(blue, 1.0f); break;

	case 3: texColor = texture(tex0, texCoord) * vec4(red + green, 1.0f); break;
	case 5: texColor = texture(tex0, texCoord) * vec4(red + blue, 1.0f); break;
	case 6: texColor = texture(tex0, texCoord) * vec4(green + blue, 1.0f); break;
	case 7: texColor = texture(tex0, texCoord) * vec4(red + green + blue, 1.0f); break;

	default: texColor = texture(tex0, texCoord) * vec4(red + green + blue, 1.0f);
	}

	FragColor = texColor;
}