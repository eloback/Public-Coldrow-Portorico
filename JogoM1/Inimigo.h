#pragma once
#include "GameObject.h"
#include "Tile.h"
#include "Map.h"
#include "Jogador.h"
#include <vector>
class Inimigo :
	public GameObject
{
public:
	Inimigo(const char* texturesheet, int x, int y);
	~Inimigo();

	void updateFov(Map* mapa, Jogador* player);

private:
	int dov = 3;
	std::vector< std::vector<Tile*> > fov;
	bool inChase = false;
};

