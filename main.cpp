#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>

#include "Global_Time.h"
#include "Tile.h"
#include "Camera.h"
#include "Battle_Map.h"
#include "Person.h"
#include "Vampire.h"
#include "Warrior.h"
#include "Lizardman.h"

int width = 1700;
int height = 800;

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow* window = glfwCreateWindow(width, height, "SomeGame", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	gladLoadGL();
	glViewport(0, 0, width, height);

//	Tile tile("Tile.vert", "Tile.frag", "Textures/fire_floor.png", 0, 0, 0);
//	Tile tile1("Tile.vert", "Tile.frag", "Textures/pop_cat.png", 1, 0, 0);

	//Transparensy ON
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

//	Person person("Tile.vert", "Tile.frag", "Textures/Vampire_stand_8.png", 5, 9 * (-1), 0, 2);
//	Person person("Tile.vert", "Tile.frag", "Textures/Vampire_walk.png", 5, 9 * (-1), 0, 2);
//	person.change_Height_Sprite(3.0f);
	//Vampire vampire("Tile.vert", "Tile.frag", "Textures/Vampire_walk_6.png", "Textures/Vampire_stand_10.png", 5, 9, 0, 2);
	//Vampire vampire("Tile.vert", "Tile.frag", "Textures/warrior_stand_2.png", "Textures/warrior_run_6.png", "Textures/warrior_strike_sword_5.png", 
		//"Textures/warrior_injured_2.png", "Textures/warrior_defends_4.png", "Textures/warrior_fall_3.png", "Textures/warrior_dead_1.png", 5, 9, 0, 2);
/*	Warrior warrior("Person.vert", "Person.frag", "Textures/Persons/Warrior/warrior_stand_1.png", "Textures/Persons/Warrior/warrior_run_3.png", 
		"Textures/Persons/Warrior/warrior_strike_sword_4.png", "Textures/Persons/Warrior/warrior_injured_2.png", "Textures/Persons/Warrior/warrior_defends_2.png", 
		"Textures/Persons/Warrior/warrior_fall_3.png", "Textures/Persons/Warrior/warrior_dead_1.png", 5, 9, 0, 2);
	Lizardman lizardman("Person.vert", "Person.frag", "Textures/Persons/Lizardman/Lizardman_stand_1.png", "Textures/Persons/Lizardman/Lizardman_run_3.png", 
		"Textures/Persons/Lizardman/Lizardman_strike_sword_3.png", "Textures/Persons/Lizardman/Lizardman_injured_2.png", "Textures/Persons/Lizardman/Lizardman_defends_2.png", 
		"Textures/Persons/Lizardman/Lizardman_fall_3.png", "Textures/Persons/Lizardman/Lizardman_dead_1.png", 3, 6, 0, 2);
//	vampire.change_Height_Sprite(3.0f);
	//vampire.change_Direction(1);
	warrior.change_Direction(1);*/

	std::vector <Person*> persons;
	persons.push_back(new Warrior("Person.vert", "Person.frag", "Textures/Persons/Warrior/warrior_stand_1.png", "Textures/Persons/Warrior/warrior_run_3.png",
		"Textures/Persons/Warrior/warrior_strike_sword_4.png", "Textures/Persons/Warrior/warrior_injured_2.png", "Textures/Persons/Warrior/warrior_defends_2.png",
		"Textures/Persons/Warrior/warrior_fall_3.png", "Textures/Persons/Warrior/warrior_dead_1.png", 5, 9, 0, 2));
	persons.push_back(new Lizardman("Person.vert", "Person.frag", "Textures/Persons/Lizardman/Lizardman_stand_1.png", "Textures/Persons/Lizardman/Lizardman_run_3.png",
		"Textures/Persons/Lizardman/Lizardman_strike_sword_3.png", "Textures/Persons/Lizardman/Lizardman_injured_2.png", "Textures/Persons/Lizardman/Lizardman_defends_2.png",
		"Textures/Persons/Lizardman/Lizardman_fall_3.png", "Textures/Persons/Lizardman/Lizardman_dead_1.png", 5, 7, 0, 2));
	persons[0]->change_Direction(1);

	//Camera camera(width, height, glm::vec3(4.0f, -15.0f, 5.0f));
	Camera camera(width, height, glm::vec3(4.0f, -15.0f, 5.0f), 45.0f, 0.1f, 100.0f);

	Battle_Map battle_map(width, height);
	
	//double time = 0;

	glEnable(GL_DEPTH_TEST);



	//uniform ON or OFF color or texture of object
	//GLuint tex_or_clr = glGetUniformLocation(vampire.shaderProgram, "tex_or_clr");
	//glUseProgram(vampire.shaderProgram);
	//glUniform1i(tex_or_clr, 1);

	while (!glfwWindowShouldClose(window))//�������� ���� ������� ��� ���� ���� glfw �� ��������� ��� �� �-� �� ������ ��� ���������
	{
		//Timer
		last_time = glfwGetTime();

		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		camera.Inputs(window);

//		tile.Draw(camera);
//		tile1.Draw(camera);

		battle_map.Draw(camera);
//		person.Draw(camera, time);

		//vampire.Move(7, 4, 0);
		//vampire.Draw(window, camera);
		//warrior.Draw(window, camera);
		//lizardman.Draw(window, camera);
		persons[0]->Draw(window, camera);
		persons[1]->Draw(window, camera);

		//block of calculate screen coords in world coords
		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)//���� ������ ���
		{
			double mouseX;
			double mouseY;
			glfwGetCursorPos(window, &mouseX, &mouseY);
			//std::cout << int(mouseX) << " - " << int(mouseY) << std::endl;

			GLfloat z;
			glReadPixels(int(mouseX), height - int(mouseY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &z);

			glm::mat4 view = glm::lookAt(camera.Position, camera.Position + camera.Orientation, camera.Up);

			glm::vec3 win = glm::unProject(glm::vec3(int(mouseX), height - int(mouseY), z), view, camera.projection, glm::vec4(0, 0, width, height));
			std::cout << int(win.x + 0.5f) << " " << int((win.y - 0.5f) * -1.0f) << " " << int(win.z + 0.9f) << std::endl;
		}

		glfwSwapBuffers(window);

		glfwPollEvents();

		//Timer
		current_time = glfwGetTime();
		global_time += current_time - last_time;
	}

	glDisable(GL_BLEND);

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}