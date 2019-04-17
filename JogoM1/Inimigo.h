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
	Inimigo(const char* texturesheet, int x, int y, Map* mapa, Jogador* player, std::vector<Tile*> patrulha, int tam, int direcao);
	~Inimigo();

	void movimenta();
	void updateFov();
	void detectaFov();
	void wallFov();
	void limpaFov();
	void drawFov();
	void Update();
	void Render();
	void shootWeapon();
	void reloadWeapon();

private:
	vetor line;
	std::vector<Tiro> shoot;
	int ammunition = 30;
	int shootCD = 0;
	bool reloading = false;
	int reloadTime = 0;

	int tamPatrulha;
	std::vector<Tile*> patrulha = { {nullptr} };
	int patrulhaValue = 0;
	Map* mapa = nullptr;
	Jogador* player = nullptr;
	int dov = 5;
	std::vector< std::vector<Tile*> > fov = { {nullptr} };
	bool inChase = false;
};

