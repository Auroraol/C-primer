#pragma once
#include <SDL.h>
#include<sdl_image.h>

//把SDL接口封装，便于使用
typedef struct
{
	SDL_Window* window;
	SDL_Renderer* render;
	bool isRunning;			//游戏是否在运行
}Game;

static Game gGame;

// 初始化sdl
static bool game_init(const char* title, int width, int height)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		SDL_Log("game not init!\n");
		gGame.isRunning = false;
	}

	//创建窗口
	gGame.window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
	if (!gGame.window)
	{
		SDL_Log("SDL init failed,%s\n", SDL_GetError());
	}

	// 创建渲染
	gGame.render = SDL_CreateRenderer(gGame.window, -1, 0);
	if (!gGame.render)
	{
		SDL_Log("SDL init failed,%s\n", SDL_GetError());
	}
	gGame.isRunning = true;

	return gGame.isRunning;
}


//清理SDL
static void game_clean()
{
	SDL_DestroyWindow(gGame.window);
	SDL_DestroyRenderer(gGame.render);
	SDL_Quit();
	SDL_Log("game clean!\n");
}

// texture使用
SDL_Texture* loadTexture(const char* fileanme)
{
	//加载图片
	SDL_Surface* mmSfc = SDL_LoadBMP(fileanme);
	//把Surface转成Texture
	SDL_Texture* tex = SDL_CreateTextureFromSurface(gGame.render, mmSfc);
	//释放掉surface
	SDL_FreeSurface(mmSfc);
	return tex;
}

//判断游戏是否在运行
static bool game_running()
{
	return gGame.isRunning;
}

// 关闭游戏
static void gamer_Done()
{
	gGame.isRunning = false;
}
