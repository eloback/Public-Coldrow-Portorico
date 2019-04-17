#pragma once
#include "Game.h"
class Tile
{
public:
	Tile();
	~Tile();
	void setState(int state);
	int getState();
	void returnState();
	void draw();

	SDL_Rect src, dst;
	bool existe = false;
private:
	int state = NULL;
	int oldState;
	SDL_Texture* texture;
};

