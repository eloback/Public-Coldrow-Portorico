#include "Game.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "Map.h"
#include "Jogador.h"
#include "Inimigo.h"

Jogador* player;
Inimigo* enemy;
Map* map;
SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;
bool Game::testMode = true;

Game::Game()
{}

Game::~Game()
{}

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
	map = new Map();
	player = new Jogador("Assets/playersheet.png", 0, 0);
	enemy = new Inimigo("Assets/enemy.png", 32*6, 32*6);

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
				player->shootWeapon();
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
	enemy->Update();
	player->Update();
	map->Collision(player, enemy);
	enemy->updateFov(map, player);
}

void Game::render()
{
	SDL_RenderClear(renderer);
	map->DrawMap();
	enemy->Render();
	player->Render();
	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}