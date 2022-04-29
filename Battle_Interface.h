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
	float bg_scl;

	//Buttons block
	//Buttons in Rect class automaticaly scale (_x_scl) and move to top left corner
	//ONLY after that it compare with LKM coords
	//Button go
	Rect* go, * go_act; 
	//Flag of ON-OFF button
	bool go_flag;
	//Coords of button and scale coefficient
	float go_x_tr, go_y_tr, go_z_tr, go_x_scl, go_y_scl, go_z_scl;

	//Button attack
	Rect* attack, * attack_act; 
	//Flag of ON-OFF button
	bool atk_flag;
	//Coords of button and scale coefficient
	float atk_x_tr, atk_y_tr, atk_z_tr, atk_x_scl, atk_y_scl, atk_z_scl;

	void Draw(GLFWwindow* window);

	Battle_Interface(const char* vertexFile, const char* fragmentFile, const char*, const char*, const char*, const char*, const char*);
	~Battle_Interface();
};

