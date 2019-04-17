#include "Inimigo.h"
#include <iostream>
#include "TextureManager.h"

Inimigo::Inimigo(const char* texturesheet, int x, int y, Map* mapa, Jogador* player, std::vector<Tile*> patrulha, int tam, int direction) : GameObject(texturesheet, x, y)
{
	srcRect.h = 80;
	srcRect.w = 80;
	dstRect.h = 64;
	dstRect.w = 64;

	fov.resize(dov);
	for (int i = 0; i < dov; i++) {
		fov[i].resize(2 * (i + 1));
	}
	limpaFov();
	this->mapa = mapa;
	this->player = player;
	this->direction = direction;
	this->patrulha = patrulha;
	this->tamPatrulha = tam;
}


Inimigo::~Inimigo()
{
	SDL_DestroyTexture(objTexture);
	fov.~vector();
	patrulha.~vector();
	shoot.~vector();
}

void Inimigo::movimenta()
{
	switch (direction) {
	case 0: 
		if (ypos > patrulha[patrulhaValue]->dst.y) ypos--;
		if (ypos == patrulha[patrulhaValue]->dst.y) patrulhaValue++;
		break;
	case 1:
		if (xpos < patrulha[patrulhaValue]->dst.x) xpos++;
		if (xpos == patrulha[patrulhaValue]->dst.x) patrulhaValue++;
		break;
	case 2:
		if (ypos < patrulha[patrulhaValue]->dst.y) ypos++;
		if (ypos == patrulha[patrulhaValue]->dst.y) patrulhaValue++;
		break;
	case 3:
		if (xpos > patrulha[patrulhaValue]->dst.x) xpos--;
		if (xpos == patrulha[patrulhaValue]->dst.x) patrulhaValue++;
		break;
	}
	if (patrulhaValue >= tamPatrulha) {
		if (direction == 0 || direction == 1) direction += 2;
		else direction -= 2;
		patrulhaValue = 0;
		for (int i = 0; i < tamPatrulha / 2; i++) {
			Tile* aux = patrulha[i];
			patrulha[i] = patrulha[(tamPatrulha - 1) - i];
			patrulha[(tamPatrulha - 1) - i] = aux;
		}
	}
	if (xpos == patrulha[patrulhaValue]->dst.x) {
		if (ypos < patrulha[patrulhaValue]->dst.y) direction = 2;
		else direction = 0;
	}
	else if (ypos == patrulha[patrulhaValue]->dst.y) {
		if (xpos > patrulha[patrulhaValue]->dst.x) direction = 3;
		else direction = 1;
	}
}

void Inimigo::updateFov()
{
	int x = (this->xpos + srcRect.w), y = (ypos + srcRect.h);
	Tile * tile = mapa->getTile(xpos, ypos, 0);
	int i = tile->dst.y / 32;
	int j = tile->dst.x / 32;
	switch (this->direction)
	{
	case 0:
		for (int linha = 0; linha < dov; linha++) {
			for (int coluna = 0 - linha; coluna + linha < (linha + 1) * 2; coluna++) {
				tile = mapa->getTile(j + coluna, i - (1 + linha), 1);;
				if (tile != nullptr){
					fov[linha][coluna + linha] = tile;
					if (tile->getState() == 0) {
						fov[linha][coluna + linha]->setState(2);
					}
				}
			}
		}
		break;
	case 1:
		for (int coluna = 0; coluna < dov; coluna++) {
			for (int linha = 0 - coluna; linha + coluna < (coluna + 1) * 2; linha++) {
				tile = mapa->getTile(j + (2 + coluna), i + linha, 1);
				if (tile != nullptr){
					fov[coluna][linha + coluna] = tile;
					if (tile->getState() == 0) {
						fov[coluna][linha + coluna]->setState(2);
					}
				}
			}
		}
		break;
	case 2:
		for (int linha = 0; linha < dov; linha++) {
			for (int coluna = 0 - linha; coluna + linha < (linha + 1) * 2; coluna++) {
				tile = mapa->getTile(j + coluna, i + (2 + linha), 1);
				if (tile != nullptr){
					fov[linha][coluna + linha] = tile;
					if (tile->getState() == 0) {
						fov[linha][coluna + linha]->setState(2);
					}
				}
			}
		}
		break;
	case 3:
		for (int coluna = 0; coluna < dov; coluna++) {
			for (int linha = 0 - coluna; linha + coluna < (coluna + 1) * 2; linha++) {
				tile = mapa->getTile(j - (1 + coluna), i + linha, 1);
				if(tile != nullptr){
					fov[coluna][linha + coluna] = tile;
					if (tile->getState() == 0) {
						fov[coluna][linha + coluna]->setState(2);
					}
				}
			}
		}
		break;
	default:
		break;
	}
	wallFov();
	detectaFov();
}

void Inimigo::detectaFov()
{
	switch (this->direction)
	{
	case 0:
		for (int linha = 0; linha < dov; linha++) {
			for (int coluna = 0 - linha; coluna + linha < (linha + 1) * 2; coluna++) {
				Tile* tile = fov[linha][coluna + linha];
				if (tile->getState() == 2) {
					inChase = player->detectado(fov[linha][coluna + linha]->dst.x, fov[linha][coluna + linha]->dst.y);
					if (inChase) return;
				}
			}
		}
		break;
	case 1:
		for (int coluna = 0; coluna < dov; coluna++) {
			for (int linha = 0 - coluna; linha + coluna < (coluna + 1) * 2; linha++) {
				Tile* tile = fov[coluna][linha + coluna];
				if (tile->getState() == 2) {
					inChase = player->detectado(fov[coluna][linha + coluna]->dst.x, fov[coluna][linha + coluna]->dst.y);
					if (inChase) return;
				}
			}
		}
		break;
	case 2:
		for (int linha = 0; linha < dov; linha++) {
			for (int coluna = 0 - linha; coluna + linha < (linha + 1) * 2; coluna++) {
				Tile* tile = fov[linha][coluna + linha];
				if (tile->getState() == 2) {
					inChase = player->detectado(fov[linha][coluna + linha]->dst.x, fov[linha][coluna + linha]->dst.y);
					if (inChase) return;
				}
			}
		}
		break;
	case 3:
		for (int coluna = 0; coluna < dov; coluna++) {
			for (int linha = 0 - coluna; linha + coluna < (coluna + 1) * 2; linha++) {
				Tile* tile = fov[coluna][linha + coluna];
				if (tile->getState() == 2) {
					inChase = player->detectado(fov[coluna][linha + coluna]->dst.x, fov[coluna][linha + coluna]->dst.y);
					if (inChase) return;
				}
			}
		}
		break;
	default:
		break;
	}
}

void Inimigo::limpaFov()
{
	switch (this->direction)
	{
	case 0:
		for (int linha = 0; linha < dov; linha++) {
			for (int coluna = 0 - linha; coluna + linha < (linha + 1) * 2; coluna++) {
				if (fov[linha][coluna + linha] != nullptr) fov[linha][coluna + linha]->returnState();
				fov[linha][coluna + linha] = nullptr;
			}
		}
		break;
	case 1:
		for (int coluna = 0; coluna < dov; coluna++) {
			for (int linha = 0 - coluna; linha + coluna < (coluna + 1) * 2; linha++) {
				if (fov[coluna][linha + coluna] != nullptr) fov[coluna][linha + coluna]->returnState();
				fov[coluna][linha + coluna] = nullptr;
			}
		}
		break;
	case 2:
		for (int linha = 0; linha < dov; linha++) {
			for (int coluna = 0 - linha; coluna + linha < (linha + 1) * 2; coluna++) {
				if (fov[linha][coluna + linha] != nullptr) fov[linha][coluna + linha]->returnState();
				fov[linha][coluna + linha] = nullptr;
			}
		}
		break;
	case 3:
		for (int coluna = 0; coluna < dov; coluna++) {
			for (int linha = 0 - coluna; linha + coluna < (coluna + 1) * 2; linha++) {
				if (fov[coluna][linha + coluna] != nullptr) fov[coluna][linha + coluna]->returnState();
				fov[coluna][linha + coluna] = nullptr;
			}
		}
		break;
	default:
		break;
	}
}

void Inimigo::wallFov()
{
	switch (this->direction)
	{
	case 0:
		for (int linha = 0; linha < dov - 1; linha++) {
			for (int coluna = 0 - linha; coluna + linha < (linha + 1) * 2; coluna++) {
				Tile* tile = fov[linha][coluna + linha];
				if (tile != nullptr && (tile->getState() == 1 || tile->getState() == 3)) {
					fov[linha + 1][coluna + linha]->returnState();
					fov[linha + 1][coluna + linha + 1]->returnState();
					fov[linha + 1][coluna + linha + 2]->returnState();
					if (fov[linha + 1][coluna + linha]->getState() == 0) fov[linha + 1][coluna + linha]->setState(3);
					if (fov[linha + 1][coluna + linha + 1]->getState() == 0) fov[linha + 1][coluna + linha + 1]->setState(3);
					if (fov[linha + 1][coluna + linha + 2]->getState() == 0) fov[linha + 1][coluna + linha + 2]->setState(3);
				}
			}
		}
		break;
	case 1:
		for (int coluna = 0; coluna < dov - 1; coluna++) {
			for (int linha = 0 - coluna; linha + coluna < (coluna + 1) * 2; linha++) {
				Tile* tile = fov[coluna][linha + coluna];
				if (tile != nullptr && (tile->getState() == 1 || tile->getState() == 3)) {
					fov[coluna + 1][linha + coluna]->returnState();
					fov[coluna + 1][linha + coluna + 1]->returnState();
					fov[coluna + 1][linha + coluna + 2]->returnState();
					if (fov[coluna + 1][linha + coluna]->getState() == 0) fov[coluna + 1][linha + coluna]->setState(3);
					if (fov[coluna + 1][linha + coluna + 1]->getState() == 0) fov[coluna + 1][linha + coluna + 1]->setState(3);
					if (fov[coluna + 1][linha + coluna + 2]->getState() == 0) fov[coluna + 1][linha + coluna + 2]->setState(3);
				}
			}
		}
		break;
	case 2:
		for (int linha = 0; linha < dov - 1; linha++) {
			for (int coluna = 0 - linha; coluna + linha < (linha + 1) * 2; coluna++) {
				Tile* tile = fov[linha][coluna + linha];
				if (tile != nullptr && (tile->getState() == 1 || tile->getState() == 3)) {
					fov[linha + 1][coluna + linha]->returnState();
					fov[linha + 1][coluna + linha + 1]->returnState();
					fov[linha + 1][coluna + linha + 2]->returnState();
					if (fov[linha + 1][coluna + linha]->getState() == 0) fov[linha + 1][coluna + linha]->setState(3);
					if (fov[linha + 1][coluna + linha + 1]->getState() == 0) fov[linha + 1][coluna + linha + 1]->setState(3);
					if (fov[linha + 1][coluna + linha + 2]->getState() == 0) fov[linha + 1][coluna + linha + 2]->setState(3);
				}
			}
		}
		break;
	case 3:
		for (int coluna = 0; coluna < dov - 1; coluna++) {
			for (int linha = 0 - coluna; linha + coluna < (coluna + 1) * 2; linha++) {
				Tile* tile = fov[coluna][linha + coluna];
				if (tile != nullptr && (tile->getState() == 1 || tile->getState() == 3)) {
					fov[coluna + 1][linha + coluna]->returnState();
					fov[coluna + 1][linha + coluna + 1]->returnState();
					fov[coluna + 1][linha + coluna + 2]->returnState();
					if (fov[coluna + 1][linha + coluna]->getState() == 0) fov[coluna + 1][linha + coluna]->setState(3);
					if (fov[coluna + 1][linha + coluna + 1]->getState() == 0) fov[coluna + 1][linha + coluna + 1]->setState(3);
					if (fov[coluna + 1][linha + coluna + 2]->getState() == 0) fov[coluna + 1][linha + coluna + 2]->setState(3);
				}
			}
		}
		break;
	default:
		break;
	}
}

void Inimigo::Update()
{
	dstRect.x = xpos;
	line.x0 = dstRect.x;
	dstRect.y = ypos;
	line.y0 = dstRect.y;
	limpaFov();

	if (!inChase && !morto) {
		int dir = direction;
		if (dir == 2) dir = 3;
		else if (dir == 3) dir = 2;
		srcRect.y = 80 * dir;

		if (this->tamPatrulha) {
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

		if(this->tamPatrulha) movimenta();
		updateFov();
	}
	else if (morto) limpaFov();
	else {
		shootCD++;
		if (shootCD == 10) {
			shootWeapon();
			shootCD = 0;
		}
	}
	for (int i = 0; i < shoot.size(); i++) {
		if (shoot[i].existe == true) shoot[i].UpdateInimigo(player);
		else shoot.erase(shoot.begin() + i);
	}
	if (reloading == true) reloadWeapon();
}

void Inimigo::Render() {
	TextureManager::Draw(objTexture, srcRect, dstRect);
	for (int i = 0; i < shoot.size(); i++) {
		if (shoot[i].existe == true) shoot[i].Render();
	}
}

void Inimigo::shootWeapon() {
	if (ammunition != 0) {

		switch (direction) //mudar a posição inicial do tiro para a mão do inimigo
		{
		case 0:
			line.x0 += 64;
			line.y0 += 32;
			break;
		case 1:
			line.x0 += 32;
			line.y0 += 64;
			break;
		case 2:
			line.x0 += 0;
			line.y0 += 0;
			break;
		case 3:
			line.x0 += 0;
			line.y0 += 32;
			break;
		default:
			break;
		}

		line.x1 = player->xpos+32;
		line.y1 = player->ypos+32;
		line.calculaModulo();
		shoot.push_back(Tiro(line, mapa));
		ammunition--;
	}
	else reloading = true;
}

void Inimigo::reloadWeapon() {
	reloadTime++;
	if (reloadTime == 60) {
		std::cout << "Arma Recarregando!" << std::endl;
		ammunition = 30;
		reloadTime = 0;
		reloading = false;
	}
}