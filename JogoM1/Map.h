#pragma once
#include "Game.h"
#include "GameObject.h"
#include "Tile.h"
//#include "Jogador.h"

class Map
{
public:
	Map(const char* mapa);
	~Map();

	void LoadMap(int arr[20][25]);
	void DrawMap();
	void Collision(GameObject* Player, GameObject* enemy[]);
	Tile* getTile(int xori, int yorj, bool mode);

	Tile map[20][25];
};

