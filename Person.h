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

#include <vector>

#include "Camera.h"
#include "get_file_contents.h"

//std::string get_file_contents(const char* filename);

class Person
{
public:
	GLfloat vertices[32] =
	{	//	COORDINATES		/		COLORS					//	Texture coordinates
		-0.5f,  0.0f,  0.0f,		1.0f, 0.0f, 0.0f,		1.0f, 0.0f,
		-0.5f,  0.0f,  1.0f,		0.0f, 1.0f, 0.0f,		1.0f, 1.0f,
		 0.5f,  0.0f,  1.0f,		0.0f, 0.0f, 1.0f,		0.0f, 1.0f,
		 0.5f,  0.0f,  0.0f,		1.0f, 1.0f, 0.0f,		0.0f, 0.0f,
	};

	GLuint indices[6] =
	{
		 0,  1,  2,
		 0,  3,  2,
	};

	//shader and its components
	GLuint shaderProgram;

	//Create VAO objects for different counts frames of texture

	GLuint VAO_1[1];
	GLuint VAO_2[2];
	GLuint VAO_3[3];
	GLuint VAO_4[4];
	GLuint VAO_5[5];
	GLuint VAO_6[6];
	GLuint VAO_7[7];
	GLuint VAO_8[8];
	GLuint VAO_9[9];
	GLuint VAO_10[10];
	GLuint VBO_1[1];
	GLuint VBO_2[2];
	GLuint VBO_3[3];
	GLuint VBO_4[4];
	GLuint VBO_5[5];
	GLuint VBO_6[6];
	GLuint VBO_7[7];
	GLuint VBO_8[8];
	GLuint VBO_9[9];
	GLuint VBO_10[10];

	GLuint EBO;

	//for texture of tile
	GLuint texture;
	GLuint tex0Uni;

	//matrix position of tile and its coordinates
	glm::mat4 view;
	float x, y, z;

	//height of sprite
	float sprite_h;

	bool direction;

	bool walk;
	float speed_move;

//	Person(const char* vertexFile, const char* fragmentFile, const char* image, float x_, float y_, float z_, float sprite_h_);
	virtual ~Person();

//changing height of sprite
	void change_Height_Sprite(float sprite_h_);

	void change_Direction(bool direction_);

	void Move(float x_, float y_, float z_);

	//bind texture
	void bind_Texture(GLuint& texture_);

	//bind VAO
	void bind_VAO(int frame_milliseconds_, float time, GLuint* VAO, int size_VAO, GLuint& texture_);

	virtual void Draw(Camera& camera, float time_);

//private:
	void compileErrors(unsigned int shader, const char* type);//проверка ошибок на комипиляцию, линковку шейдера

	friend void create_VAO(GLfloat* vertices, int sizeof_vertices, GLuint* indices, int sizeof_indices, float count_of_frames, float current_frame, GLuint& VAO, GLuint& VBO, GLuint& EBO);
	friend void create_Texture(const char* image, GLuint& texture);
	friend void generate_VAO_VBO(GLuint* VAO, GLuint* VBO, int size);
	friend void configure_VAO_VBO(GLfloat* vertices, int sizeof_vertices, GLuint* indices, int sizeof_indices, GLuint* VAO, GLuint* VBO, float count_frames, GLuint& EBO);
};

//func create VAO obj
void create_VAO(GLfloat* vertices, int sizeof_vertices, GLuint* indices, int sizeof_indices, float count_of_frames, float current_frame, GLuint& VAO, GLuint& VBO, GLuint& EBO);

//func create texture obj
void create_Texture(const char* image, GLuint& texture);

void generate_VAO_VBO(GLuint* VAO, GLuint* VBO, int size);

void configure_VAO_VBO(GLfloat* vertices, int sizeof_vertices, GLuint* indices, int sizeof_indices, GLuint* VAO, GLuint* VBO, float count_frames, GLuint& EBO, bool direction);
