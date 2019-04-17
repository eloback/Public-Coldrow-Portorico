#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include <iostream>

struct vetor
{
	float x0;
	float x1;
	float y0;
	float y1;
	float modulo;

	void calculaModulo() {
		modulo = std::sqrt((x0 - x1) * (x0 - x1) + (y0 - y1) * (y0 - y1));
		//return std::sqrt(j * j + i * i);
	}
};

class Game
{
public:
	Game();
	~Game();

	void init(const char* title, int width, int height, bool fullscreen);

	void handleEvents();
	void update();
	bool running() { return isRunning; }
	void render();
	void clean();

	static SDL_Renderer* renderer;
	static SDL_Event event;
	static bool testMode;
	static const int objQuant;

private:
	bool isRunning = false;
	int cnt = 0;
	SDL_Window *window = nullptr;
};