#pragma once

#include "Game.h"

class GameObject
{
public:
	GameObject(const char* texturesheet, int x, int y);
	//~GameObject();

	void Update();
	void Render();
	virtual void Collision(int x, int y);
	int xpos, ypos;

protected:
	int speed = 3;
	int direction=3;

	SDL_Texture* objTexture;
	SDL_Rect srcRect, dstRect;
};


