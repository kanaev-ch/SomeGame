#pragma once
#include <vector>
#include "Tile.h"
#include "Camera.h"
#include "Data.h"

//extern char map_prototype[10][10];

class Battle_Map
{
public:
	char map_prototype[8][12] = {
	{'F','G','G','G','G','G','G','G','G','F','G','F'},
	{'G','G','G','G','G','G','G','G','G','G','G','F'},
	{'G','G','G','G','G','G','G','G','G','G','G','F'},
	{'G','G','G','G','G','G','G','G','G','G','G','F'},
	{'G','G','G','F','G','G','G','F','G','G','G','F'},
	{'G','G','G','G','G','G','G','G','G','G','G','F'},
	{'G','G','G','G','G','G','G','G','G','G','G','F'},
	{'G','G','G','F','G','G','G','G','G','G','G','F'},
	};

	//width and height of map
	int map_w, map_h;

	//array of tiles
	std::vector <std::vector <Tile*>> map;

	//default constructor
	//Battle_Map(int width, int height);
	Battle_Map();
	Battle_Map(float z);

	void Draw(Camera & camera, CLR);

	~Battle_Map();
};

