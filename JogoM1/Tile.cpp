#include "Tile.h"
#include "TextureManager.h"
#include <iostream>



Tile::Tile()
{
	src = { 0, 0, 32, 32 };
	dst.h = dst.w = 32;
}


Tile::~Tile()
{
}

void Tile::setState(int state)
{
	this->state = state;
	switch (state)
	{
	case 0:
		texture = TextureManager::LoadTexture("Assets/woodenfloor.png");
		break;
	case 1:
		texture = TextureManager::LoadTexture("Assets/grass.png");
		break;
	default:
		break;
	}
}

void Tile::draw()
{
	TextureManager::Draw(texture, src, dst);

	if (Game::testMode) {
		if (state == 2) {
			SDL_SetRenderDrawColor(Game::renderer, 255, 0, 0, 255);
		}
		SDL_RenderDrawRect(Game::renderer, &dst);
		SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, 255);
	}
}
