#include "Battle_Map.h"

/*char map_prototype[10][10] = {
	{'F','G','G','G','G','G','G','G','G','F'},
	{'G','G','G','G','G','G','G','G','G','G'},
	{'G','G','G','G','G','G','G','G','G','G'},
	{'G','G','G','G','G','G','G','G','G','G'},
	{'G','G','G','F','G','G','G','F','G','G'},
	{'G','G','G','G','G','G','G','G','G','G'},
	{'G','G','G','G','G','G','G','G','G','G'},
	{'G','G','G','F','G','G','G','G','G','G'},
	{'G','G','G','G','G','G','G','G','G','G'},
	{'F','G','G','G','G','G','G','G','F','G'},
};*/

//Battle_Map::Battle_Map(int width, int height)
Battle_Map::Battle_Map()
{
	//calculate width and height
	map_w = sizeof(map_prototype[0]);
	map_h = sizeof(map_prototype) / map_w;;
	//std::cout << map_h << std::endl;

	map.resize(map_h);


//	person_on_tile.resize(map_h);

	for (int i = 0; i < map_h; i++)
		for (int j = 0; j < map_w; j++)
		{
			switch (map_prototype[i][j])
			{
				case 'G': map[i].push_back(new Tile("Tile.vert", "Tile.frag", "Textures/floor.png", float(j), -float(i), 0)); break;
				case 'F': map[i].push_back(new Tile("Tile.vert", "Tile.frag", "Textures/fire_floor.png", float(j), -float(i), 0)); break;
			}

			//person_on_tile[i][j] = 0;

			//ON or OFF texture jr color of object 
			/*GLuint tex_or_clr = glGetUniformLocation(map[i][j]->shaderProgram, "tex_or_clr");
			glUseProgram(map[i][j]->shaderProgram);
			glUniform1i(tex_or_clr, 1);*/
		}
}

Battle_Map::Battle_Map(float z)
{
	//calculate width and height
	map_w = sizeof(map_prototype[0]);
	map_h = sizeof(map_prototype) / map_w;;
	//std::cout << map_h << std::endl;


	map.resize(map_h);

	//person_on_tile.resize(map_h);

	for (int i = 0; i < map_h; i++)
		for (int j = 0; j < map_w; j++)
		{
			switch (map_prototype[i][j])
			{
			case 'G': map[i].push_back(new Tile("Tile.vert", "Tile.frag", "Textures/floor.png", float(j), -float(i), z)); break;
			case 'F': map[i].push_back(new Tile("Tile.vert", "Tile.frag", "Textures/fire_floor.png", float(j), -float(i), z)); break;
			}

			//person_on_tile[i][j] = 0;

			//ON or OFF texture jr color of object 
			/*GLuint tex_or_clr = glGetUniformLocation(map[i][j]->shaderProgram, "tex_or_clr");
			glUseProgram(map[i][j]->shaderProgram);
			glUniform1i(tex_or_clr, 1);*/
		}
}

bool Battle_Map::No_Way_Object(float x, float y, std::vector <Person*>& persons)const
{
	//If tile no way
	if (map_prototype[int(y)][int(x)] == 'F')
	{
		//std::cout << x << " - " << y << std::endl;
		return false;	
	}

	//If there is a person on tile AND hi is not dead
	for (int i = 0; i < persons.size(); i++)
	{
		if (x == persons[i]->x && y == -persons[i]->y && persons[i]->lifes_steps.size() > 0)
		{
			//std::cout << x << " ! " << y << std::endl;
			return false;
		}
	}
	//std::cout << x << " ! " << y << std::endl;
	return true;
}

void Battle_Map::Draw(Camera& camera, CLR clr)
{
	for (int i = 0; i < map_h; i++)
		for (int j = 0; j < map_w; j++)
		{
			map[i][j]->Draw(camera, clr);
		}
}

Battle_Map::~Battle_Map()
{
	for (int i = 0; i < map_h; i++)
		for (int j = 0; j < map_w; j++)
		{
			delete map[i][j];
		}
}