#pragma once
#include "Game.h"
class Tile
{
public:
	Tile();
	~Tile();
	void setState(int state);
	int getState() { return state; }
	void draw();

	SDL_Rect src, dst;
private:
	int state;
	SDL_Texture* texture;
};

