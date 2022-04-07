#include "Battle_Map.h"

char map_prototype[10][10] = {
	{'G','G','G','G','G','G','G','G','G','G'},
	{'G','G','G','G','G','G','G','G','G','G'},
	{'G','G','G','G','G','G','G','G','G','G'},
	{'G','G','G','G','G','G','G','G','G','G'},
	{'G','G','G','G','G','G','G','G','G','G'},
	{'G','G','G','G','G','G','G','G','G','G'},
	{'G','G','G','G','G','G','G','G','G','G'},
	{'G','G','G','G','G','G','G','G','G','G'},
	{'G','G','G','G','G','G','G','G','G','G'},
	{'F','G','G','G','G','G','G','G','F','G'},
};

Battle_Map::Battle_Map(int width, int height)
{
	map.resize(10);
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
		{
			switch (map_prototype[i][j])
			{
				case 'G': map[i].push_back(new Tile("Tile.vert", "Tile.frag", "Textures/floor.png", float(j), -float(i), 0)); break;
				case 'F': map[i].push_back(new Tile("Tile.vert", "Tile.frag", "Textures/fire_floor.png", float(j), -float(i), 0)); break;
			}

			//ON or OFF texture jr color of object 
			/*GLuint tex_or_clr = glGetUniformLocation(map[i][j]->shaderProgram, "tex_or_clr");
			glUseProgram(map[i][j]->shaderProgram);
			glUniform1i(tex_or_clr, 1);*/
		}
}

void Battle_Map::Draw(Camera& camera)
{
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
		{
			map[i][j]->Draw(camera);
		}
}

Battle_Map::~Battle_Map()
{
}