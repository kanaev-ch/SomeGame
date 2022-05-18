#pragma once
#include <vector>
#include "Tile.h"
#include "Camera.h"
#include "Data.h"
#include "Person.h"

//extern char map_prototype[10][10];

class Battle_Map
{
public:
	char map_prototype[8][12] = {
	{'G','G','G','G','G','G','G','G','G','F','G','F'},
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


	//std::vector <std::vector <int>> person_on_tile;

	//default constructor
	//Battle_Map(int width, int height);
	Battle_Map();
	Battle_Map(float z);

	//Check tiles walk or not
	bool No_Way_Object(float x, float y, std::vector <Person*> persons, size_t size_persons)const;

	void Draw(Camera & camera, CLR);

	~Battle_Map();
};

