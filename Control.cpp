#include "Control.h"



Control::Control()
{
	x = y = z = 0;
	mouseX = mouseY = 0;
	person_selected = 0;

	//Create object of Battle_Interface
	battle_interface = new Battle_Interface ("Rect.vert", "Rect.frag", "Textures/Battle_Interface/background.png",
															 "Textures/Battle_Interface/go.png", "Textures/Battle_Interface/go_act.png",
															 "Textures/Battle_Interface/attack.png", "Textures/Battle_Interface/attack_act.png");

	chk_walk_rng = 0;
}


Control::~Control()
{
	delete battle_interface;
}

void Control::Draw_Interface(GLFWwindow* window)
{
	battle_interface->Draw(window);
}

void Control::Click_Lmb(GLFWwindow* window, Camera& camera, std::vector<Person*> persons, size_t size_persons)
{
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)//если нажата ЛКМ
	{
		glfwGetCursorPos(window, &mouseX, &mouseY);
		
		//block of calculate screen coords ortho Battle_Interface
		if (mouseY <= HEIGHT_SCREEN * battle_interface->bg_scl)
		{
			if (!battle_interface->go_flag && !battle_interface->atk_flag)
			{
				//std::cout << "Top" << std::endl;
				//glfwGetCursorPos(window, &mouseX, &mouseY);

				//Block compare coords of buttons with LKM coords
				//WIDTH_SCREEN * battle_interface->aspect * battle_interface->go->x_sc - is width of button by x
				//HEIGHT_SCREEN * battle_interface->go->y_sc - is height of button by y
				if ((mouseX >= (WIDTH_SCREEN * battle_interface->aspect * battle_interface->go->x_sc / 2) * battle_interface->go->x_tr && 
						mouseX <= (WIDTH_SCREEN * battle_interface->aspect * battle_interface->go->x_sc / 2) * battle_interface->go->x_tr + (WIDTH_SCREEN * battle_interface->aspect * battle_interface->go->x_sc)) &&
					(mouseY >= (HEIGHT_SCREEN * battle_interface->go->y_sc / 2) * battle_interface->go->y_tr && 
						mouseY <= (HEIGHT_SCREEN * battle_interface->go->y_sc / 2) * battle_interface->go->y_tr + (HEIGHT_SCREEN * battle_interface->go->y_sc)))
				{
					//ON go flag
					battle_interface->go_flag = true;
					//std::cout << mouseX << " GO " << mouseY << std::endl;
				}

				if ((mouseX >= (WIDTH_SCREEN * battle_interface->aspect * battle_interface->attack->x_sc / 2) * battle_interface->attack->x_tr && 
						mouseX <= (WIDTH_SCREEN * battle_interface->aspect * battle_interface->attack->x_sc / 2) * battle_interface->attack->x_tr + (WIDTH_SCREEN * battle_interface->aspect * battle_interface->attack->x_sc)) &&
					(mouseY >= (HEIGHT_SCREEN * battle_interface->attack->y_sc / 2) * battle_interface->attack->y_tr && 
						mouseY <= (HEIGHT_SCREEN * battle_interface->attack->y_sc / 2) * battle_interface->attack->y_tr + (HEIGHT_SCREEN * battle_interface->attack->y_sc)))
				{
					battle_interface->atk_flag = true;
					//std::cout << mouseX << " ATTACK " << mouseY << std::endl;
				}
			}
		}
		//block of calculate screen coords in world coords and save in to var x y z
		else if (mouseY > HEIGHT_SCREEN * battle_interface->bg_scl)
		{
			//std::cout << "Bottom" << std::endl;

			GLfloat _z;
			glReadPixels(int(mouseX), HEIGHT_SCREEN - int(mouseY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &_z);

			glm::mat4 view = glm::lookAt(camera.Position, camera.Position + camera.Orientation, camera.Up);

			glm::vec3 win = glm::unProject(glm::vec3(int(mouseX), HEIGHT_SCREEN - int(mouseY), _z), view, camera.projection, glm::vec4(0, 0, WIDTH_SCREEN, HEIGHT_SCREEN));
			//std::cout << win.x << " " << win.y << " " << win.z << std::endl;

			//Rounded data is here
			x = float(int(win.x + 0.5f)); y = float(int(win.y - 0.5f)); z = float(int(win.z + 0.9f));
			//std::cout << x << " " << y << " " << z << std::endl;

			//Unselect go button
			if (person_selected == 0 && battle_interface->go_flag)
				battle_interface->go_flag = false;

			//Unselect atk button
			if (person_selected == 0 && battle_interface->atk_flag)
				battle_interface->atk_flag = false;
		}
	}
}

void Control::Mouse_Over_Battle_Map(GLFWwindow* window, Camera& camera, Battle_Map & battle_map)
{
	float x, y, z;

	//Calculate width height of map by array
	int width_map = sizeof(battle_map.map_prototype) / sizeof(battle_map.map_prototype[0]);
	int height_map = sizeof(battle_map.map_prototype[0]) / sizeof(char);

	//Save cursor position
	glfwGetCursorPos(window, &mouseX, &mouseY);

	//If mouse lower interface pole of screen
	if (mouseY > HEIGHT_SCREEN * battle_interface->bg_scl)
	{
		//std::cout << "Bottom" << std::endl;

		GLfloat _z;
		glReadPixels(int(mouseX), HEIGHT_SCREEN - int(mouseY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &_z);

		glm::mat4 view = glm::lookAt(camera.Position, camera.Position + camera.Orientation, camera.Up);

		glm::vec3 win = glm::unProject(glm::vec3(int(mouseX), HEIGHT_SCREEN - int(mouseY), _z), view, camera.projection, glm::vec4(0, 0, WIDTH_SCREEN, HEIGHT_SCREEN));
		//std::cout << win.x << " " << win.y << " " << win.z << std::endl;

		//Rounded data is here
		x = float(int(win.x + 0.5f)); y = float(int(win.y - 0.5f)); z = float(int(win.z + 0.9f));

		//Check cursor over the map pole
		//if (x >= 0 && x <= 9 && y >= -9 && y <= 0)
		if (x >= 0 && x <= width_map - 1 && y >= -height_map - 1 && y <= 0)
		{
			//Clear bit after first draw tiles
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			//Change color of bit if mouse over it
			battle_map.map[int(-y)][int(x)]->Draw(camera, green);
			//std::cout << x << " - " << y << " - " << z << std::endl;
		}
	}
}

void Control::Mark_Active(std::vector<Person*> persons, size_t size_persons, GLFWwindow* window)
{
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)//если нажата ЛКМ
	{
		for (int i = 0; i < size_persons; i++)
		{
			//std::cout << x << " " << y << " " << z << std::endl;

			//save person object to pointer if coords are same
			if (persons[i]->x == x && persons[i]->y == y && person_selected != persons[i]) person_selected = persons[i];
			//unselect preson pointer if click coors are not same and Battle_Interface flag not active
			else if (persons[i]->x != x && persons[i]->y != y && person_selected != persons[i] && !battle_interface->go_flag) person_selected = 0;

			//Select or UnSelect person for backround color of person
			if (person_selected == persons[i]) persons[i]->selected = true;
			else persons[i]->selected = false;
		}
	}
}

void Control::Melee_Attack(GLFWwindow* window, std::vector<Person*> persons, size_t size_persons)
{
	
}

void Control::Move()
{
	//Move person if Battle_Interface flag active and person selected
	/*if (person_selected && battle_interface->go_flag)
	{
		//std::cout << x << " " << y << std::endl;
		//std::cout << map_prototype[0][9] << std::endl;
		//Check coords
		if (person_selected->x != x || person_selected->y != y)
		{
			//block for stay where person stand if coords to move larger then range
			//if (x - person_selected->x > person_selected->walk_range_x || x - person_selected->x < -person_selected->walk_range_x || 
			//	y - person_selected->y > person_selected->walk_range_y || y - person_selected->y < -person_selected->walk_range_y)
			//{
				//stay person where it stand
			//	x = person_selected->x;
			//	y = person_selected->y;
			//}

			//Move person
			if (!person_selected->Move(x, -y, z))
			{
				//Change anime to run
				person_selected->Change_Enum_Anime(1);
				
				std::cout << person_selected->x << std::endl;
			}
			//Stop person
			else
			{
				std::cout << person_selected->x << std::endl;

				//Change anime to stand
				person_selected->Change_Enum_Anime(0);
				//Unselect person for background color
				//person_selected->selected = false;
				//Clear pointer of selected person
				person_selected = 0;

				//OFF flag Battle_Interface
				battle_interface->go_flag = false;
				

				//std::cout << battle_interface->go_flag << std::endl;
			}
		}
	}*/

	//Move person if Battle_Interface flag active and person selected
	if (person_selected && battle_interface->go_flag)
	{
		//Move person
		if (!person_selected->Move(person_selected->step[chk_walk_rng].x, -person_selected->step[chk_walk_rng].y, person_selected->step[chk_walk_rng].z))
		{
			person_selected->Change_Enum_Anime(1);
		}
		else
		{
			//if end current step switch to next
			chk_walk_rng++;

			//end of walk
			if (chk_walk_rng == person_selected->walk_range)
			{
				person_selected->Change_Enum_Anime(0);

				person_selected = 0;

				battle_interface->go_flag = false;

				chk_walk_rng = 0;
			}
		}
	}
}