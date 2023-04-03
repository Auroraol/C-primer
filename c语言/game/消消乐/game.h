#pragma once
#include <SDL.h>
#include<sdl_image.h>

typedef struct
{
	SDL_Window* window;
	SDL_Renderer* renderer;
	bool isRunning;			//��Ϸ�Ƿ�������
}Game;


static Game ggame;

static bool game_init(const char* title, int width, int height)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		SDL_Log("game not init!\n");
		ggame.isRunning = false;
	}

	ggame.window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
	if (!ggame.window)
	{
		SDL_Log("SDL init failed,%s\n", SDL_GetError());
	}

	ggame.renderer = SDL_CreateRenderer(ggame.window, -1, 0);
	if (!ggame.renderer)
	{
		SDL_Log("SDL init failed,%s\n", SDL_GetError());
	}
	ggame.isRunning = true;

	return ggame.isRunning;
}

void gameClear()
{

	SDL_DestroyWindow(ggame.window);
	SDL_DestroyRenderer(ggame.renderer);
	SDL_Quit();
	SDL_Log("game clean!\n");
}


SDL_Texture* textureLoad(const char* fileanme)
{
	int ret = IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
	SDL_Surface* sur = IMG_Load(fileanme);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(ggame.renderer, sur);
	SDL_FreeSurface(sur);

	return tex;
}


//�ж���Ϸ�Ƿ�������
static bool game_running()
{
	return ggame.isRunning;
}

// �ر���Ϸ
static void gamer_Done()
{
	ggame.isRunning = false;
}

