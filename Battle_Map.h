#pragma once
#include <vector>
#include "Tile.h"
#include "Camera.h"
#include "Data.h"

//extern char map_prototype[10][10];

class Battle_Map
{
public:
	char map_prototype[10][10] = {
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
	};

	//array of tiles
	std::vector <std::vector <Tile*>> map;

	//default constructor
	//Battle_Map(int width, int height);
	Battle_Map();

	void Draw(Camera & camera, CLR);

	~Battle_Map();
};

