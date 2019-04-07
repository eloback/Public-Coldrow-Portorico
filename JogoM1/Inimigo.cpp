#include "Inimigo.h"
#include <iostream>


Inimigo::Inimigo(const char* texturesheet, int x, int y) : GameObject(texturesheet, x, y)
{
	fov.resize(dov);
	for (int i = 0; i < dov; i++) {
		fov[i].resize(2 * (i + 1));
	}
}


Inimigo::~Inimigo()
{
}

void Inimigo::updateFov(Map* mapa, Jogador* player)
{
	int x = (xpos + srcRect.w), y = (ypos + srcRect.h);
	Tile* inimigoTile = mapa->getTile(xpos, ypos, 0);
	int i = inimigoTile->dst.y / 32;
	int j = inimigoTile->dst.x / 32;
	switch (direction)
	{
	case 0:
		for (int linha = 0; linha < dov; linha++) {
			for (int coluna = 0 - linha; coluna + linha < (linha + 1) * 2; coluna++) {
				fov[linha][coluna + linha] = mapa->getTile(j + coluna, i - (1 + linha), 1);
				inChase = player->detectado(fov[linha][coluna + linha]->dst.x, fov[linha][coluna + linha]->dst.y);
				if(Game::testMode) fov[linha][coluna + linha]->setState(2);
			}
		}
		break;
	case 1:
		for (int coluna = 0; coluna < dov; coluna++) {
			for (int linha = 0-coluna; linha+coluna < (coluna + 1) * 2; linha++) {
				fov[coluna][linha+coluna] = mapa->getTile(j + (2 + coluna), i+linha, 1);
				inChase = player->detectado(fov[coluna][linha + coluna]->dst.x, fov[coluna][linha + coluna]->dst.y);
				if (Game::testMode) fov[coluna][linha+coluna]->setState(2);
			}
		}
		break;
	case 2:
		for (int linha = 0; linha < dov; linha++) {
			for (int coluna = 0 - linha; coluna + linha < (linha + 1) * 2; coluna++) {
				fov[linha][coluna + linha] = mapa->getTile(j + coluna, i + (2 + linha), 1);
				inChase = player->detectado(fov[linha][coluna + linha]->dst.x, fov[linha][coluna + linha]->dst.y);
				if (Game::testMode) fov[linha][coluna + linha]->setState(2);
			}
		}
		break;
	case 3:
		for (int coluna = 0; coluna < dov; coluna++) {
			for (int linha = 0 - coluna; linha + coluna < (coluna + 1) * 2; linha++) {
				fov[coluna][linha + coluna] = mapa->getTile(j - (1 + coluna), i + linha, 1);
				inChase = player->detectado(fov[coluna][linha + coluna]->dst.x, fov[coluna][linha + coluna]->dst.y);
				if (Game::testMode) fov[coluna][linha + coluna]->setState(2);
			}
		}
		break;
	default:
		break;
	}
}
