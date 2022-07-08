#pragma once
#include "Control.h"
#include "Lizardman.h"
//#include "Data.h"

class Battle :
	public Control
{
public:
	//How much steps person can make in phase
	int count_person_steps;

	//How much persons in one phase
	int count_person_in_phase;

	//All phases in battle
	int count_phases;

	//Flag end of battle
	bool end_of_battle;

	//Flag ON when anime melee atk playing, works dual with flag person_selected->is_anime_cycle_playing
	bool is_anime_melee_atk_playing;

	//Flag for skipping step, need for work skipping person by one time, non billion times in second
	bool skipping_step_flag;

	Battle(std::vector<Person*>&);
	~Battle();

	//Func push to person_selected current or next person, do him active
	void Make_Active_Person_Selected(Person * person);

	//Func switch to next step of person and copy it to person_selected
	void Switch_to_Next_Step_Person(std::vector<Person*>& persons);

	//Func Switch to Next Person in_Phase and reset counter of steps
	void Switch_to_Next_Person(std::vector<Person*>& persons);

	//Func activate next step id current person or next person
	void Mark_Active_By_Person(std::vector<Person*>& persons);

	//Func save World coords of click LMB on top Menu, it moved from Control. May be it must rebuild
	void Click_Lmb_on_Top_interface(GLFWwindow* window, Camera& camera, std::vector<Person*>& persons);

	//Func save World coords of click LMB on main scriin, it moved from Control. May be it must rebuild
	void Click_Lmb_on_Main_Screen(GLFWwindow* window, Camera& camera, std::vector<Person*>& persons);

	//Func Calculate damage, animate strike, clear skirmish arr when person wants go out from skirmish
	void Go_Out_From_Skirmish(GLFWwindow* window);

	//Func move person
	void Move(std::vector<Person*>& persons, GLFWwindow* window);

	//Func of atk
	void Melee_Attack(GLFWwindow* window, std::vector<Person*>& persons);

	//Func of skipping step of person
	void Skipping_Step(GLFWwindow* window);

	//func do Sort Ascending of arr persons
	friend void sort_arr(std::vector<Person*>&);//func do Sort Ascending of arr, array members must not be zeros!!!
};

