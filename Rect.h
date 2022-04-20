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

#include "get_file_contents.h"

class Rect
{
public:
	GLfloat vertices[32] =
	{	//	COORDINATES		/		COLORS					//	Texture coordinates
		-1.0f, -1.0f,  0.0f,		0.8f, 0.8f, 0.8f,		0.0f, 0.0f,
		-1.0f,  1.0f,  0.0f,		0.8f, 0.8f, 0.8f,		0.0f, 1.0f,
		 1.0f,  1.0f,  0.0f,		0.8f, 0.8f, 0.8f,		1.0f, 1.0f,
		 1.0f, -1.0f,  0.0f,		0.8f, 0.8f, 0.8f,		1.0f, 0.0f,
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

	//uniform address for texture
	GLuint tex0Uni;

	//matrix position of rect and its coordinates
	glm::mat4 view;
	float x_tr, y_tr, z_tr;
	float x_sc, y_sc, z_sc;

	//Default constructor without GLfloat vertices
	Rect(const char* vertexFile, const char* fragmentFile, const char* image, float, float, float, float, float, float, float);

	//Default constructor with changed GLfloat vertices
	Rect(const char* vertexFile, const char* fragmentFile, const char* image, float, float, float, float, float, float, float, GLfloat *, int);
	~Rect();

	void Draw();

private:
	void compileErrors(unsigned int shader, const char* type);//проверка ошибок на комипиляцию, линковку шейдера
};

