#include "Game.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "Map.h"
#include "Jogador.h"
#include "Inimigo.h"
#include <vector>

Jogador* player;
const int Game::objQuant = 6;
GameObject* objetos[Game::objQuant];
Map* map;
SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;
bool Game::testMode = false;

Game::Game()
{}

Game::~Game()
{
	player->~Jogador();
	delete player;
	for (int i = 0; i < objQuant; i++) {
		objetos[i]->~GameObject();
	}
	map->~Map();
	delete map;
}

void Game::init(const char* title, int width, int height, bool fullscreen)
{
	int flags = 0;

	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		}

		isRunning = true;
	}
	map = new Map("Assets/Mapas/Mapa01.txt");

	player = new Jogador("Assets/playersheet.png", 32, 32);
	//enemy = new Inimigo("Assets/enemy.png", 32*6, 32*6, map, player);//mapa deve criar inimigos com base em um vector carregado a partir do txt do mapa

	int x[6] = { 22, 8, 4, 22, 11, 13 }, y[6] = { 2, 6, 17, 15, 9, 17 };
	int tam[6] = { 14,14,10,19,0, 0 };
	std::vector< std::vector<int> > direcaoArray;
	direcaoArray.resize(Game::objQuant);
	for (int i = 0; i < Game::objQuant; i++) {
		direcaoArray[i].resize(tam[i]);
	}
	int direcao[6] = { 3, 1, 0, 3, 2, 0 };
	/*direcaoArray[0] = { {{3}} };
	direcaoArray[1] = { {{1}} };
	direcaoArray[2] = { {{0}} };
	direcaoArray[3] = { {{3}} };
	direcaoArray[4] = { {{-1}} };
	direcaoArray[5] = { {{-1}} };*/
	for (int i = 0; i < objQuant; i++) {
		for (int j = 0; j < tam[i]; j++) {
			direcaoArray[i][j] = direcao[i];
		}
	}

	std::vector<std::vector<Tile*>> patrulha;
	patrulha.resize(objQuant);
	for (int i = 0; i < objQuant; i++) {
		Tile* tileAtual = tileAtual = map->getTile(x[i], y[i], 1);
		for (int j = 0; j < tam[i]; j++) {
			if(j == 0) tileAtual = map->getTile(x[i], y[i], 1);
			else tileAtual = patrulha[i][j - 1];
			switch (direcaoArray[i][j]) {
			case 0:
				patrulha[i].push_back(map->getTile(tileAtual->dst.x, tileAtual->dst.y - 32, 0));
				break;
			case 1:
				patrulha[i].push_back(map->getTile(tileAtual->dst.x + 32, tileAtual->dst.y, 0));
				break;
			case 2:
				patrulha[i].push_back(map->getTile(tileAtual->dst.x, tileAtual->dst.y + 32, 0));
				break;
			case 3:
				patrulha[i].push_back(map->getTile(tileAtual->dst.x - 32, tileAtual->dst.y, 0));
				break;
			default:
				break;
			}
		}
		objetos[i] = new Inimigo("Assets/enemysheet.png", 32 * x[i], 32 * y[i], map, player, patrulha[i], patrulha[i].size(), direcao[i]);
	}
	
	patrulha.~vector();
	direcaoArray.~vector();

	/*objetos[0] = new Inimigo("Assets/enemy.png", 32 * 6, 32 * 6, map, player);
	objetos[1] = new Inimigo("Assets/enemy.png", 32 * 9, 32 * 12, map, player);*/
}

void Game::handleEvents()
{

	while (SDL_PollEvent(&event)) {

		switch (event.type)
		{
		case SDL_QUIT:
			isRunning = false;
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (event.button.button == SDL_BUTTON_LEFT) {
				player->shootWeapon(map);
			}
			break;
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_a) {
				player->isMoving = true;
				player->movingLeft = true;
			}
			else if (event.key.keysym.sym == SDLK_RIGHT || event.key.keysym.sym == SDLK_d) {
				player->isMoving = true;
				player->movingRight = true;
			}
			else if (event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_w) {
				player->isMoving = true;
				player->movingUp = true;
			}
			else if (event.key.keysym.sym == SDLK_DOWN || event.key.keysym.sym == SDLK_s) {
				player->isMoving = true;
				player->movingDown = true;
			}
			else if (event.key.keysym.sym == SDLK_SPACE) {
				Game::testMode = !Game::testMode;
			}
			else if (event.key.keysym.sym == SDLK_r) {
				player->reloading = true;
			}

			break;
		case SDL_KEYUP:
			if (event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_a) {

				player->movingLeft = false;
			}
			else if (event.key.keysym.sym == SDLK_RIGHT || event.key.keysym.sym == SDLK_d) {
				player->movingRight = false;
			}
			else if (event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_w) {

				player->movingUp = false;
			}
			else if (event.key.keysym.sym == SDLK_DOWN || event.key.keysym.sym == SDLK_s) {

				player->movingDown = false;
			}
			if ((!player->movingLeft && !player->movingRight && !player->movingUp && !player->movingDown)) player->isMoving = false;
		default:
			event.type = NULL;
			break;
		}
	}
}

void Game::update()
{
	player->Update(objetos);
	map->Collision(player, objetos);
	for (int i = 0; i < objQuant; i++) {
		if(!objetos[i]->morto) objetos[i]->Update();
	}
	if (player->morto == true ) {
		isRunning = false;
	}
}

void Game::render()
{
	SDL_RenderClear(renderer);
	map->DrawMap();
	for (int i = 0; i < objQuant; i++) {
		if (!objetos[i]->morto) objetos[i]->Render();
	}
	player->Render();
	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	this->isRunning = false;
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	this->~Game();
	SDL_Quit();
	//delete this;
}