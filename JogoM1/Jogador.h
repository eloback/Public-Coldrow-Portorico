#pragma once
#include "GameObject.h"

class Jogador :
	public GameObject
{
public:
	Jogador(const char* texturesheet, int x, int y);
	~Jogador();

	void Movimenta();
	void Update();
	void Render();
	void UpdateDirection();
	void Collision(int tileX, int tileY);
	bool detectado(int tileX, int tileY);
	void shootWeapon();
	void reloadWeapon();

	int mouseX, mouseY;
	bool isMoving = false;
	bool movingLeft = false;
	bool movingRight = false;
	bool movingUp = false;
	bool movingDown = false;
private:
	int animationFrame = 0;
	int ammunition = 12;
	int oldX, oldY;
	SDL_Texture* crosshair;
	SDL_Texture* shoot;
};

