#pragma once
#include "Person.h"
#include "Global_Time.h"

class Lizardman :
	public Person
{
public:
	//textures
	GLuint texture_stand;
	GLuint texture_walk;
	GLuint texture_strike_sword;
	GLuint texture_injured;
	GLuint texture_defends;
	GLuint texture_fall;
	GLuint texture_dead;

	//enum of choice anime
	enum animation_enum {stand, walk, strike_sword, injured, defends, fall, dead};
	enum animation_enum anime;

	//Lizardman(const char* vertexFile, const char* fragmentFile, const char*, const char*, const char*, const char*, const char*, const char*, const char*, float x_, float y_, float z_, float sprite_h_);
	Lizardman(const char* vertexFile, const char* fragmentFile, const char*, const char*, const char*, const char*, const char*, const char*, const char*, float x_, float y_, float z_, float sprite_h_);
	~Lizardman();

	//func of anime
	void Anime_Cycle(int frames, GLuint* VAO, int size_VAO, GLuint& texture);
	void Anime_NON_Cycle(int frames, GLuint* VAO, int size_VAO, GLuint& texture);

	void Draw(GLFWwindow* window, Camera& camera);
};

