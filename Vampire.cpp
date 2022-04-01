#include "Vampire.h"



Vampire::Vampire(const char* vertexFile, const char* fragmentFile, const char* image, const char* image2, float x_, float y_, float z_, float sprite_h_)
{
	//change global height of poligon
	vertices[10] = vertices[18] = sprite_h_;

	direction = true;

	std::string vertexCode = get_file_contents(vertexFile);//func takes simbols from file to string
	std::string fragmentCode = get_file_contents(fragmentFile);//func takes simbols from file to string

	const char* vertexSource = vertexCode.c_str();//func takes simbols from string to array of chars
	const char* fragmentSource = fragmentCode.c_str();//func takes simbols from string to array of chars

	//create and compile vertex shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);
	compileErrors(vertexShader, "VERTEX");//check vertex compile errors

	//create and compile fragment shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);
	compileErrors(fragmentShader, "FRAGMENT");//check fragment compile errors

	//create shader programm and link all shaders to it
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	compileErrors(shaderProgram, "PROGRAM");//check shader programm compile errors

	//delete shaders, they dont need anymore
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	//generate VAO objects in vector array
	generate_VAO_VBO(VAO_1, VBO_1, 1);
	generate_VAO_VBO(VAO_2, VBO_2, 2);
	generate_VAO_VBO(VAO_4, VBO_4, 4);
	generate_VAO_VBO(VAO_5, VBO_5, 5);
	generate_VAO_VBO(VAO_6, VBO_6, 6);
	generate_VAO_VBO(VAO_8, VBO_8, 8);
	generate_VAO_VBO(VAO_10, VBO_10, 10);

	//generate EBO obj
	glGenBuffers(1, &EBO);

	//block of creating VAO, VBO, EBO objects in vector arrays with parameters
	//reset texture coordinates for each EBO
	configure_VAO_VBO(vertices, sizeof(vertices), indices, sizeof(indices), VAO_1, VBO_1, 1, EBO, direction);
	configure_VAO_VBO(vertices, sizeof(vertices), indices, sizeof(indices), VAO_2, VBO_2, 2, EBO, direction);
	configure_VAO_VBO(vertices, sizeof(vertices), indices, sizeof(indices), VAO_4, VBO_4, 4, EBO, direction);
	configure_VAO_VBO(vertices, sizeof(vertices), indices, sizeof(indices), VAO_5, VBO_5, 5, EBO, direction);
	configure_VAO_VBO(vertices, sizeof(vertices), indices, sizeof(indices), VAO_6, VBO_6, 6, EBO, direction);
	configure_VAO_VBO(vertices, sizeof(vertices), indices, sizeof(indices), VAO_8, VBO_8, 8, EBO, direction);
	configure_VAO_VBO(vertices, sizeof(vertices), indices, sizeof(indices), VAO_10, VBO_10, 10, EBO, direction);


	//matrix of position tile, and changing to needed position here
	view = glm::mat4(1.0f);
	x = x_; y = y_; z = z_;
	view = glm::translate(view, glm::vec3(x, y, z));

	//create texture object
	create_Texture(image, texture);
	create_Texture(image2, texture2);

}


Vampire::~Vampire()
{
	//delete all elements
	for (int i = 0; i < sizeof(VAO_1); i++) glDeleteVertexArrays(1, &VAO_1[i]);
	for (int i = 0; i < sizeof(VBO_1); i++) glDeleteBuffers(1, &VBO_1[i]);
	for (int i = 0; i < sizeof(VAO_2); i++) glDeleteVertexArrays(1, &VAO_2[i]);
	for (int i = 0; i < sizeof(VBO_2); i++) glDeleteBuffers(1, &VBO_2[i]);
	for (int i = 0; i < sizeof(VAO_4); i++) glDeleteVertexArrays(1, &VAO_4[i]);
	for (int i = 0; i < sizeof(VBO_4); i++) glDeleteBuffers(1, &VBO_4[i]);
	for (int i = 0; i < sizeof(VAO_5); i++) glDeleteVertexArrays(1, &VAO_5[i]);
	for (int i = 0; i < sizeof(VBO_5); i++) glDeleteBuffers(1, &VBO_5[i]);
	for (int i = 0; i < sizeof(VAO_6); i++) glDeleteVertexArrays(1, &VAO_6[i]);
	for (int i = 0; i < sizeof(VBO_6); i++) glDeleteBuffers(1, &VBO_6[i]);
	for (int i = 0; i < sizeof(VAO_8); i++) glDeleteVertexArrays(1, &VAO_8[i]);
	for (int i = 0; i < sizeof(VBO_8); i++) glDeleteBuffers(1, &VBO_8[i]);
	for (int i = 0; i < sizeof(VAO_10); i++) glDeleteVertexArrays(1, &VAO_10[i]);
	for (int i = 0; i < sizeof(VBO_10); i++) glDeleteBuffers(1, &VBO_10[i]);
	glDeleteBuffers(1, &EBO);
	glDeleteProgram(shaderProgram);
	glDeleteTextures(1, &texture);
	glDeleteTextures(1, &texture2);
}

void Vampire::Draw(Camera& camera, float time_)
{
	//activate shader programm
	glUseProgram(shaderProgram);

	//load to vertex uniform current position of tile
	int viewLoc = glGetUniformLocation(shaderProgram, "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

	//aplying camera uniform fo look at
	camera.Matrix(45.0f, 0.1f, 100.0f, shaderProgram, "camMatrix");

	//bind VAO
	//glBindVertexArray(VAO);

	//time is time = float(glfwGetTime());
/*	int time = int(time_ * 100) % (25 * sizeof(VAO_8) / sizeof(int));

	//bind VAO
	if (time >= 0 && time <= 24) glBindVertexArray(VAO_8[0]);
	if (time >= 25 && time <= 49) glBindVertexArray(VAO_8[1]);
	if (time >= 50 && time <= 74) glBindVertexArray(VAO_8[2]);
	if (time >= 75 && time <= 99) glBindVertexArray(VAO_8[3]);
	if (time >= 100 && time <= 124) glBindVertexArray(VAO_8[4]);
	if (time >= 125 && time <= 149) glBindVertexArray(VAO_8[5]);
	if (time >= 150 && time <= 174) glBindVertexArray(VAO_8[6]);
	if (time >= 175 && time <= 199) glBindVertexArray(VAO_8[7]);*/

	//time is time = float(glfwGetTime());
	int time = int(time_ * 100) % (25 * sizeof(VAO_6) / sizeof(int));

	//bind VAO
	if (time >= 0 && time <= 24) glBindVertexArray(VAO_6[0]);
	if (time >= 25 && time <= 49) glBindVertexArray(VAO_6[1]);
	if (time >= 50 && time <= 74) glBindVertexArray(VAO_6[2]);
	if (time >= 75 && time <= 99) glBindVertexArray(VAO_6[3]);
	if (time >= 100 && time <= 124) glBindVertexArray(VAO_6[4]);
	if (time >= 125 && time <= 149) glBindVertexArray(VAO_6[5]);

	//bind texture
	//загружаем из юниформы текстурные координаты, которые загружены из масссива в вертексный, потом в фрагментный, потом в юниформу tex0
	tex0Uni = glGetUniformLocation(shaderProgram, "tex0");//создаем перем в кот будем хранить указатель на переменную uniform
	glUseProgram(shaderProgram);
	glUniform1i(tex0Uni, 0);//загружаем в юниформу ID текстурного блока с картинкой (тот, что активировали ранее glActiveTexture(GL_TEXTURE0);)
//	glBindTexture(GL_TEXTURE_2D, texture);
	glBindTexture(GL_TEXTURE_2D, texture2);

	//draw element
	glDrawElements(GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_INT, 0);
}