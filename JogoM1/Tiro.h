#pragma once
#include "Game.h"
#include "Map.h"

class Tiro
{
public:
	Tiro(vetor line, Map* mapa);
	~Tiro();
	void Update(GameObject* inimigos[]);
	void UpdateInimigo(GameObject* player);
	void Render();

	bool existe = false;
private:
	int speed = 16;
	Map* mapa;
	int tam = 3;
	float xpos, ypos;
	vetor line;
	float speedx, speedy;
};

