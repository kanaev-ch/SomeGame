#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

//#include "Tile.h"
#include "Data.h"

class Camera
{
public:
	//главные 3 вектора
	glm::vec3 Position;//“екущие координаты
	glm::vec3 Orientation = glm::vec3(0.0f, 1.0f, -0.5f);//вектор ориентации, куда хотим посмотреть, он всегда единичный, в итоге вектор вычисл€етс€ сложением текущей координаты и данного вектора.
	//glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);//вектор ориентации, куда хотим посмотреть, он всегда единичный, в итоге вектор вычисл€етс€ сложением текущей координаты и данного вектора.
	glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);//вектор направленный вверх, тоже единичный, нужен дл€ ф-ии glm::lookAt

	//Projection Matrix
	glm::mat4 projection = glm::mat4(1.0f);

	glm::vec3 CameraMoveWS = Orientation;

	bool firstClick = true;

	//Ўирина высота экрана
	//int width;
	//int height;

	float speed = 0.005f;//коэф скорости перемещени€ камеры
	float sensitivity = 100.0f;//коэф чувствительности поворота

	//Camera(int width_, int height_, glm::vec3 position, float FOVdeg, float nearPlane, float farPlane);//конструктор объекта камера
	Camera(glm::vec3 position, float FOVdeg, float nearPlane, float farPlane);//конструктор объекта камера

	//ф-€ вычисл€ет вектор куда смотрим и загружает его матрицу в vertex shader ч\з uniform:
		//1 - угол обзора, 2-3 - ближн€€ и дальн€€ обрезка, 4 - шейдер, 5 - юниформа
	void Matrix(GLuint & shaderProgram, const char* uniform);

	//ф-€ вычисл€ет координаты в зависимости от нажати€ органов управлени€, клава-мышь
	void Inputs(GLFWwindow * window);
};

#endif

