#include "Map.h"
#include <fstream> 
#include <iostream>


Map::Map(const char* mapa)
{
	std::ifstream arquivo(mapa, std::ifstream::in);
	int lvl[20][25];
	for (int linha = 0; linha < 20; linha++) {
		for (int coluna = 0; coluna < 25; coluna++) {
			arquivo >> lvl[linha][coluna];
		}
	}
	LoadMap(lvl);		
}

Map::~Map()
{
	for (int linha = 0; linha < 20; linha++) {
		for (int coluna = 0; coluna < 25; coluna++) {
			map[linha][coluna].~Tile();
		}
	}
}


void Map::LoadMap(int arr[20][25])
{
	for (int linha = 0; linha < 20; linha++) {
		for (int coluna = 0; coluna < 25; coluna++) {
			map[linha][coluna].setState(arr[linha][coluna]);
			map[linha][coluna].dst.x = coluna * 32;
			map[linha][coluna].dst.y = linha * 32;
		}
	}
}

void Map::DrawMap() {
	for (int linha = 0; linha < 20; linha++) {
		for (int coluna = 0; coluna < 25; coluna++) {
			map[linha][coluna].draw();
		}
	}
}

void Map::Collision(GameObject* player, GameObject* enemy[])
{
	int ti=2, tj=2;
	int pi, pj;

	pi = player->ypos / (640 / 20);
	pj = player->xpos / (800 / 25);

	// caso afete mais de dois tiles ao mesmo tempo
	if ((640 / 20) * pi != player->ypos) ti ++;
	if ((800 / 25) * pj != player->xpos) tj ++;

	for (int i=0; i < ti; i++) {
		for (int j = 0; j < tj; j++) {
			int linha = pi + i, coluna = pj + j;
			bool enemycollision = false;

			for (int i = 0; i < Game::objQuant; i++) {
				if ((coluna * 32 >= enemy[i]->xpos && coluna * 32 < enemy[i]->xpos + 64)) {
					if ((linha * 32 >= enemy[i]->ypos && linha * 32 < enemy[i]->ypos + 64) && enemy[i]->morto == false) enemycollision = true;
				}
			}
			if (map[linha][coluna].getState() == 1 || enemycollision) player->Collision(coluna * 32, linha * 32);
			if (map[linha][coluna].getState() == 5) player->vitoria(coluna * 32, linha * 32 );
		}
	}

}

Tile* Map::getTile(int x, int y, bool mode)
{
	if (mode) {
		if (x > 24 || x < 0 || y > 20 || y < 0) return nullptr;
		return &map[y][x];
	}
	else {
		int pi = y / (640 / 20), pj = x / (800 / 25);
		if (x > 800 || x < 0 || y > 640 || y < 0) return nullptr;
		return &map[pi][pj];
	}
}