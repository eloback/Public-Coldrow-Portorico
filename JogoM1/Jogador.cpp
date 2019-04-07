#include "Jogador.h"
#include <iostream>
#include "TextureManager.h"

Jogador::Jogador(const char* texturesheet, int x, int y) : GameObject(texturesheet, x, y) {
	crosshair = TextureManager::LoadTexture("Assets/crosshair.png");
	shoot = TextureManager::LoadTexture("Assets/shoot.png");
	srcRect = { 0, 0, 80, 80 };
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

void Jogador::Update()
{
	if (isMoving) {
		Movimenta();
		animationFrame++;
		if (animationFrame < 20) {
			srcRect.x = 0;
		}
		else if(animationFrame < 40){
			srcRect.x = 80;
		}
		else if (animationFrame < 60) {
			srcRect.x = 160;
		}
		if (animationFrame > 60) animationFrame = 0;
	}
	UpdateDirection();

	dstRect.x = xpos;
	dstRect.y = ypos;
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
	SDL_Rect dstMouse = { mouseX-32, mouseY-32, 64, 64 };
	TextureManager::Draw(crosshair, srcMouse, dstMouse);
}

void Jogador::UpdateDirection() {
	SDL_GetMouseState(&mouseX, &mouseY);
	if (mouseY <= ypos && (mouseX >= xpos && mouseX <= (xpos + dstRect.w))) {
		direction = 0;
		srcRect.y = 80 * direction;
	}
	else if(mouseY <= ypos && mouseX >= (xpos + dstRect.w)){
		direction = 1;
		srcRect.y = 80 * direction;
	}
	else if (mouseX >= (xpos + dstRect.w) && (mouseY >= ypos && mouseY <= (ypos + dstRect.h))) {
		direction = 2;
		srcRect.y = 80 * direction;
	}
	else if (mouseY >= (ypos + dstRect.h) && mouseX >= (xpos + dstRect.w)) {
		direction = 3;
		srcRect.y = 80 * direction;
	}
	else if (mouseY >= (ypos + dstRect.h) && (mouseX >= xpos && mouseX <= (xpos + dstRect.w))) {
		direction = 4;
		srcRect.y = 80 * direction;
	}
	else if (mouseY >= (ypos + dstRect.h) && mouseX <= (xpos + dstRect.w)) {
		direction = 5;
		srcRect.y = 80 * direction;
	}
	else if (mouseX <= xpos && (mouseY >= ypos && mouseY <= (ypos + dstRect.h))) {
		direction = 6;
		srcRect.y = 80 * direction;
	}
	else if (mouseY <= ypos && mouseX <= (xpos + dstRect.w)) {
		direction = 7;
		srcRect.y = 80 * direction;
	}
}

void Jogador::Collision(int tileX, int tileY) {
	if (ypos+64 >= tileY && ypos <= tileY+32 && xpos + 64 >= tileX && xpos <= tileX + 32) {
		xpos = oldX;
		ypos = oldY;
	}
}

bool Jogador::detectado(int tileX, int tileY)
{
	if (ypos + 64 >= tileY && ypos <= tileY + 32 && xpos + 64 >= tileX && xpos <= tileX + 32) {
		return true;
	}
	return false;
}

void Jogador::shootWeapon() {
	if (ammunition != 0) {
		std::cout << ammunition<< std::endl;
		ammunition--;
	}
	else reloadWeapon();
}

void Jogador::reloadWeapon() {
	std::cout << "Arma Recarregando!" << std::endl;
	ammunition = 12;
}
