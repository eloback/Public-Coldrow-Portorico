#include "Game.h"

Game* game = nullptr;

int main(int argc, char* argv[])
{
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;

	game = new Game();
	game->init("Coldrow Portorico", 800, 640, false);
	SDL_ShowCursor(SDL_DISABLE);

	while (game->running())
	{
		frameStart = SDL_GetTicks();

		game->handleEvents();
		if(game->running()) game->update();
		if (game->running()) {
			game->render();

			frameTime = SDL_GetTicks() - frameStart;

			if (frameDelay > frameTime) {
				SDL_Delay(frameDelay - frameTime);
			}
		}
	}
	game->clean();
	return 0;
}