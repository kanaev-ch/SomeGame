#include "Battle.h"

//func do Sort Ascending of arr
void sort_arr(std::vector<Person*>& persons)
{
	Person* ex;
	for (size_t i = persons.size() - 1; i > 0; --i)
	{
		for (size_t j = 0; j < i; ++j)
			if (persons[j]->initiative > persons[i]->initiative)
			{
				ex = persons[j]; persons[j] = persons[i];  persons[i] = ex;
			}
	}
}

Battle::Battle(std::vector<Person*>&persons)
{
	//Block of adding enemies in arr
	persons.push_back(new Lizardman("Person.vert", "Person.frag", "Textures/Persons/Lizardman/Lizardman_stand_1.png", "Textures/Persons/Lizardman/Lizardman_run_3.png",
		"Textures/Persons/Lizardman/Lizardman_strike_sword_3.png", "Textures/Persons/Lizardman/Lizardman_injured_2.png", "Textures/Persons/Lizardman/Lizardman_defends_2.png",
		"Textures/Persons/Lizardman/Lizardman_fall_2.png", "Textures/Persons/Lizardman/Lizardman_dead_1.png", 5, 2, 0, 2, 3));
	persons.push_back(new Lizardman("Person.vert", "Person.frag", "Textures/Persons/Lizardman/Lizardman_stand_1.png", "Textures/Persons/Lizardman/Lizardman_run_3.png",
		"Textures/Persons/Lizardman/Lizardman_strike_sword_3.png", "Textures/Persons/Lizardman/Lizardman_injured_2.png", "Textures/Persons/Lizardman/Lizardman_defends_2.png",
		"Textures/Persons/Lizardman/Lizardman_fall_2.png", "Textures/Persons/Lizardman/Lizardman_dead_1.png", 5, 4, 0, 2, 3));
	persons.push_back(new Lizardman("Person.vert", "Person.frag", "Textures/Persons/Lizardman/Lizardman_stand_1.png", "Textures/Persons/Lizardman/Lizardman_run_3.png",
		"Textures/Persons/Lizardman/Lizardman_strike_sword_3.png", "Textures/Persons/Lizardman/Lizardman_injured_2.png", "Textures/Persons/Lizardman/Lizardman_defends_2.png",
		"Textures/Persons/Lizardman/Lizardman_fall_2.png", "Textures/Persons/Lizardman/Lizardman_dead_1.png", 5, 6, 0, 2, 3));

	//Calculate initiative of person
	for (int i = 0; i < persons.size(); i++)
	{
		persons[i]->initiative += (rand() % 6 + 1) + (rand() % 6 + 1);
	}

	//Sort arr of person by initiative
	//sort_arr(persons);

	/*for (int i = 0; i < persons.size(); i++)
	{
		std::cout << persons[i]->initiative << std::endl;
	}*/

	//Block if initiate start values of counters and vars
	count_person_steps = 0;
	count_person_in_phase = 0;
	count_phases = 0;
	end_of_battle = false;

	//firts person selecting
	//person_selected = persons[count_person_in_phase];
	//person_selected = 0;
	Make_Active_Person_Selected(persons[count_person_in_phase]);

	is_anime_melee_atk_playing = false;

	skipping_step_flag = true;
}


Battle::~Battle()
{
	
}

void Battle::Make_Active_Person_Selected(Person * person)
{
	//Push to person_selected current or next person
	person_selected = person;

	//Lighter him if selected
	person_selected->selected = true;
}

void Battle::Switch_to_Next_Step_Person(std::vector<Person*>& persons)
{
	//std::cout << count_person_steps << "!" << std::endl;
	//When person ended moves
	if (!person_selected)
	{
		//Go to next step of person
		count_person_steps++;
		//std::cout << "!!!!" << std::endl;

		//std::cout << count_person_steps << "!" << std::endl;
		
		//Select current person
		Make_Active_Person_Selected(persons[count_person_in_phase]);
	}
}

void Battle::Switch_to_Next_Person(std::vector<Person*>& persons)
{
	//End of steps of one person
	if (count_person_steps >= persons[count_person_in_phase]->lifes_steps.size())
	{
		//Go to the next person
		count_person_in_phase++;

		//std::cout << count_person_in_phase << std::endl;

		//Reset count steps of next person
		count_person_steps = 0;

		//Clear current person
		Clear_Person_Selected();

		//Block of switch to next phase and start it from beginning
		if (count_person_in_phase >= persons.size())
		{
			//std::cout << count_person_in_phase << std::endl;

			count_person_in_phase = 0;

			//Reset count steps of next person
			count_person_steps = 0;

			//Make active next person
			//person_selected = persons[count_person_in_phase];
			Make_Active_Person_Selected(persons[count_person_in_phase]);

			//Increment counter of phases
			count_phases++;
			return;
		}

		//Make active next person
		Make_Active_Person_Selected(persons[count_person_in_phase]);

		//std::cout << count_person_in_phase << std::endl;
	}
}

void Battle::Click_Lmb_on_Top_interface(GLFWwindow* window, Camera& camera, std::vector<Person*>& persons)
{
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)//если нажата ЛКМ
	{
		glfwGetCursorPos(window, &mouseX, &mouseY);

		//block of calculate screen coords ortho Battle_Interface
		if (mouseY <= HEIGHT_SCREEN * battle_interface->bg_scl)
		{
			//if (!battle_interface->go_flag && person_selected && person_selected->lifes_steps[count_person_steps] >= 1)
			if (person_selected && person_selected->lifes_steps[count_person_steps] >= 1)
			{
				//std::cout << "Top" << std::endl;
				//glfwGetCursorPos(window, &mouseX, &mouseY);

				//Block compare coords of buttons with LKM coords
				//WIDTH_SCREEN * battle_interface->aspect * battle_interface->go->x_sc - is width of button by x
				//HEIGHT_SCREEN * battle_interface->go->y_sc - is height of button by y
				//ON go button, compare with global time
				if ((mouseX >= (WIDTH_SCREEN * battle_interface->aspect * battle_interface->go->x_sc / 2) * battle_interface->go->x_tr &&
					mouseX <= (WIDTH_SCREEN * battle_interface->aspect * battle_interface->go->x_sc / 2) * battle_interface->go->x_tr + (WIDTH_SCREEN * battle_interface->aspect * battle_interface->go->x_sc)) &&
					(mouseY >= (HEIGHT_SCREEN * battle_interface->go->y_sc / 2) * battle_interface->go->y_tr &&
					mouseY <= (HEIGHT_SCREEN * battle_interface->go->y_sc / 2) * battle_interface->go->y_tr + (HEIGHT_SCREEN * battle_interface->go->y_sc)) &&
					!battle_interface->atk_flag &&
					!battle_interface->go_flag && global_time > 0.2f)
				{
					//ON go flag
					battle_interface->go_flag = true;
					//std::cout << mouseX << " GO " << mouseY << std::endl;

					//reset global time for non immideatelly on-off button
					global_time = 0;
				}
				//OFF go button, compare with global time
				else if ((mouseX >= (WIDTH_SCREEN * battle_interface->aspect * battle_interface->go->x_sc / 2) * battle_interface->go->x_tr &&
					mouseX <= (WIDTH_SCREEN * battle_interface->aspect * battle_interface->go->x_sc / 2) * battle_interface->go->x_tr + (WIDTH_SCREEN * battle_interface->aspect * battle_interface->go->x_sc)) &&
					(mouseY >= (HEIGHT_SCREEN * battle_interface->go->y_sc / 2) * battle_interface->go->y_tr &&
					mouseY <= (HEIGHT_SCREEN * battle_interface->go->y_sc / 2) * battle_interface->go->y_tr + (HEIGHT_SCREEN * battle_interface->go->y_sc)) &&
					!battle_interface->atk_flag &&
					battle_interface->go_flag && global_time > 0.2f)
				{
					//OFF go flag
					battle_interface->go_flag = false;
					//std::cout << mouseX << " GO " << mouseY << std::endl;

					//reset global time for non immideatelly on-off button
					global_time = 0;
				}
			}

			//if (!battle_interface->atk_flag && person_selected && person_selected->skirmish.size() > 0 && person_selected->lifes_steps[count_person_steps] >= 3)
			if (person_selected && person_selected->skirmish.size() > 0 && person_selected->lifes_steps[count_person_steps] >= 3)
			{
				//ON atk button, compare with global time
				if ((mouseX >= (WIDTH_SCREEN * battle_interface->aspect * battle_interface->attack->x_sc / 2) * battle_interface->attack->x_tr &&
					mouseX <= (WIDTH_SCREEN * battle_interface->aspect * battle_interface->attack->x_sc / 2) * battle_interface->attack->x_tr + (WIDTH_SCREEN * battle_interface->aspect * battle_interface->attack->x_sc)) &&
					(mouseY >= (HEIGHT_SCREEN * battle_interface->attack->y_sc / 2) * battle_interface->attack->y_tr &&
					mouseY <= (HEIGHT_SCREEN * battle_interface->attack->y_sc / 2) * battle_interface->attack->y_tr + (HEIGHT_SCREEN * battle_interface->attack->y_sc)) && 
					!battle_interface->go_flag &&
					!battle_interface->atk_flag&& global_time > 0.2f)
				{
					battle_interface->atk_flag = true;
					//std::cout << mouseX << " ATTACK " << mouseY << std::endl;

					//reset global time for non immideatelly on-off button
					global_time = 0;
				}
				//OFF atk button, compare with global time
				else if ((mouseX >= (WIDTH_SCREEN * battle_interface->aspect * battle_interface->attack->x_sc / 2) * battle_interface->attack->x_tr &&
					mouseX <= (WIDTH_SCREEN * battle_interface->aspect * battle_interface->attack->x_sc / 2) * battle_interface->attack->x_tr + (WIDTH_SCREEN * battle_interface->aspect * battle_interface->attack->x_sc)) &&
					(mouseY >= (HEIGHT_SCREEN * battle_interface->attack->y_sc / 2) * battle_interface->attack->y_tr &&
						mouseY <= (HEIGHT_SCREEN * battle_interface->attack->y_sc / 2) * battle_interface->attack->y_tr + (HEIGHT_SCREEN * battle_interface->attack->y_sc)) &&
					!battle_interface->go_flag &&
					battle_interface->atk_flag && global_time > 0.2f)
				{
					battle_interface->atk_flag = false;
					//std::cout << mouseX << " ATTACK " << mouseY << std::endl;

					//reset global time for non immideatelly on-off button
					global_time = 0;
				}
			}

			//Unselect go button
			if (person_selected == 0 && battle_interface->go_flag)
				battle_interface->go_flag = false;

			//Unselect atk button
			if (person_selected == 0 && battle_interface->atk_flag)
				battle_interface->atk_flag = false;
		}
	}
}

void Battle::Click_Lmb_on_Main_Screen(GLFWwindow* window, Camera& camera, std::vector<Person*>& persons)
{
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)//если нажата ЛКМ
	{
		glfwGetCursorPos(window, &mouseX, &mouseY);

		if (mouseY > HEIGHT_SCREEN * battle_interface->bg_scl)
		{
			//std::cout << "Bottom" << std::endl;

			GLfloat _z;
			glReadPixels(int(mouseX), HEIGHT_SCREEN - int(mouseY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &_z);

			glm::mat4 view = glm::lookAt(camera.Position, camera.Position + camera.Orientation, camera.Up);

			glm::vec3 win = glm::unProject(glm::vec3(int(mouseX), HEIGHT_SCREEN - int(mouseY), _z), view, camera.projection, glm::vec4(0, 0, WIDTH_SCREEN, HEIGHT_SCREEN));
			//std::cout << win.x << " " << win.y << " " << win.z << std::endl;

			//Rounded data is here, save into vars of class
			x = float(int(win.x + 0.5f)); y = float(int(win.y - 0.5f)); z = float(int(win.z + 0.9f));
			//std::cout << x << " " << y << " " << z << std::endl;
		}
	}
}

void Battle::Go_Out_From_Skirmish(GLFWwindow* window)
{
	/*if (person_selected)
	{
		std::cout << person_selected->skirmish.size() << std::endl;
	}*/

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && person_selected->skirmish.size() > 0)//если нажата ЛКМ
	{
		if (person_selected && battle_interface->go_flag && person_selected->walk_flag)
		{
			int skirmish_size = int(person_selected->skirmish.size());

			//Look at the whole skirmish array
			for (int i = 0; i < person_selected->skirmish.size(); i++)
			{
				//Block of changing view direction of striker
				PERSON_DIRECTION from_what_side_is_striker = right;

				//Remember from what side is opponent of striker
				if (person_selected->x > person_selected->skirmish[i]->x)
					from_what_side_is_striker = right;
				if (person_selected->x < person_selected->skirmish[i]->x)
					from_what_side_is_striker = left;

				//Change direction of striker
				if (person_selected->skirmish[i]->direction != from_what_side_is_striker)
					person_selected->skirmish[i]->change_Direction(PERSON_DIRECTION(!person_selected->skirmish[i]->direction));




				//Calculate Hit strike or not
				//int atk_hot_or_not = rand() % 6 + 1 + person_selected->agility;
				int atk_hit_or_not = rand() % 6 + 1 + person_selected->skirmish[i]->agility + 10;
				//int defense_recap_or_not = rand() % 6 + 1 + person_selected->skirmish[i]->agility;
				int defense_recap_or_not = rand() % 6 + 1 + person_selected->agility;

				//Block of strike hit to person from enemy, Lowing lifes
				if (atk_hit_or_not > defense_recap_or_not)
				{
					//Block of Lowing lifes (lifes_steps arr)
					if (person_selected->lifes_steps.size() == 1)
						//Lowing 1 life if there is operson have only one life
						person_selected->lifes_steps.pop_back();
					else if (person_selected->lifes_steps.size() > 1) 
					{
						//if sthength 1-2, lowing 1 life
						if (person_selected->skirmish[i]->strength <= 2)
						{
							person_selected->lifes_steps.pop_back();
							//std::cout << "1" << std::endl;
						}
						//if sthength 3-4, lowing 2 lifes
						else if (person_selected->skirmish[i]->strength > 2 && person_selected->skirmish[i]->strength <= 4)
						{
							person_selected->lifes_steps.pop_back(); person_selected->lifes_steps.pop_back();
							//std::cout << "2" << std::endl;
						}
						//if sthength 5-6, lowing 3 lifes
						else if (person_selected->skirmish[i]->strength > 4 && person_selected->skirmish[i]->strength <= 6)
						{
							person_selected->lifes_steps.pop_back(); person_selected->lifes_steps.pop_back(); person_selected->lifes_steps.pop_back();
						}
						//...etc we must do bigger how much lifes lowing by the strength of person
					}

					//Change anime to injured
					person_selected->Change_Enum_Anime(injured);

					//battle_interface->go_flag = false;
					//person_selected->walk_flag = false;

					//This needs for last step out of person when he injured, if the count_person_steps is not artificially decremented, the person_selected will not take this step out
					if (count_person_steps >= person_selected->lifes_steps.size())
						count_person_steps--;
				}

				//Block of person die
				if (person_selected->lifes_steps.size() == 0)
				{
					//Change anime to fall
					person_selected->Change_Enum_Anime(dead);
					
					//Reset button flags
					battle_interface->go_flag = false;
					person_selected->walk_flag = false;

					//std::cout << "!" << std::endl;
				}




				//Reset global_time for anime
				global_time = 0;

				//Change anime of striker to strike
				person_selected->skirmish[i]->Change_Enum_Anime(strike_sword);

				//Remove from skirmish arr of enemy current person_selected, look over all skirmish arr of enemy, are loking for same pointer like person_selected in it
				for (int j = 0; j < person_selected->skirmish[i]->skirmish.size(); j++)
					//If pointers of person_selected and himself in skirmish arr of his opponent are same
					if (person_selected == person_selected->skirmish[i]->skirmish[j])
					{
						//Remove it
						//std::cout << person_selected << " " << person_selected->skirmish[i]->skirmish[j];
						person_selected->skirmish[i]->skirmish.erase(person_selected->skirmish[i]->skirmish.begin() + j);
					}

				//Remove from person skirmish arr his enemy
				//person_selected->skirmish.erase(person_selected->skirmish.begin() + i);
			}

			//std::cout << person_selected->skirmish.size() << std::endl;
			//Clear skirmish arr of person selected
			for (int i = 0; i < skirmish_size; i++)
			{
				person_selected->skirmish.pop_back();
			}
		}
	}
}

void Battle::Move(std::vector<Person*>& persons, GLFWwindow* window)
{
	//Move person if Battle_Interface flag active and person selected AND if he isn't injured when trying Go_Out_From_Skirmish
	//if (person_selected && battle_interface->go_flag && person_selected->walk_flag)
	if (person_selected && battle_interface->go_flag && person_selected->walk_flag && person_selected->anime != injured)
	{
		//Move person
		if (person_selected->step[chk_walk_rng].x >= 0 && person_selected->step[chk_walk_rng].y <= 0 && person_selected->step[chk_walk_rng].z >= 0 &&
			!person_selected->Move(person_selected->step[chk_walk_rng].x, -person_selected->step[chk_walk_rng].y, person_selected->step[chk_walk_rng].z))
		{
			person_selected->Change_Enum_Anime(walk);
		}
		else
		{
			//Block of check on each step person if He near the enemy
			//Check current cell of arr steps is not empty
			if (person_selected->step[chk_walk_rng].x >= 0 && person_selected->step[chk_walk_rng].y <= 0)
			{
				//Check all arr of persons with same coords
				for (int i = 0; i < persons.size(); i++)
				{
					//Check coords of current person with arr of person nearer 1 cel of him and that opposing person is enemy
					if (persons[i]->x >= person_selected->x - 1 && persons[i]->x <= person_selected->x + 1 &&
						persons[i]->y >= person_selected->y - 1 && persons[i]->y <= person_selected->y + 1 &&
						persons[i]->person_type != person_selected->person_type &&
						persons[i]->lifes_steps.size() > 0)
					{
						//std::cout << persons[i]->x << "-" << persons[i]->y << " " << person_selected->x << "-" << person_selected->y << std::endl;

						//Push Up in skirmish vectors of each person nearest opposing person
						person_selected->skirmish.push_back(persons[i]);
						persons[i]->skirmish.push_back(person_selected);
					}
				}
				//std::cout << person_selected->skirmish.size() << std::endl;

				//Stop person_selected if there is enemy nearbuy, he will not move farer buy step arr 
				if (person_selected->skirmish.size() > 0)
					{
						Clear_Person_Selected();
						return;
					}
			}
			//std::cout << person_selected->step[chk_walk_rng].x << " " << person_selected->step[chk_walk_rng].y << std::endl;

			//if end current step switch to next
			chk_walk_rng++;

			//end of walk
			if (chk_walk_rng == person_selected->walk_range)
			{
				//Reset coord of LKM 
				x = -1; y = 1;

				Clear_Person_Selected();
				//std::cout << "!!!!!!" << std::endl;
			}
		}
	}
}

void Battle::Melee_Attack(GLFWwindow* window, std::vector<Person*>& persons)
{
	//Block of switch to next step or next person step if melee anime ended
	if (person_selected && !person_selected->is_anime_cycle_playing && is_anime_melee_atk_playing)
	{
		//OFF flag melee anime
		is_anime_melee_atk_playing = false;

		//Clear current person
		Clear_Person_Selected();

		//Reset LKM coords to not in map for non repeat melee atk anime when press atk button
		x = -1; y = 1;

		//Exit, farer doesn't need do code
		return;
	}

	//Block of melee atk
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)//если нажата ЛКМ
	{
		if (person_selected && battle_interface->atk_flag)
		{
			//Check all skirmish arr
			for (int i = 0; i < person_selected->skirmish.size(); i++)
			{
				//If coords are same with LKM
				if (x == person_selected->skirmish[i]->x && y == person_selected->skirmish[i]->y && person_selected->skirmish[i]->lifes_steps.size() > 0)
				{

					//Block of changing direction in the time of strike
					//Start values
					PERSON_DIRECTION from_what_side_is_enemy = left;
					PERSON_DIRECTION from_what_side_is_striker = right;

					//Remember where is the striker and his opponent
					if (person_selected->x > person_selected->skirmish[i]->x)
					{
						from_what_side_is_enemy = left;
						from_what_side_is_striker = right;
					}
					if (person_selected->x < person_selected->skirmish[i]->x)
					{
						from_what_side_is_enemy = right;
						from_what_side_is_striker = left;
					}

					//Change direction of striker
					if (person_selected->direction != from_what_side_is_enemy)
						person_selected->change_Direction(PERSON_DIRECTION(!person_selected->direction));

					//Change direction whom strike
					if (person_selected->skirmish[i]->direction != from_what_side_is_striker)
						person_selected->skirmish[i]->change_Direction(PERSON_DIRECTION(!person_selected->skirmish[i]->direction));

					//Needs for melee atk anime play from beginning
					global_time = 0;

					//Change anime
					person_selected->Change_Enum_Anime(strike_sword);

					//OFF atk button
					battle_interface->atk_flag = false;

					//ON anime flag in person class
					person_selected->is_anime_cycle_playing = true;

					//ON anime flag of battle class
					is_anime_melee_atk_playing = true;

					//Calculate Hit strike or not
					//int atk_hot_or_not = rand() % 6 + 1 + person_selected->agility;
					int atk_hit_or_not = rand() % 6 + 1 + person_selected->agility + 10;
					//int defense_recap_or_not = rand() % 6 + 1 + person_selected->skirmish[i]->agility;
					int defense_recap_or_not = rand() % 6 + 1 + person_selected->skirmish[i]->agility;

					//Block of strike hit to opponent, Lowing lifes
					if (atk_hit_or_not > defense_recap_or_not)
					{
						//Change anime to injured
						person_selected->skirmish[i]->Change_Enum_Anime(injured);

						//Block of Lowing lifes (lifes_steps arr)
						if (person_selected->skirmish[i]->lifes_steps.size() == 1)
							//Lowing 1 life if there is operson have only one life
							person_selected->skirmish[i]->lifes_steps.pop_back();
						else if (person_selected->skirmish[i]->lifes_steps.size() > 1)
						{
							//if sthength 1-2, lowing 1 life
							if (person_selected->strength <= 2)
								person_selected->skirmish[i]->lifes_steps.pop_back();
							//if sthength 3-4, lowing 2 lifes
							else if (person_selected->strength > 2 && person_selected->strength <= 4)
							{
								person_selected->skirmish[i]->lifes_steps.pop_back(); person_selected->skirmish[i]->lifes_steps.pop_back();
							}
							//if sthength 5-6, lowing 3 lifes
							else if (person_selected->strength > 4 && person_selected->strength <= 6)
							{
								person_selected->skirmish[i]->lifes_steps.pop_back(); person_selected->skirmish[i]->lifes_steps.pop_back(); person_selected->skirmish[i]->lifes_steps.pop_back();
							}
							//...etc we must do bigger how much lifes lowing by the strength of person
						}
					}
					//If not hit
					else if (atk_hit_or_not <= defense_recap_or_not)
						//Change anime to defends
						person_selected->skirmish[i]->Change_Enum_Anime(defends);

					//Block of person die and remove from ALL skirmish arrays
					if (person_selected->skirmish[i]->lifes_steps.size() == 0)
					{
						//Change anime to fall, IMPORTANT fall anime must be smaler by frames then strike_sword, or person will stand after dead
						person_selected->skirmish[i]->Change_Enum_Anime(fall);
						//person_selected->skirmish[i]->Change_Enum_Anime(dead);

						//Remove him from all skirmish arrays
						for (int i = 0; i < persons.size(); i++)
							for (int j = 0; j < persons[i]->skirmish.size(); j++)
							{
								if (persons[i]->skirmish[j]->lifes_steps.size() == 0)
									persons[i]->skirmish.erase(persons[i]->skirmish.begin() + j);
							}
					}

				}
			}
		}

		//Temporary block printing lifes_steps arr
		/*for (int i = 0; i < persons[count_person_in_phase]->lifes_steps.size(); i++)
			std::cout << persons[count_person_in_phase]->lifes_steps[i] << " ! ";

		for (int i = 0; i < person_selected->lifes_steps.size(); i++)
			std::cout << person_selected->lifes_steps[i] << " ";
		std::cout << std::endl;*/
	}


	/*if (person_selected->skirmish.size() > 0)
	{
		for (int j = 0; j < person_selected->lifes_steps.size(); j++)
			std::cout << person_selected->lifes_steps[j] << "   ";
		std::cout << " ----- ";
		for (int j = 0; j < person_selected->skirmish[k]->lifes_steps.size(); j++)
			std::cout << person_selected->skirmish[k]->lifes_steps[j] << " ! ";
		std::cout << " : ATK - " << atk_hot_or_not << " : DEF - " << defense_recap_or_not;
		std::cout << std::endl;
	}*/
	
}

void Battle::Skipping_Step(GLFWwindow* window)
{
	//std::cout << global_time << std::endl;

	//Reset skipping_step_flag by global time
	if (global_time > 0.2f)
		skipping_step_flag = true;

	//Block of skipping step
	if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS || (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) && skipping_step_flag)
	{
		//Skip step
		Clear_Person_Selected();

		//Reset flag
		skipping_step_flag = false;

		//Reset global time
		global_time = 0;
	}
}