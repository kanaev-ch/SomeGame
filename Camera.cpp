#include "Camera.h"

//Camera::Camera(int width_, int height_, glm::vec3 position, float FOVdeg, float nearPlane, float farPlane)
Camera::Camera(glm::vec3 position, float FOVdeg, float nearPlane, float farPlane)
{
	Position = position;

	projection = glm::perspective(glm::radians(FOVdeg), (float)(WIDTH_SCREEN) / float(HEIGHT_SCREEN), nearPlane, farPlane);//������ �����������
}

//void Camera::Matrix(float FOVdeg, float nearPlane, float farPlane, GLuint& shaderProgram, const char* uniform)
void Camera::Matrix(GLuint& shaderProgram, const char* uniform)
{
	//������ ���� ������� ���������� ����������
	glm::mat4 view = glm::mat4(1.0f);
//	glm::mat4 projection = glm::mat4(1.0f);

	view = glm::lookAt(Position, Position + Orientation, Up);//�-� ������ ������� ���� ����� ����������, 1 - ���� �������,
		//2 - ���� ����� ����������, ��� �������� �������� �������� � ��������� �������.
		//3 - ������ �����, Orientation ������ ������ ��������� � ��� ��� ��� ������ �� ��� ����� ����������

	//calculate perspective, needs if size of screen changes
	projection = glm::perspective(glm::radians(45.0f), (float(WIDTH_SCREEN) / float(HEIGHT_SCREEN)), 0.1f, 100.0f);

	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, uniform), 1, GL_FALSE, glm::value_ptr(projection * view));//������������ ������� � vertex shader �/� uniform, ������� �������������
}

void Camera::Inputs(GLFWwindow * window)
{
	//���� ���������� ������
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)//������� W
	{
		//Position += speed * Up;//��������� ������
		Position += speed * past_time * Up;//��������� ������
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)//������� A
	{
		//Position += speed * -glm::normalize(glm::cross(Orientation, Up));//��������� �����
		Position += speed * past_time * -glm::normalize(glm::cross(Orientation, Up));//��������� �����
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)//�������  S
	{
		//Position += speed * -Up;//��������� �����
		Position += speed * past_time * -Up;//��������� �����
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)//������� D
	{
		//Position += speed * glm::normalize(glm::cross(Orientation, Up));//��������� ������
		Position += speed * past_time * glm::normalize(glm::cross(Orientation, Up));//��������� ������
	}

	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)//������� R
	{
		//Position += speed * Orientation;//������������
		Position += speed * past_time * Orientation;//������������
	}
	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)//������� F
	{
		//Position += speed * -Orientation;//����������
		Position += speed * past_time * -Orientation;//����������
	}
/*	//���� ���������� ������
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)//������� W
	{
		Position += speed * Orientation;//��������� ������
//		Position += speed * (Orientation * CameraMoveWS);//��������� ������
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)//������� A
	{
		Position += speed * -glm::normalize(glm::cross(Orientation, Up));//��������� �����
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)//�������  S
	{
		Position += speed * -Orientation;//��������� �����
//		Position += speed * -(Orientation * CameraMoveWS);//��������� �����
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)//������� D
	{
		Position += speed * glm::normalize(glm::cross(Orientation, Up));//��������� ������
	}

	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)//������� R
	{
		Position += speed * Orientation;//������������
	}
	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)//������� F
	{
		Position += speed * -Orientation;//����������
	}

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)//������� SPACE
	{
		Position += speed * Up;//��������� �����
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)//������� LCTRL
	{
		Position += speed * -Up;//��������� ����
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)//������� LSHIFT
	{
		speed = 0.009f;//����������
	}
	else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)//���������� LSHIFT 
	{
		speed = 0.005f;//������� ��������
	}
	//����� ����� ���������� ������

	//���� ��������� ������ �����
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)//���� ������ ���
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);//�������� ������

		if (firstClick)//���� ��� ������ � ������ ��� (�.�. ������� �������������� � �����), ��������� ���� � ������ ������ ���������� ������
		{
			glfwSetCursorPos(window, (width / 2), (height / 2));
			firstClick = false;
		}

		double mouseX;
		double mouseY;
		glfwGetCursorPos(window, &mouseX, &mouseY);//������ ������� ��������� ������� ��� ������� ���

		//��������� ������ �������� X � Y, �.�. ���������� ���������� � ������� ����� ����, ��������� �� ��� �������� ������, ������ ����� �� ������ ��� ������ (�� ������ ���!)
		//��� ��������� �� � ������� (�� ���!)
		float rotX = sensitivity * (float)(mouseY - (height / 2)) / height;
		float rotY = sensitivity * (float)(mouseX - (width / 2)) / width;

		//������ ����� �������� �� ��� X, ������ ������ ����� ����
		glm::vec3 newOrientation = glm::rotate(Orientation, glm::radians(-rotX), glm::normalize(glm::cross(Orientation, Up)));

		//���� ������ ��������� � �������� 5-85 ��������
//		if (!((glm::angle(newOrientation, Up) <= glm::radians(5.0f)) or (glm::angle(newOrientation, -Up) <= glm::radians(5.0f))))
//		{
			Orientation = newOrientation;//��������������
//		}

		//������ ��������� �� ��� Y, �����-������
		Orientation = glm::rotate(Orientation, glm::radians(-rotY), Up);

		glfwSetCursorPos(window, (width / 2), (height / 2));//������ ������������� ���� �� ������ ������
	}
	else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)//��������� ���
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);//������ ����������
		firstClick = true;//����� ����, ����� ������ �� �������
	}*/
}