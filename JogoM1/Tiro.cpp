#include "Tiro.h"
#include <iostream>

Tiro::Tiro(vetor line, Map* mapa)
{
	this->mapa = mapa;
	this->line = line;
	xpos = line.x0;
	ypos = line.y0;
	existe = true;
	speedx = ((line.x1 - line.x0) / line.modulo) * speed;
	speedy = ((line.y1 - line.y0) / line.modulo) * speed;
	this->line.x1 = (line.x0 + ((speedx/speed) * 10000));
	this->line.y1 = (line.y0 + ((speedy/speed) * 10000));
}

Tiro::~Tiro()
{
	existe = false;
}


void Tiro::Update(GameObject* inimigos[]) {
	xpos += speedx;
	ypos += speedy;
	Tile* tile = mapa->getTile(xpos, ypos, 0);
	if (tile) {
		tile = mapa->getTile(xpos, ypos, 0);
		for (int i = 0; i < Game::objQuant; i++) {
			if (xpos > inimigos[i]->xpos && xpos < inimigos[i]->xpos + 64 && ypos > inimigos[i]->ypos && ypos < inimigos[i]->ypos + 64 && inimigos[i]->morto == false) {
				inimigos[i]->morto = true;
				inimigos[i]->Update();
				Tiro::~Tiro();
				return;
			}
		}
		if (tile->getState() == 1) {
			Tiro::~Tiro();
			return;
		}
	}
	else Tiro::~Tiro();
}

void Tiro::UpdateInimigo(GameObject* player)
{
	xpos += speedx;
	ypos += speedy;
	Tile* tile = mapa->getTile(xpos, ypos, 0);
	if (tile) {
		tile = mapa->getTile(xpos, ypos, 0);
		if (xpos > player->xpos && xpos < player->xpos + 64 && ypos > player->ypos && ypos < player->ypos + 64){// && player->morto == false) {
			player->morto = true;
			//player->Update();
			Tiro::~Tiro();
			return;
		}
		if (tile->getState() == 1) {
			Tiro::~Tiro();
			return;
		}
	}
	else Tiro::~Tiro();
}

void Tiro::Render() {
	if (Game::testMode) {
		SDL_SetRenderDrawColor(Game::renderer, 255, 0, 0, 255);
		SDL_RenderDrawLine(Game::renderer, line.x0, line.y0, line.x1, line.y1);
	}
	SDL_SetRenderDrawColor(Game::renderer, 255, 255, 0, 255);
	SDL_RenderDrawLine(Game::renderer, xpos - (speedx * tam), ypos - (speedy * tam), xpos, ypos);
	SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, 255);
}
