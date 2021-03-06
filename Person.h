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
#include "Global_Time.h"
#include "Data.h"

//std::string get_file_contents(const char* filename);

class Person
{
public:
	GLfloat vertices[32] =
	{	//	COORDINATES		/		COLORS					//	Texture coordinates
		/*-0.5f,  0.0f,  0.0f,		1.0f, 0.0f, 0.0f,		1.0f, 0.0f,
		-0.5f,  0.0f,  1.0f,		0.0f, 1.0f, 0.0f,		1.0f, 1.0f,
		 0.5f,  0.0f,  1.0f,		0.0f, 0.0f, 1.0f,		0.0f, 1.0f,
		 0.5f,  0.0f,  0.0f,		1.0f, 1.0f, 0.0f,		0.0f, 0.0f,*/
		-0.5f,  0.0f,  0.0f,		0.8f, 0.8f, 0.8f,		1.0f, 0.0f,
		-0.5f,  0.0f,  1.0f,		0.8f, 0.8f, 0.8f,		1.0f, 1.0f,
		 0.5f,  0.0f,  1.0f,		0.8f, 0.8f, 0.8f,		0.0f, 1.0f,
		 0.5f,  0.0f,  0.0f,		0.8f, 0.8f, 0.8f,		0.0f, 0.0f,
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
	
	//uniform address for texture
	GLuint tex0Uni;

	//uniform address for flag of background light if selected
	GLuint uniSelected;

	//enum of choice anime
	ANIMATION_ENUM anime;

	//matrix position of tile and its coordinates
	glm::mat4 view;
	float x, y, z;

	//height of sprite
	float sprite_h;

	//directoin of person, true if to left
	//bool direction;
	PERSON_DIRECTION direction;

	//speed of moving person
	float speed_move;

	//flag selected person or not
	bool selected;

	//Array and its size of lifes and steps of person
	std::vector <int> lifes_steps;
	//int* lifes_steps;
	int size_lifes_steps;

	//Strength and agility
	int strength;
	int agility;

	//Initiative of person
	int initiative;

	//Type of person
	PERSON_TYPE person_type;

	//Range how far person move by cells
	//float walk_range_x, walk_range_y;

	//Dynamic array coords of person way, init new in default construct, walk_range its size
	Step* step;

	//Person walk range, init in default constructor of warrior, lizardman etc..., size of array step
	int walk_range;

	//Flag person move or not
	bool walk_flag;

	//Arr with whom person is in skirmish
	std::vector <Person*> skirmish;

	//Flag ON if non cycle anime playing, OFF when it stop
	bool is_anime_cycle_playing;

//	Person(const char* vertexFile, const char* fragmentFile, const char* image, float x_, float y_, float z_, float sprite_h_);
	virtual ~Person();

//changing height of sprite
	void change_Height_Sprite(float sprite_h_);

	//void change_Direction(bool direction_);
	void change_Direction(PERSON_DIRECTION direction_);

	//void Move(float x_, float y_, float z_);
	virtual bool Move(float x_, float y_, float z_) = 0;

	//bind texture
	void bind_Texture(GLuint& texture_);

	//bind VAO
	//int bind_VAO(int frame_milliseconds_, float time, GLuint* VAO, int size_VAO, GLuint& texture_);
	void bind_VAO(int frame_milliseconds_, float time, GLuint* VAO, int size_VAO, GLuint& texture_);

	//func of loading select flag in uniform for back light if Person selected
	void Selected_Uniform_Load(bool);

	//virtual void Change_Enum_Anime(int) = 0;
	virtual void Change_Enum_Anime(int);

	virtual void Draw(GLFWwindow* window, Camera& camera) = 0;

//private:
	void compileErrors(unsigned int shader, const char* type);//???????? ?????? ?? ???????????, ???????? ???????

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
