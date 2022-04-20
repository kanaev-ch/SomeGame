#pragma once
#include <iostream>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Person.h"
#include "Camera.h"
#include "Data.h"

class Control
{
public:
	//Coords of World Click
	float x, y, z;

	//Pointer for selected person
	Person* person_selected;

	Control();
	~Control();

	//Func save World coords of click
	void Click_Lmb(GLFWwindow* window, Camera& camera, std::vector<Person*>, size_t);

	//Func make active person with back light in shader
	void Mark_Active(std::vector<Person*>, size_t);

	//
	void Melee_Attack(GLFWwindow* window, std::vector<Person*> persons, size_t size_persons);

	//Func move person
	void Move();
};

