#include "Battle_Interface.h"



Battle_Interface::Battle_Interface(const char* vertexFile, const char* fragmentFile, const char* image_bg, 
								   const char* image_go, const char* image_go_act,
								   const char* image_attack, const char* image_attack_act)
{
	aspect = float(HEIGHT_SCREEN) / float(WIDTH_SCREEN);

	GLfloat vertices_bg[32] =
	{	//	COORDINATES		/		COLORS					//	Texture coordinates
		-1.0f, -1.0f,  0.0f,		0.8f, 0.8f, 0.8f,		 0.0f, 0.0f,
		-1.0f,  1.0f,  0.0f,		0.8f, 0.8f, 0.8f,		 0.0f, 1.0f,
		 1.0f,  1.0f,  0.0f,		0.8f, 0.8f, 0.8f,		10.0f, 1.0f,
		 1.0f, -1.0f,  0.0f,		0.8f, 0.8f, 0.8f,		10.0f, 0.0f,
	};

	go_flag = atk_flag = false;

	//apply background menu picture
	background = new Rect (vertexFile, fragmentFile, image_bg, aspect, 0, 0, 0, 1.0f, 1.0f, 1.0f, vertices_bg, sizeof(vertices_bg) / sizeof(float));
	background->view = glm::ortho(-1., 1., -1. * aspect, 1. * aspect, .1, 100.);
	background->view = glm::translate(background->view, glm::vec3(0, 0, -1));
	background->view = glm::scale(background->view, glm::vec3(1.0f, 0.1f * aspect, 1.0f));
	background->view = glm::translate(background->view, glm::vec3(0, 9, 0));


	//Block of buttons, arguments of translate and scale very important, 
	go = new Rect(vertexFile, fragmentFile, image_go, aspect, 1, 1, 0, 0.05f, 0.05f, 1.0f);
	//go->view = glm::ortho(-1., 1., -1. * aspect, 1. * aspect, .1, 100.);
	//go->view = glm::translate(go->view, glm::vec3(0, 0, -1));
	//go->view = glm::scale(go->view, glm::vec3(0.1f * aspect, 0.1f * aspect, 1.0f));
	//go->view = glm::translate(go->view, glm::vec3(-9 / aspect, 9, 0));
	go_act = new Rect(vertexFile, fragmentFile, image_go_act, aspect, 1, 1, 0, 0.05f, 0.05f, 1.0f);

	attack = new Rect(vertexFile, fragmentFile, image_attack, aspect, 4, 1, 0, 0.05f, 0.05f, 1.0f);
	//go1->view = glm::ortho(-1., 1., -1. * aspect, 1. * aspect, .1, 100.);
	//go1->view = glm::translate(go1->view, glm::vec3(0, 0, -1));
	//go1->view = glm::scale(go1->view, glm::vec3(0.1f * aspect, 0.1f * aspect, 1.0f));
	//go1->view = glm::translate(go1->view, glm::vec3(0 / aspect, 9, 0));
	attack_act = new Rect(vertexFile, fragmentFile, image_attack_act, aspect, 4, 1, 0, 0.05f, 0.05f, 1.0f);
}

void Battle_Interface::Draw(GLFWwindow* window)
{
	if (!go_flag) go->Draw();
	else go_act->Draw();

	if (!atk_flag) attack->Draw();
	else attack_act->Draw();

	background->Draw();

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)//если нажата ЛКМ
	{
		double mouseX;
		double mouseY;
		glfwGetCursorPos(window, &mouseX, &mouseY);
	
		if ((mouseX >= (WIDTH_SCREEN * aspect * go->x_sc / 2) * go->x_tr && mouseX <= (WIDTH_SCREEN * aspect * go->x_sc / 2) * go->x_tr + (WIDTH_SCREEN * aspect * go->x_sc)) &&
			(mouseY >= (HEIGHT_SCREEN * go->y_sc / 2) * go->y_tr && mouseY <= (HEIGHT_SCREEN * go->y_sc / 2) * go->y_tr + (HEIGHT_SCREEN * go->y_sc)))
			std::cout << mouseX << " GO " << mouseY << std::endl;

		if ((mouseX >= (WIDTH_SCREEN * aspect * attack->x_sc / 2) * attack->x_tr && mouseX <= (WIDTH_SCREEN * aspect * attack->x_sc / 2) * attack->x_tr + (WIDTH_SCREEN * aspect * attack->x_sc)) &&
			(mouseY >= (HEIGHT_SCREEN * attack->y_sc / 2) * attack->y_tr && mouseY <= (HEIGHT_SCREEN * attack->y_sc / 2) * attack->y_tr + (HEIGHT_SCREEN * attack->y_sc)))
			std::cout << mouseX << " ATTACK " << mouseY << std::endl;
		//if ( (mouseX >= (WIDTH_SCREEN * aspect * 0.05f / 2) * 25 && mouseX <= (WIDTH_SCREEN * aspect * 0.05f / 2) * 25 + (WIDTH_SCREEN * aspect * 0.05f)) &&
			 //(mouseY >= (HEIGHT_SCREEN * 0.05f / 2) * 25 && mouseY <= (HEIGHT_SCREEN * 0.05f / 2) * 25 + (HEIGHT_SCREEN * 0.05f)) )
			//std::cout << mouseX << " - " << mouseY << std::endl;
	}
}

Battle_Interface::~Battle_Interface()
{
	delete background;
	delete go;
	delete go_act;
	delete attack;
	delete attack_act;
}
