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
	//������� 3 �������
	glm::vec3 Position;//������� ����������
	glm::vec3 Orientation = glm::vec3(0.0f, 1.0f, -0.5f);//������ ����������, ���� ����� ����������, �� ������ ���������, � ����� ������ ����������� ��������� ������� ���������� � ������� �������.
	//glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);//������ ����������, ���� ����� ����������, �� ������ ���������, � ����� ������ ����������� ��������� ������� ���������� � ������� �������.
	glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);//������ ������������ �����, ���� ���������, ����� ��� �-�� glm::lookAt

	//Projection Matrix
	glm::mat4 projection = glm::mat4(1.0f);

	glm::vec3 CameraMoveWS = Orientation;

	bool firstClick = true;

	//������ ������ ������
	//int width;
	//int height;

	float speed = 0.005f;//���� �������� ����������� ������
	float sensitivity = 100.0f;//���� ���������������� ��������

	//Camera(int width_, int height_, glm::vec3 position, float FOVdeg, float nearPlane, float farPlane);//����������� ������� ������
	Camera(glm::vec3 position, float FOVdeg, float nearPlane, float farPlane);//����������� ������� ������

	//�-� ��������� ������ ���� ������� � ��������� ��� ������� � vertex shader �\� uniform:
		//1 - ���� ������, 2-3 - ������� � ������� �������, 4 - ������, 5 - ��������
	void Matrix(GLuint & shaderProgram, const char* uniform);

	//�-� ��������� ���������� � ����������� �� ������� ������� ����������, �����-����
	void Inputs(GLFWwindow * window);
};

#endif

