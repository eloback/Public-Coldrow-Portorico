#pragma once

#include "Game.h"

class GameObject
{
public:
	GameObject(const char* texturesheet, int x, int y);
	virtual ~GameObject();

	virtual void Update();
	virtual void Render();
	virtual void Collision(int x, int y);
	virtual void vitoria(int x, int y) {};
	int xpos, ypos;
	bool morto = false;

protected:
	int speed = 3;
	int direction;
	int animationFrame = 0;

	SDL_Texture* objTexture;
	SDL_Rect srcRect, dstRect;
};


