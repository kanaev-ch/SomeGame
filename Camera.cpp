#include "Camera.h"

//Camera::Camera(int width_, int height_, glm::vec3 position, float FOVdeg, float nearPlane, float farPlane)
Camera::Camera(glm::vec3 position, float FOVdeg, float nearPlane, float farPlane)
{
	Position = position;

	projection = glm::perspective(glm::radians(FOVdeg), (float)(WIDTH_SCREEN) / float(HEIGHT_SCREEN), nearPlane, farPlane);//вычисл перспективу
}

//void Camera::Matrix(float FOVdeg, float nearPlane, float farPlane, GLuint& shaderProgram, const char* uniform)
void Camera::Matrix(GLuint& shaderProgram, const char* uniform)
{
	//Обязат иниц матрицы единичными значениями
	glm::mat4 view = glm::mat4(1.0f);
//	glm::mat4 projection = glm::mat4(1.0f);

	view = glm::lookAt(Position, Position + Orientation, Up);//ф-я загруж позицию куда хотим посмотреть, 1 - наша позиция,
		//2 - куда хотим посмотреть, тут работает сложение векторов и единичные вектора.
		//3 - вектор вверх, Orientation вектор всегда единичный и его исп как вектор на кот хотим посмотреть

	//calculate perspective, needs if size of screen changes
	projection = glm::perspective(glm::radians(45.0f), (float(WIDTH_SCREEN) / float(HEIGHT_SCREEN)), 0.1f, 100.0f);

	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, uniform), 1, GL_FALSE, glm::value_ptr(projection * view));//экспортируем матрицу в vertex shader ч/з uniform, матрицы перемноженные
}

void Camera::Inputs(GLFWwindow * window)
{
	//блок управления клавиш
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)//нажатие W
	{
		//Position += speed * Up;//двигаемся вперед
		Position += speed * past_time * Up;//двигаемся вперед
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)//нажатие A
	{
		//Position += speed * -glm::normalize(glm::cross(Orientation, Up));//двигаемся влево
		Position += speed * past_time * -glm::normalize(glm::cross(Orientation, Up));//двигаемся влево
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)//нажатие  S
	{
		//Position += speed * -Up;//двигаемся назад
		Position += speed * past_time * -Up;//двигаемся назад
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)//нажатие D
	{
		//Position += speed * glm::normalize(glm::cross(Orientation, Up));//двигаемся вправо
		Position += speed * past_time * glm::normalize(glm::cross(Orientation, Up));//двигаемся вправо
	}

	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)//нажатие R
	{
		//Position += speed * Orientation;//приближаемся
		Position += speed * past_time * Orientation;//приближаемся
	}
	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)//нажатие F
	{
		//Position += speed * -Orientation;//отдаляемся
		Position += speed * past_time * -Orientation;//отдаляемся
	}
/*	//блок управления клавиш
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)//нажатие W
	{
		Position += speed * Orientation;//двигаемся вперед
//		Position += speed * (Orientation * CameraMoveWS);//двигаемся вперед
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)//нажатие A
	{
		Position += speed * -glm::normalize(glm::cross(Orientation, Up));//двигаемся влево
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)//нажатие  S
	{
		Position += speed * -Orientation;//двигаемся назад
//		Position += speed * -(Orientation * CameraMoveWS);//двигаемся назад
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)//нажатие D
	{
		Position += speed * glm::normalize(glm::cross(Orientation, Up));//двигаемся вправо
	}

	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)//нажатие R
	{
		Position += speed * Orientation;//приближаемся
	}
	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)//нажатие F
	{
		Position += speed * -Orientation;//отдаляемся
	}

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)//нажатие SPACE
	{
		Position += speed * Up;//двигаемся вверх
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)//нажатие LCTRL
	{
		Position += speed * -Up;//двигаемся вниз
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)//нажатие LSHIFT
	{
		speed = 0.009f;//ускоряемся
	}
	else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)//отпускание LSHIFT 
	{
		speed = 0.005f;//обычная скорость
	}
	//конец блока управления клавиш

	//блок упавления обзора мышью
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)//если нажата ЛКМ
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);//скрываем курсор

		if (firstClick)//если ЛКМ нажата в первый раз (т.к. событие обрабатывается в цикле), переводим флаг и ставим курсор посередине экрана
		{
			glfwSetCursorPos(window, (width / 2), (height / 2));
			firstClick = false;
		}

		double mouseX;
		double mouseY;
		glfwGetCursorPos(window, &mouseX, &mouseY);//вычисл текущее положение курсора при нажатой ЛКМ

		//Вычисляем вектор поворота X и Y, т.к. координата начинается в верхнем левом углу, вычисляем из нее половину экрана, дальше делим на высоту или ширину (хз почему так!)
		//еще переводим их в градусы (хз как!)
		float rotX = sensitivity * (float)(mouseY - (height / 2)) / height;
		float rotY = sensitivity * (float)(mouseX - (width / 2)) / width;

		//вычисл коорд попорота по оси X, подъем головы вверх вниз
		glm::vec3 newOrientation = glm::rotate(Orientation, glm::radians(-rotX), glm::normalize(glm::cross(Orientation, Up)));

		//если родъем опускание в пределах 5-85 градусов
//		if (!((glm::angle(newOrientation, Up) <= glm::radians(5.0f)) or (glm::angle(newOrientation, -Up) <= glm::radians(5.0f))))
//		{
			Orientation = newOrientation;//поворачиваемся
//		}

		//просто поворачив по оси Y, влево-вправо
		Orientation = glm::rotate(Orientation, glm::radians(-rotY), Up);

		glfwSetCursorPos(window, (width / 2), (height / 2));//всегда устанавливаем мышь по центру экрана
	}
	else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)//отпускаем ЛКМ
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);//курсор появляется
		firstClick = true;//возвр флаг, чтобы камера не прыгала
	}*/
}