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

class Tile
{
public:
	GLfloat vertices[128] =
	{	//	COORDINATES		/		COLORS					//	Texture coordinates
		-0.5f, -0.5f,  0.0f,		1.0f, 0.0f, 0.0f,		0.0f, 0.5f,		//top
		-0.5f,  0.5f,  0.0f,		0.0f, 1.0f, 0.0f,		0.0f, 1.0f,
		 0.5f,  0.5f,  0.0f,		0.0f, 0.0f, 1.0f,		1.0f, 1.0f,
		 0.5f, -0.5f,  0.0f,		1.0f, 1.0f, 0.0f,		1.0f, 0.5f,

		-0.5f, -0.5f, -0.25f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f,		//side front
		-0.5f, -0.5f,  0.0f,		0.0f, 1.0f, 0.0f,		0.0f, 0.5f,
		 0.5f, -0.5f,  0.0f,		0.0f, 0.0f, 1.0f,		1.0f, 0.5f,
		 0.5f, -0.5f, -0.25f,		1.0f, 1.0f, 0.0f,		1.0f, 0.0f,

		-0.5f,  0.5f, -0.25f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f,		//side left
		-0.5f,  0.5f,  0.0f,		0.0f, 1.0f, 0.0f,		0.0f, 0.5f,
		-0.5f, -0.5f,  0.0f,		0.0f, 0.0f, 1.0f,		1.0f, 0.5f,
		-0.5f, -0.5f, -0.25f,		1.0f, 1.0f, 0.0f,		1.0f, 0.0f,

		 0.5f, -0.5f, -0.25f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f,		//side right
		 0.5f, -0.5f,  0.0f,		0.0f, 1.0f, 0.0f,		0.0f, 0.5f,
		 0.5f,  0.5f,  0.0f,		0.0f, 0.0f, 1.0f,		1.0f, 0.5f,
		 0.5f,  0.5f, -0.25f,		1.0f, 1.0f, 0.0f,		1.0f, 0.0f,
	};

	GLuint indices[24] =
	{
		 0,  1,  2,
		 0,  3,  2,
		 4,  5,  6,
		 4,  7,  6,
		 8,  9, 10,
		 8, 10, 11,
		12, 13, 14,
		12, 15, 14,
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

//	Tile();
	Tile(const char* vertexFile, const char* fragmentFile, const char* image, float x_, float y_, float z_);
	
//	Tile(const Tile& tile);
	
	~Tile();

	void Draw(Camera & camera);

private:
	void compileErrors(unsigned int shader, const char* type);//проверка ошибок на комипиляцию, линковку шейдера

};

