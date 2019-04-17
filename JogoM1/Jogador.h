#pragma once
#include "GameObject.h"
#include "Map.h"
#include <math.h>
#include "Tiro.h"
#include <vector>

class Jogador :
	public GameObject
{
public:
	Jogador(const char* texturesheet, int x, int y);
	~Jogador();

	void Movimenta();
	void Update(GameObject* inimigos[]);
	void Render();
	void UpdateDirection();
	void Collision(int tileX, int tileY);
	bool detectado(int tileX, int tileY);
	void vitoria(int tileX, int tileY);
	void shootWeapon(Map* mapa);
	void reloadWeapon();

	int mouseX, mouseY;
	bool isMoving = false;
	bool movingLeft = false;
	bool movingRight = false;
	bool movingUp = false;
	bool movingDown = false;
	bool reloading = false;

private:
	vetor line;
	std::vector<Tiro> shoot;
	int ammunition = 12;
	int reloadTime = 0;

	int oldX, oldY;
	SDL_Texture* crosshair;
};

