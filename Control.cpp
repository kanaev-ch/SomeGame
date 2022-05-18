#include "Control.h"



Control::Control()
{
	x = y = z = 0;
	mouseX = mouseY = 0;
	person_selected = 0;
	x_over = y_over = z_over = 0;

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
	//float x, y, z;

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
		x_over = float(int(win.x + 0.5f)); y_over = float(int(win.y - 0.5f)); z_over = float(int(win.z + 0.9f));
	}
}

void Control::Draw_Mouse_Over_Tile(Camera& camera, Battle_Map& battle_map, CLR clr)const
{
	//Check tile is in map area
	if (x_over >= 0 && x_over <= battle_map.map_w - 1 && y_over >= -(battle_map.map_h - 1) && y_over <= 0)
		{
			//Draw tile under mouse
			battle_map.map[int(-y_over)][int(x_over)]->Draw(camera, clr);
			//std::cout << x << " - " << y << " - " << z << std::endl;
		}
}

void Control::Mark_Active(std::vector<Person*> persons, size_t size_persons, GLFWwindow* window)
{
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)//если нажата ЛКМ
	{
		for (int i = 0; i < size_persons; i++)
		{
			//save person object to pointer if coords are same
			if (persons[i]->x == x && persons[i]->y == y && person_selected != persons[i])
			{

				//Block of clear last person if there was selected person allready
				if (person_selected)
				{
					//clear array trajectory of move
					for (int i = 0; i < person_selected->walk_range; i++)
					{
						person_selected->step[i].x = -1;
						person_selected->step[i].y = 1;
					}

					//change anime to stand
					person_selected->Change_Enum_Anime(0);

					//Stop person
					person_selected->walk_flag = false;

					//Unselect person
					person_selected->selected = false;

					//clear pointer of selected person
					person_selected = 0;

					//unset go button in interface
					battle_interface->go_flag = false;

					//reset counter of steps
					chk_walk_rng = 0;
				}

				//Select new person
				person_selected = persons[i];
				//std::cout << persons[i] << " " << person_selected << std::endl;
			}
			//unselect preson pointer if click coors are not same and Battle_Interface flag not active
			//else if (persons[i]->x != x && persons[i]->y != y && person_selected != persons[i] && !battle_interface->go_flag) person_selected = 0;

			//Select or UnSelect person for backround color of person
			if (person_selected == persons[i]) persons[i]->selected = true;
			else persons[i]->selected = false;
		}
	}
}

void Control::UnMark_Active(GLFWwindow* window)
{
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS && person_selected)//если нажата ПКМ
	{
		//clear active person by RMB
		person_selected->selected = false;
		person_selected = 0;
	}
}

void Control::Draw_Walk_Area(Camera& camera, Battle_Map& battle_map, std::vector <Person*> persons, size_t size_persons)
{
	//if person active and not moving
	if (person_selected && !person_selected->walk_flag)
	{
		//cycle draw selected range tiles of active person
		for (int i = -person_selected->walk_range; i <= person_selected->walk_range; i++)
			for (int j = -person_selected->walk_range; j <= person_selected->walk_range; j++)
			{
				//check the tile position in map
				if (person_selected->x + i >= 0 && person_selected->x + i <= battle_map.map_w - 1 && person_selected->y - j >= -(battle_map.map_h - 1) && person_selected->y - j <= 0)
					//Not draw unwalk tiles
					if (battle_map.No_Way_Object(person_selected->x + i, -person_selected->y + j, persons, size_persons))
						//Draw selected range tiles
						battle_map.map[int(-person_selected->y + j)][int(person_selected->x + i)]->Draw(camera, red);
			}
	}
}

void Control::Draw_Person_Way_Walk(Camera& camera, Battle_Map& battle_map, std::vector <Person*> persons, size_t size_persons)const
{
	if (person_selected)
	{
		for (int i = 0; i < person_selected->walk_range; i++)
			//Check tile is in map area
			if (person_selected->step[i].x >= 0 && person_selected->step[i].x <= battle_map.map_w - 1 && 
				person_selected->step[i].y >= -(battle_map.map_h - 1) && person_selected->step[i].y <= 0)
				//Not draw unwalk tiles
				if (battle_map.No_Way_Object(person_selected->step[i].x, -person_selected->step[i].y, persons, size_persons))
					//Draw way tile
					battle_map.map[int(-person_selected->step[i].y)][int(person_selected->step[i].x)]->Draw(camera, blue);
	}
}

void Control::Save_Walk_Coords_to_Arr(GLFWwindow* window, Camera& camera, Battle_Map& battle_map, std::vector <Person*> persons, size_t size_persons)
{
	//If person selected, GO button off, and he is not move
	if (person_selected && battle_interface->go_flag && !person_selected->walk_flag)
	{
		//Select by walk range of person
		switch (person_selected->walk_range)
		{
		//Block for persons with 2 steps
		case 2: {
			//Block of chek nearest to person tile
			if (x_over >= person_selected->x - 1 && x_over <= person_selected->x + 1 &&
				y_over >= person_selected->y - 1 && y_over <= person_selected->y + 1)
			{
				//Don't save way tile to arr AND don't RMB fo walk if NO WAY TILE
				if (battle_map.No_Way_Object(x_over, -y_over, persons, size_persons))
				{
					//Save way tile to first cell of way arr
					person_selected->step[0].x = x_over;
					person_selected->step[0].y = y_over;
				}
						
				//std::cout << x_over << " - " << y_over << std::endl;

				//Clear other cells, NO first
				for (int i = 1; i < person_selected->walk_range; i++)
				{
					person_selected->step[i].x = -1.0f;
					person_selected->step[i].y =  1.0f;

					//By RMB activate move person flag
					if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)//if RMB pressed
					{
						person_selected->walk_flag = true;
					}
				}

				
			}

			//Block of check second tile, nearest to ferst tile in arr way
			if (person_selected->step[0].x >= 0 && person_selected->step[0].y <= 0)
			{
				if (x_over >= person_selected->step[0].x - 1 && x_over <= person_selected->step[0].x + 1 &&
					y_over >= person_selected->step[0].y - 1 && y_over <= person_selected->step[0].y + 1)
				{
					//Don't save way tile to arr AND don't RMB fo walk if NO WAY TILE
					if (battle_map.No_Way_Object(x_over, -y_over, persons, size_persons))
					{
						//Save way tile to first cell of way arr
						person_selected->step[1].x = x_over;
						person_selected->step[1].y = y_over;

						//By RMB activate move person flag
						if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)//if RMB pressed
						{
							person_selected->walk_flag = true;
						}
					}

					
				}
			}

			break;
		}

		//Block for persons with 3 steps
		case 3: {
			//Block of chek nearest to person tile
			if (x_over >= person_selected->x - 1 && x_over <= person_selected->x + 1 &&
				y_over >= person_selected->y - 1 && y_over <= person_selected->y + 1)
			{
				//Don't save way tile to arr AND don't RMB fo walk if NO WAY TILE
				if (battle_map.No_Way_Object(x_over, -y_over, persons, size_persons))
				{
					//Save way tile to second cell of way arr
					person_selected->step[0].x = x_over;
					person_selected->step[0].y = y_over;

					//By RMB activate move person flag
					if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)//if RMB pressed
					{
						person_selected->walk_flag = true;
					}
				}

				//std::cout << x_over << " - " << y_over << std::endl;

				//Clear other cells, NO first
				for (int i = 1; i < person_selected->walk_range; i++)
				{
					person_selected->step[i].x = -1.0f;
					person_selected->step[i].y = 1.0f;
				}
			}

			//Block of check second tile, nearest to first tile in arr way
			if (person_selected->step[0].x >= 0 && person_selected->step[0].y <= 0)
			{
				if (x_over >= person_selected->step[0].x - 1 && x_over <= person_selected->step[0].x + 1 &&
					y_over >= person_selected->step[0].y - 1 && y_over <= person_selected->step[0].y + 1)
				{
					//Don't save way tile to arr AND don't RMB fo walk if NO WAY TILE
					if (battle_map.No_Way_Object(x_over, -y_over, persons, size_persons))
					{
						//Save way tile to second cell of way arr
						person_selected->step[1].x = x_over;
						person_selected->step[1].y = y_over;

						//By RMB activate move person flag
						if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)//if RMB pressed
						{
							person_selected->walk_flag = true;
						}
					}
				}
			}

			//Block of check Third tile, nearest to second tile in arr way
			if (person_selected->step[1].x >= 0 && person_selected->step[1].y <= 0)
			{
				if (x_over >= person_selected->step[1].x - 1 && x_over <= person_selected->step[1].x + 1 &&
					y_over >= person_selected->step[1].y - 1 && y_over <= person_selected->step[1].y + 1)
				{
					//Don't save way tile to arr AND don't RMB fo walk if NO WAY TILE
					if (battle_map.No_Way_Object(x_over, -y_over, persons, size_persons))
					{
						//Save way tile to second cell of way arr
						person_selected->step[2].x = x_over;
						person_selected->step[2].y = y_over;

						//By RMB activate move person flag
						if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)//if RMB pressed
						{
							person_selected->walk_flag = true;
						}
					}
				}
			}

			break;
		}
		
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
	if (person_selected && battle_interface->go_flag && person_selected->walk_flag)
	{
		//Move person
		//if (!person_selected->Move(person_selected->step[chk_walk_rng].x, -person_selected->step[chk_walk_rng].y, person_selected->step[chk_walk_rng].z))
		if (person_selected->step[chk_walk_rng].x >=0 && person_selected->step[chk_walk_rng].y <= 0 && person_selected->step[chk_walk_rng].z >= 0 &&
			!person_selected->Move(person_selected->step[chk_walk_rng].x, -person_selected->step[chk_walk_rng].y, person_selected->step[chk_walk_rng].z))
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
				//clear array trajectory of move
				for (int i = 0; i < person_selected->walk_range; i++)
				{
					person_selected->step[i].x = -1;
					person_selected->step[i].y =  1;
				}

				//change anime to stand
				person_selected->Change_Enum_Anime(0);

				//Stop person
				person_selected->walk_flag = false;

				//Unselect person
				person_selected->selected = false;

				//clear pointer of selected person
				person_selected = 0;

				//unset go button in interface
				battle_interface->go_flag = false;

				//reset counter of steps
				chk_walk_rng = 0;
			}
		}
	}
}