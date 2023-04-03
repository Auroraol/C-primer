#pragma once
#include <SDL.h>
#include<sdl_image.h>

//��SDL�ӿڷ�װ������ʹ��
typedef struct
{
	SDL_Window* window;
	SDL_Renderer* render;
	bool isRunning;			//��Ϸ�Ƿ�������
}Game;

static Game gGame;

// ��ʼ��sdl
static bool game_init(const char* title, int width, int height)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		SDL_Log("game not init!\n");
		gGame.isRunning = false;
	}

	//��������
	gGame.window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
	if (!gGame.window)
	{
		SDL_Log("SDL init failed,%s\n", SDL_GetError());
	}

	// ������Ⱦ
	gGame.render = SDL_CreateRenderer(gGame.window, -1, 0);
	if (!gGame.render)
	{
		SDL_Log("SDL init failed,%s\n", SDL_GetError());
	}
	gGame.isRunning = true;

	return gGame.isRunning;
}


//����SDL
static void game_clean()
{
	SDL_DestroyWindow(gGame.window);
	SDL_DestroyRenderer(gGame.render);
	SDL_Quit();
	SDL_Log("game clean!\n");
}

// textureʹ��
SDL_Texture* loadTexture(const char* fileanme)
{
	//����ͼƬ
	SDL_Surface* mmSfc = SDL_LoadBMP(fileanme);
	//��Surfaceת��Texture
	SDL_Texture* tex = SDL_CreateTextureFromSurface(gGame.render, mmSfc);
	//�ͷŵ�surface
	SDL_FreeSurface(mmSfc);
	return tex;
}

//�ж���Ϸ�Ƿ�������
static bool game_running()
{
	return gGame.isRunning;
}

// �ر���Ϸ
static void gamer_Done()
{
	gGame.isRunning = false;
}
