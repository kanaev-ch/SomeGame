#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Tile.h"
#include "Camera.h"
#include "Battle_Map.h"
#include "Person.h"
#include "Vampire.h"

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

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

//	Person person("Tile.vert", "Tile.frag", "Textures/Vampire_stand_8.png", 5, 9 * (-1), 0, 2);
//	Person person("Tile.vert", "Tile.frag", "Textures/Vampire_walk.png", 5, 9 * (-1), 0, 2);
//	person.change_Height_Sprite(3.0f);
	Vampire vampire("Tile.vert", "Tile.frag", "Textures/Vampire_stand_8.png", "Textures/Vampire_walk.png", 5, 9 * (-1), 0, 2);
//	vampire.change_Height_Sprite(3.0f);
	vampire.change_Direction(0);

	Camera camera(width, height, glm::vec3(4.0f, -15.0f, 5.0f));

	Battle_Map battle_map(width, height);
	
	float time = 0;

	glEnable(GL_DEPTH_TEST);

	while (!glfwWindowShouldClose(window))//�������� ���� ������� ��� ���� ���� glfw �� ��������� ��� �� �-� �� ������ ��� ���������
	{

		time = float(glfwGetTime());

		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		

		camera.Inputs(window);

//		tile.Draw(camera);
//		tile1.Draw(camera);

		battle_map.Draw(camera);
//		person.Draw(camera, time);
		vampire.Draw(camera, time);

		glfwSwapBuffers(window);

		glfwPollEvents();

	}

	glDisable(GL_BLEND);

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}