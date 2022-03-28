#pragma once
#include <vector>
#include "Tile.h"
#include "Camera.h"

class Battle_Map
{
public:
	//array of tiles
	std::vector <std::vector <Tile*>> map;

	//default constructor
	Battle_Map(int width, int height);

	void Draw(Camera & camera);

	~Battle_Map();
};

