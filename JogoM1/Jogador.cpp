#include "Jogador.h"
#include <iostream>
#include "TextureManager.h"

Jogador::Jogador(const char* texturesheet, int x, int y) : GameObject(texturesheet, x, y) {
	crosshair = TextureManager::LoadTexture("Assets/crosshair.png");
	line.x0 = x;
	line.y0 = y;
}

Jogador::~Jogador()
{
	SDL_DestroyTexture(objTexture);
	SDL_DestroyTexture(crosshair);
	shoot.~vector();
}

void Jogador::Movimenta()
{
	oldX = xpos;
	oldY = ypos;

	if (movingLeft) xpos -= speed;

	if (movingRight) xpos += speed;

	if (movingUp) ypos -= speed;

	if (movingDown) ypos += speed;
}

void Jogador::Update(GameObject* inimigos[])
{
	if (isMoving) {
		Movimenta();
		animationFrame++;
		if (animationFrame < 20) {
			srcRect.x = 0;
		}
		else if (animationFrame < 40) {
			srcRect.x = 80;
		}
		else if (animationFrame < 60) {
			srcRect.x = 160;
		}
		if (animationFrame > 60) animationFrame = 0;
	}
	
	for (int i = 0; i < shoot.size(); i++) {
		if (shoot[i].existe == true) shoot[i].Update(inimigos);
		else shoot.erase(shoot.begin()+i);
	}

	dstRect.x = xpos;
	dstRect.y = ypos;

	line.x0 = dstRect.x;
	line.y0 = dstRect.y;

	UpdateDirection();

	if (reloading == true) reloadWeapon();
}

void Jogador::Render()
{
	TextureManager::Draw(objTexture, srcRect, dstRect);
	if (Game::testMode) {
		SDL_SetRenderDrawColor(Game::renderer, 0, 255, 0, 255);
		SDL_RenderDrawRect(Game::renderer, &dstRect);
		SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, 255);
	}
	SDL_Rect srcMouse = { 0, 0, 32, 32 };
	SDL_Rect dstMouse = { mouseX - 32, mouseY - 32, 64, 64 };
	TextureManager::Draw(crosshair, srcMouse, dstMouse);
	for (int i = 0; i < shoot.size(); i++) {
		if (shoot[i].existe == true) shoot[i].Render();
	}
}

void Jogador::UpdateDirection() {
	SDL_GetMouseState(&mouseX, &mouseY);
	if (mouseY <= ypos && (mouseX >= xpos && mouseX <= (xpos + dstRect.w))) {
		direction = 0;
		srcRect.y = 80 * direction;
		line.y0 += 0; /// alterar a posição inicial da bala para a mão do jogador
		line.x0 += 48;
	}
	else if (mouseY <= ypos && mouseX >= (xpos + dstRect.w)) {
		direction = 1;
		srcRect.y = 80 * direction;
		line.y0 += 40;
		line.x0 += 58;
	}
	else if (mouseX >= (xpos + dstRect.w) && (mouseY >= ypos && mouseY <= (ypos + dstRect.h))) {
		direction = 2;
		srcRect.y = 80 * direction;
		line.y0 += 54;
		line.x0 += 58;
	}
	else if (mouseY >= (ypos + dstRect.h) && mouseX >= (xpos + dstRect.w)) {
		direction = 3;
		srcRect.y = 80 * direction;
		line.y0 += 80;
		line.x0 += 64;
	}
	else if (mouseY >= (ypos + dstRect.h) && (mouseX >= xpos && mouseX <= (xpos + dstRect.w))) {
		direction = 4;
		srcRect.y = 80 * direction;
		line.y0 += 64;
		line.x0 += 16;
	}
	else if (mouseY >= (ypos + dstRect.h) && mouseX <= (xpos + dstRect.w)) {
		direction = 5;
		srcRect.y = 80 * direction;
		line.y0 += 44;
		line.x0 += 4;
	}
	else if (mouseX <= xpos && (mouseY >= ypos && mouseY <= (ypos + dstRect.h))) {
		direction = 6;
		srcRect.y = 80 * direction;
		line.y0 += 8;
		line.x0 += 8;
	}
	else if (mouseY <= ypos && mouseX <= (xpos + dstRect.w)) {
		direction = 7;
		srcRect.y = 80 * direction;
		line.y0 += 4;
		line.x0 += 40;
	}
}

void Jogador::Collision(int tileX, int tileY) {
	if (ypos + 64 > tileY && ypos < tileY + 32 && xpos + 64 >= tileX && xpos < tileX + 32) {
		xpos = oldX;
		ypos = oldY;
	}
}

bool Jogador::detectado(int tileX, int tileY){
	if (ypos + 64 >= tileY && ypos < tileY + 32 && xpos + 64 >= tileX && xpos < tileX + 32) {
		return true;
	}
	else return false;
}

void Jogador::vitoria(int tileX, int tileY) {
	if (ypos + 64 > tileY && ypos < tileY + 32 && xpos + 64 >= tileX && xpos < tileX + 32) {
		morto = true;
	}
}

void Jogador::shootWeapon(Map * mapa) {
	SDL_GetMouseState(&mouseX, &mouseY);
	if (ammunition != 0 && reloading == false) {
		line.x1 = mouseX;
		line.y1 = mouseY;
		line.calculaModulo();
		shoot.push_back(Tiro(line, mapa));
		ammunition--;
	}
	else reloading = true;
}

void Jogador::reloadWeapon() {
	reloadTime++;
	if (reloadTime == 60) {
		ammunition = 12;
		reloadTime = 0;
		reloading = false;
	}
}
