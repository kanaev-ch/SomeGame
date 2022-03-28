#pragma once
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <fstream>
#include <sstream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stb/stb_image.h>

#include "Camera.h"
#include "get_file_contents.h"

//std::string get_file_contents(const char* filename);

class Person
{
public:
	GLfloat vertices[32] =
	{	//	COORDINATES		/		COLORS					//	Texture coordinates
		-0.5f,  0.0f,  0.0f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f,
		-0.5f,  0.0f,  1.0f,		0.0f, 1.0f, 0.0f,		0.0f, 1.0f,
		 0.5f,  0.0f,  1.0f,		0.0f, 0.0f, 1.0f,		1.0f, 1.0f,
		 0.5f,  0.0f,  0.0f,		1.0f, 1.0f, 0.0f,		1.0f, 0.0f,
	};

	GLuint indices[6] =
	{
		 0,  1,  2,
		 0,  3,  2,
	};

	//shader and its components
	GLuint shaderProgram;
	GLuint VAO;
	GLuint VBO;
	GLuint EBO;

	//for texture of tile
	GLuint texture;
	GLuint tex0Uni;

	//matrix position of tile and its coordinates
	glm::mat4 view;
	float x, y, z;

	Person(const char* vertexFile, const char* fragmentFile, const char* image, float x_, float y_, float z_, float sprite_h_);
	~Person();

	void Draw(Camera& camera);

private:
	void compileErrors(unsigned int shader, const char* type);//проверка ошибок на комипиляцию, линковку шейдера
};

