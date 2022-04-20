#pragma once
#include "Rect.h"
#include "Data.h"

class Battle_Interface
{
public:
	//Var of float(HEIGHT_SCREEN) / float(WIDTH_SCREEN)
	float aspect;

	//Objects of Battle interface
	Rect * background;

	Rect* go; Rect* go_act; bool go_flag;

	Rect* attack; Rect* attack_act; bool atk_flag;

	void Draw(GLFWwindow* window);

	Battle_Interface(const char* vertexFile, const char* fragmentFile, const char*, const char*, const char*, const char*, const char*);
	~Battle_Interface();
};

