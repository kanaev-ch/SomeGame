#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <time.h>

#include "Global_Time.h"
//#include "Tile.h"
#include "Camera.h"
#include "Battle_Map.h"
#include "Person.h"
#include "Vampire.h"
#include "Warrior.h"
#include "Lizardman.h"
#include "Data.h"
//#include "Control.h"
//#include "Battle_Interface.h"
#include "Battle.h"

//Call back func for changing size of screen if it changes, glfw call it every time if screen changing
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	//new viewport
	glViewport(0, 0, width, height);

	//new zise of screen
	WIDTH_SCREEN = width;
	HEIGHT_SCREEN = height;
}


int main()
{
	//For randomize
	srand((unsigned)time(NULL)); rand(); rand();

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//windowed screen
	GLFWwindow* window = glfwCreateWindow(WIDTH_SCREEN, HEIGHT_SCREEN, "SomeGame", NULL, NULL);
	//Full screen
	//GLFWwindow* window = glfwCreateWindow(WIDTH_SCREEN, HEIGHT_SCREEN, "SomeGame", glfwGetPrimaryMonitor(), NULL);

	//if window can't create
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	//talking glfw cotext of our window is main
	glfwMakeContextCurrent(window);

	//Tell glfw what callback func must call when size of screen changing
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	
	//Load Glad
	gladLoadGL();

	//viewport screen
	glViewport(0, 0, WIDTH_SCREEN, HEIGHT_SCREEN);

	//Transparensy ON
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);


	std::vector <Person*> persons;
	persons.push_back(new Warrior("Person.vert", "Person.frag", "Textures/Persons/Warrior/warrior_stand_1.png", "Textures/Persons/Warrior/warrior_run_3.png",
		"Textures/Persons/Warrior/warrior_strike_sword_4.png", "Textures/Persons/Warrior/warrior_injured_2.png", "Textures/Persons/Warrior/warrior_defends_2.png",
		"Textures/Persons/Warrior/warrior_fall_3.png", "Textures/Persons/Warrior/warrior_dead_1.png", 8, 3, 0, 2, 2));
	/*persons.push_back(new Lizardman("Person.vert", "Person.frag", "Textures/Persons/Lizardman/Lizardman_stand_1.png", "Textures/Persons/Lizardman/Lizardman_run_3.png",
		"Textures/Persons/Lizardman/Lizardman_strike_sword_3.png", "Textures/Persons/Lizardman/Lizardman_injured_2.png", "Textures/Persons/Lizardman/Lizardman_defends_2.png",
		"Textures/Persons/Lizardman/Lizardman_fall_3.png", "Textures/Persons/Lizardman/Lizardman_dead_1.png", 5, 5, 0, 2, 3));*/
	persons.push_back(new Warrior("Person.vert", "Person.frag", "Textures/Persons/Warrior/warrior_stand_1.png", "Textures/Persons/Warrior/warrior_run_3.png",
		"Textures/Persons/Warrior/warrior_strike_sword_4.png", "Textures/Persons/Warrior/warrior_injured_2.png", "Textures/Persons/Warrior/warrior_defends_2.png",
		"Textures/Persons/Warrior/warrior_fall_3.png", "Textures/Persons/Warrior/warrior_dead_1.png", 8, 6, 0, 2, 2));
	//persons[0]->selected = true;
	//persons[1]->selected = true;
	//persons[2]->selected = true;
	//persons[0]->change_Direction(1);
	//persons[2]->change_Direction(1);

	Camera camera(glm::vec3(5.0f, -14.0f, 5.0f), 45.0f, 0.1f, 100.0f);

	Battle_Map battle_map;

	//Control control;

	Battle battle(persons);

	//Battle_Interface battle_interface("Rect.vert", "Rect.frag", "Textures/Battle_Interface/background.png", 
	//								  "Textures/Battle_Interface/go.png", "Textures/Battle_Interface/go_act.png", 
	//								  "Textures/Battle_Interface/attack.png", "Textures/Battle_Interface/attack_act.png");
	
	//double time = 0;

	glEnable(GL_DEPTH_TEST);


	while (!glfwWindowShouldClose(window))//основной цикл говорит что пока окно glfw не закроется или др ф-я не скажет ему закрыться
	{
		//Timer
		last_time = glfwGetTime();

		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		camera.Inputs(window);

		//First draw of All scene
		battle_map.Draw(camera, rgb);
		for (int i = 0; i < persons.size(); i++)
			persons[i]->Draw(window, camera);
		battle.Draw_Interface(window);

		//Read and save all coords into variables
		battle.Mouse_Over_Battle_Map(window, camera, battle_map);
		battle.Click_Lmb_on_Top_interface(window, camera, persons);
		battle.Click_Lmb_on_Main_Screen(window, camera, persons);
		//battle.Click_Lmb(window, camera, persons, persons.size());
		battle.Save_Walk_Coords_to_Arr(window, camera, battle_map, persons);

		//Clear all scene
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		//battle.Mark_Active(persons, persons.size(), window);
		//battle.Mark_Active_By_Person(persons);
		battle.Switch_to_Next_Step_Person(persons);
		battle.Switch_to_Next_Person(persons);
		//battle.Switch_to_Next_Phase(persons);
		//battle.UnMark_Active(window);
		battle.Draw_Person_Way_Walk(camera, battle_map, persons);
		battle.Draw_Mouse_Over_Tile(camera, battle_map, green);
		battle.Draw_Walk_Area(camera, battle_map, persons);
		battle.Melee_Attack(window, persons);

		battle.Move(persons, window);

		battle.Skipping_Step(window);

		//Second draw ALL scene
		battle_map.Draw(camera, rgb);
		for (int i = 0; i < persons.size(); i++)
			persons[i]->Draw(window, camera);
		//persons[1]->Draw(window, camera);
		battle.Draw_Interface(window);

		glfwSwapBuffers(window);

		glfwPollEvents();




		//Temporary exit
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			break;
		}

		//Timer
		current_time = glfwGetTime();
		//Time of cycle and past from beginning of program, for changing frames of animation
		global_time += current_time - last_time;
		past_time = float(current_time - last_time) * 400;
		//std::cout << past_time << std::endl;
	}

	glDisable(GL_BLEND);

	for (int i = 0; i < persons.size(); i++)
		delete persons[i];

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}