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
	//Coords of World Left Mouse Click
	float x, y, z;

	//Coords of world Mouse Over
	float x_over, y_over, z_over;

	double mouseX;
	double mouseY;

	//Pointer for selected person
	Person* person_selected;

	//Object of Battle_Interface
	Battle_Interface * battle_interface;

	//Counter var to switch steps in array of move Step* step
	int chk_walk_rng;

	Control();
	~Control();

	//Func draw ortho interface
	void Draw_Interface(GLFWwindow* window);

	//Func save World coords of click
	//void Click_Lmb(GLFWwindow* window, Camera& camera, std::vector<Person*>&, size_t);

	//Func for save mouse over coords
	void Mouse_Over_Battle_Map(GLFWwindow* window, Camera& camera, Battle_Map &);

	//Func make active person with back light in shader
	//void Mark_Active(std::vector<Person*>, size_t, GLFWwindow* window);
	
	
	//void Mark_Active_By_Person(std::vector<Person*>&, size_t);

	//Func clear Pointer Person* person_selected;
	void Clear_Person_Selected();

	//Func of unmark active-selected person
	void UnMark_Active(GLFWwindow* window);

	//Func draw walk range tiles around active person
	void Draw_Walk_Area(Camera& camera, Battle_Map &, std::vector <Person*>& persons);

	//Func of save mouse over coords to person walk-way array
	void Save_Walk_Coords_to_Arr(GLFWwindow* window, Camera& camera, Battle_Map&, std::vector <Person*>& persons);

	//Func draw tile under mouse when mouse over it
	void Draw_Mouse_Over_Tile(Camera& camera, Battle_Map& battle_map, CLR clr)const;

	//Func draw tile of person array way direction
	void Draw_Person_Way_Walk(Camera& camera, Battle_Map& battle_map, std::vector <Person*>& persons)const;

	//
	//void Melee_Attack(GLFWwindow* window, std::vector<Person*> persons, size_t size_persons);

	//Func move person
	//void Move();
};

