#include "Control.h"



Control::Control()
{
	x = y = z = 0;
	person_selected = 0;
}


Control::~Control()
{
}

void Control::Click_Lmb(GLFWwindow* window, Camera& camera, std::vector<Person*> persons, size_t size_persons)
{
	//block of calculate screen coords in world coords
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)//если нажата ЛКМ
	{
		double mouseX;
		double mouseY;
		glfwGetCursorPos(window, &mouseX, &mouseY);
		//std::cout << int(mouseX) << " - " << int(mouseY) << std::endl;

		GLfloat _z;
		glReadPixels(int(mouseX), HEIGHT_SCREEN - int(mouseY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &_z);

		glm::mat4 view = glm::lookAt(camera.Position, camera.Position + camera.Orientation, camera.Up);

		glm::vec3 win = glm::unProject(glm::vec3(int(mouseX), HEIGHT_SCREEN - int(mouseY), _z), view, camera.projection, glm::vec4(0, 0, WIDTH_SCREEN, HEIGHT_SCREEN));
		//std::cout << win.x << " " << win.y << " " << win.z << std::endl;
		
		//Rounded data is here
		x = float(int(win.x + 0.5f)); y = float(int(win.y - 0.5f)); z = float(int(win.z + 0.9f));
		//std::cout << x << " " << y << " " << z << std::endl;
	}

	

	//std::cout << persons[0]->x << " " << persons[0]->y << " " << persons[0]->z << std::endl;
	//std::cout << x << " " << y << " " << z << std::endl;
}

void Control::Mark_Active(std::vector<Person*> persons, size_t size_persons)
{
	for (int i = 0; i < size_persons; i++)
	{
		if (persons[i]->x == x && persons[i]->y == y && person_selected != persons[i]) person_selected = persons[i];
		//else person_selected = 0;

		if (person_selected == persons[i]) persons[i]->selected = true;
		else persons[i]->selected = false;
	}
}

void Control::Melee_Attack(GLFWwindow* window, std::vector<Person*> persons, size_t size_persons)
{
	
}

void Control::Move()
{
	if (person_selected)
		if (person_selected->x != x || person_selected->y != y)
		{
			if (!person_selected->Move(x, -y, z)) person_selected->Change_Enum_Anime(1);
			else person_selected->Change_Enum_Anime(0);
			//person_selected->Move(x, -y, z);
			//std::cout << x << " " << y << " " << z << std::endl;
		}
}