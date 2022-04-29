#include "Battle_Interface.h"



Battle_Interface::Battle_Interface(const char* vertexFile, const char* fragmentFile, const char* image_bg, 
								   const char* image_go, const char* image_go_act,
								   const char* image_attack, const char* image_attack_act)
{
	aspect = float(HEIGHT_SCREEN) / float(WIDTH_SCREEN);

	bg_scl = 0.1f;

	go_x_tr = 1.0f; go_y_tr = 1.0f; go_z_tr = 0; go_x_scl = 0.05f; go_y_scl = 0.05f; go_z_scl = 1.0f;

	atk_x_tr = 4.0f; atk_y_tr = 1.0f; atk_z_tr = 0; atk_x_scl = 0.05f; atk_y_scl = 0.05f; atk_z_scl = 1.0f;

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
	background->view = glm::scale(background->view, glm::vec3(1.0f, bg_scl * aspect, 1.0f));
	background->view = glm::translate(background->view, glm::vec3(0, 1.0f / bg_scl - 1.0f, 0));


	//Block of buttons, arguments of translate and scale very important, 
	//Buttons in Rect class automaticaly scale (_x_scl _y_scl) and move to top left corner
	//than it move to right and down by _x_tr _y_tr coords
	//AND ONLY after they compare with LKM coords
	go = new Rect(vertexFile, fragmentFile, image_go, aspect, go_x_tr, go_y_tr, go_z_tr, go_x_scl, go_y_scl, go_z_scl);
	go_act = new Rect(vertexFile, fragmentFile, image_go_act, aspect, go_x_tr, go_y_tr, go_z_tr, go_x_scl, go_y_scl, go_z_scl);

	attack = new Rect(vertexFile, fragmentFile, image_attack, aspect, atk_x_tr, atk_y_tr, atk_z_tr, atk_x_scl, atk_y_scl, atk_z_scl);
	attack_act = new Rect(vertexFile, fragmentFile, image_attack_act, aspect, atk_x_tr, atk_y_tr, atk_z_tr, atk_x_scl, atk_y_scl, atk_z_scl);
}

void Battle_Interface::Draw(GLFWwindow* window)
{
	if (!go_flag) go->Draw();
	else go_act->Draw();

	if (!atk_flag) attack->Draw();
	else attack_act->Draw();

	background->Draw();
/*
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && !go_flag && !atk_flag)//если нажата ЛКМ
	{
		double mouseX;
		double mouseY;
		glfwGetCursorPos(window, &mouseX, &mouseY);

		//Block compare coords of buttons with LKM coords
		//WIDTH_SCREEN * aspect * go->x_sc - is width of button by x
		//HEIGHT_SCREEN * go->y_sc - is height of button by y
		if ((mouseX >= (WIDTH_SCREEN * aspect * go->x_sc / 2) * go->x_tr && mouseX <= (WIDTH_SCREEN * aspect * go->x_sc / 2) * go->x_tr + (WIDTH_SCREEN * aspect * go->x_sc)) &&
			(mouseY >= (HEIGHT_SCREEN * go->y_sc / 2) * go->y_tr && mouseY <= (HEIGHT_SCREEN * go->y_sc / 2) * go->y_tr + (HEIGHT_SCREEN * go->y_sc)))
		{
			//ON go flag
			go_flag = true;
			std::cout << mouseX << " GO " << mouseY << std::endl;
		}

		if ((mouseX >= (WIDTH_SCREEN * aspect * attack->x_sc / 2) * attack->x_tr && mouseX <= (WIDTH_SCREEN * aspect * attack->x_sc / 2) * attack->x_tr + (WIDTH_SCREEN * aspect * attack->x_sc)) &&
			(mouseY >= (HEIGHT_SCREEN * attack->y_sc / 2) * attack->y_tr && mouseY <= (HEIGHT_SCREEN * attack->y_sc / 2) * attack->y_tr + (HEIGHT_SCREEN * attack->y_sc)))
		{
			atk_flag = true;
			std::cout << mouseX << " ATTACK " << mouseY << std::endl;
		}
	}*/
}

Battle_Interface::~Battle_Interface()
{
	delete background;
	delete go;
	delete go_act;
	delete attack;
	delete attack_act;
}
