#pragma once
#include "Person.h"
#include "Global_Time.h"

class Warrior :
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
	enum ANIMATION_ENUM {stand, walk, strike_sword, injured, defends, fall, dead};
	ANIMATION_ENUM anime;

	//temp save current coords of person for calc range move
	//float x_move, y_move;

	Warrior(const char* vertexFile, const char* fragmentFile, const char*, const char*, const char*, const char*, const char*, const char*, const char*, float x_, float y_, float z_, float sprite_h_);
	~Warrior();

	//func of anime
	void Anime_Cycle(int frames, GLuint* VAO, int size_VAO, GLuint& texture);
	void Anime_NON_Cycle(int frames, GLuint* VAO, int size_VAO, GLuint& texture);

	void Change_Enum_Anime(int);

	//void Move(float x_, float y_, float z_);
	bool Move(float x_, float y_, float z_);


	/*
	//func of anime
	void Stand(int frames, GLuint* VAO, int size_VAO, GLuint& texture);
	void Walk(int frames, GLuint* VAO, int size_VAO, GLuint& texture);
	void Strike_Sword(int frames, GLuint* VAO, int size_VAO, GLuint& texture);
	void Injured(int frames, GLuint* VAO, int size_VAO, GLuint& texture);*/

	void Draw(GLFWwindow* window, Camera& camera);
};

