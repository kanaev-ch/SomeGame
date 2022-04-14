#version 330 core
out vec4 FragColor;//output colors

//input from vertex shader
in vec3 color;
in vec2 texCoord;

//intermediate var for output if discard pixel
vec4 texColor;

uniform sampler2D tex0;//texture coordinates

//uniform ON or OFF color or texture of object
uniform bool tex_or_clr = true;

//flag of selected person
uniform bool selected_flag = false;

void main()
{
	if (tex_or_clr == false)
		FragColor = vec4(color, 1.0f);//if only color draw without texture
	else
	{
		//block without discard pixel lower alpha
		//if (selected_flag) FragColor = texture(tex0, texCoord) * vec4(vec3(1.0f), 1.0f);//selected backgroud light
		//else FragColor = texture(tex0, texCoord) * vec4(vec3(0.9f), 1.0f);//not selected backgroud light

		//block with discard pixel lower alpha
		if (selected_flag) texColor = texture(tex0, texCoord) * vec4(vec3(1.0f), 1.0f);//selected backgroud light
		else texColor = texture(tex0, texCoord) * vec4(vec3(0.9f), 1.0f);//selected backgroud light
		if(texColor.a < 0.1)
			discard;
		FragColor = texColor;
	}
}