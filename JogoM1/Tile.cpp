#include "Tile.h"
#include "TextureManager.h"
#include <iostream>



Tile::Tile()
{
	src = { 0, 0, 32, 32};
	dst.h = dst.w = 32;
}


Tile::~Tile()
{
	SDL_DestroyTexture(texture);
}

void Tile::setState(int state)
{	
	if (this != nullptr) {
		this->state = state;
		if (this->existe == false) {
			this->existe = true;
			switch (state)
			{
			case 0:
				texture = TextureManager::LoadTexture("Assets/ground_tex.png");
				src.y = 32;
				src.x = 64;
				break;
			case 1:
				texture = TextureManager::LoadTexture("Assets/ground_tex.png");
				src.y = 64;
				src.x = 64;
				this->state = 0;
				break;
			case 2:
				texture = TextureManager::LoadTexture("Assets/ground_tex.png");
				src.y = 96;
				src.x = 64;
				break;
			case 3:
				texture = TextureManager::LoadTexture("Assets/ground_tex.png");
				src.y = 128;
				src.x = 64;
				break;
			case 4:
				texture = TextureManager::LoadTexture("Assets/ground_tex.png");
				src.y = 64;
				src.x = 32;
				this->state = 0;
				break;
			case 5:
				texture = TextureManager::LoadTexture("Assets/ground_tex.png");
				src.y = 32;
				src.x = 0;
				this->state = 0;
				break;
			case 6:
				texture = TextureManager::LoadTexture("Assets/ground_tex.png");
				src.y = 96;
				src.x = 0;
				break;
			case 7:
				texture = TextureManager::LoadTexture("Assets/ground_tex.png");
				src.y = 96;
				src.x = 32;
				break;
			case 8:
				texture = TextureManager::LoadTexture("Assets/wall_8.png");
				src.y = 0;
				src.x = 0;
				break;
			case 9:
				texture = TextureManager::LoadTexture("Assets/ground_tex.png");
				src.y = 128;
				src.x = 0;
				break;
			case 10:
				texture = TextureManager::LoadTexture("Assets/ground_tex.png");
				src.y = 128;
				src.x = 32;
				break;
			case 11:
				texture = TextureManager::LoadTexture("Assets/ground_tex.png");
				src.y = 32;
				src.x = 0;
				this->state = 5;
				break;
			default:
				this->state = 0;
				break;
			}
			if (this->state != 0 && this->state != 5) this->state = 1;
			oldState = this->state;
		}
	}
}

int Tile::getState() {
	if (this) return state;
	else return -1;
}

void Tile::returnState()
{
	if (this != nullptr) {
		state = oldState;
	}
}

void Tile::draw()
{
	TextureManager::Draw(texture, src, dst);
	if (state == 5) {
		SDL_SetRenderDrawColor(Game::renderer, 0, 255, 0, 255);
		SDL_RenderFillRect(Game::renderer, &dst);
		SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, 255);
	}
	if (Game::testMode) {
		if (state == 2) {
			SDL_SetRenderDrawColor(Game::renderer, 255, 0, 0, 255);
			SDL_RenderFillRect(Game::renderer, &dst);
		}
		SDL_RenderDrawRect(Game::renderer, &dst);
		SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, 255);
	}
}
