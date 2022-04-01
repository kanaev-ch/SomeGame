#pragma once
#include "Person.h"
class Vampire :
	public Person
{
public:
	//textures
	GLuint texture;
	GLuint texture2;

	Vampire(const char* vertexFile, const char* fragmentFile, const char* image, const char* image2, float x_, float y_, float z_, float sprite_h_);
	~Vampire();

	void Draw(Camera& camera, float time_);
};

