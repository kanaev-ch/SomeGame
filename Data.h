#pragma once

extern int WIDTH_SCREEN;
extern int HEIGHT_SCREEN;

//Struct for array to move person by step-tiles
struct Step { float x, y, z; };

//Choose colors for tiles, but can use for anything. Using 777 system like linux rights
enum CLR { red = 1, green = 2, blue = 4, red_green = 3, red_blue = 5, green_blue = 6, rgb = 7 };
