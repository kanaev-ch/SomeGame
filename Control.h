#pragma once
#include <iostream>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Person.h"
#include "Camera.h"
#include "Data.h"
#include "Battle_Interface.h"
#include "Battle_Map.h"

class Control
{
public:
	//Coords of World Click
	float x, y, z;

	double mouseX;
	double mouseY;

	//Pointer for selected person
	Person* person_selected;

	//Object of Battle_Interface
	Battle_Interface * battle_interface;

	//Temp var to switch steps in array of move Step* step
	int chk_walk_rng;

	Control();
	~Control();

	void Draw_Interface(GLFWwindow* window);

	//Func save World coords of click
	void Click_Lmb(GLFWwindow* window, Camera& camera, std::vector<Person*>, size_t);

	//Func for change color of tile if mouse over it. It works y double draw of map tile and clear color bits between draw
	void Mouse_Over_Battle_Map(GLFWwindow* window, Camera& camera, Battle_Map &);

	//Func make active person with back light in shader
	void Mark_Active(std::vector<Person*>, size_t, GLFWwindow* window);

	//
	void Melee_Attack(GLFWwindow* window, std::vector<Person*> persons, size_t size_persons);

	//Func move person
	void Move();
};

