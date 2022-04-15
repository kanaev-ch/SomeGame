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
	float x, y, z;

	Person* person_selected;

	Control();
	~Control();

	void Click_Lmb(GLFWwindow* window, Camera& camera, std::vector<Person*>, size_t);

	void Mark_Active(std::vector<Person*>, size_t);

	void Melee_Attack(GLFWwindow* window, std::vector<Person*> persons, size_t size_persons);

	void Move();
};

