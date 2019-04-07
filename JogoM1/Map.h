#pragma once
#include "Game.h"
#include "GameObject.h"
#include "Tile.h"
//#include "Jogador.h"

class Map
{
public:
	Map();
	//~Map();

	void LoadMap(int arr[20][25]);
	void DrawMap();
	void Collision(GameObject* Player, GameObject* enemy);
	Tile* getTile(int xori, int yorj, bool mode);

private:
	SDL_Texture* woodenfloor;
	SDL_Texture* grass;

	Tile map[20][25];
};

