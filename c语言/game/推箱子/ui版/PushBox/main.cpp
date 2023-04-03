#include "Game.h"
#include <stdio.h>
#include <conio.h>
#include <time.h>

enum date
{
	SPACE, WALL, DEST, BOX, PLAYER
};

int level = 0;	//当前所在关卡

int map[4][10][10] = {
	{
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,1,1,1,0,0,0,0},
		{0,0,0,1,2,1,0,0,0,0},
		{0,0,0,1,0,1,1,1,1,0},
		{0,1,1,1,3,0,3,2,1,0},
		{0,1,2,3,4,0,1,1,1,0},
		{0,1,1,1,1,3,1,0,0,0},
		{0,0,0,0,1,2,1,0,0,0},
		{0,0,0,0,1,1,1,0,0,0},
		{0,0,0,0,0,0,0,0,0,0}
	},
	{
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,1,1,1,0,0,0,0},
		{0,1,1,1,2,1,0,0,0,0},
		{0,1,0,0,0,1,1,1,1,0},
		{0,1,1,1,3,0,3,2,1,0},
		{0,1,2,3,4,0,1,1,1,0},
		{0,1,0,1,1,3,1,0,0,0},
		{0,1,1,1,1,2,1,0,0,0},
		{0,0,0,0,1,1,1,0,0,0},
		{0,0,0,0,0,0,0,0,0,0}
	},
	{
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,1,1,0,0,1,1,0,0},
		{0,1,0,0,1,1,0,0,1,0},
		{1,2,0,0,0,0,0,0,2,1},
		{1,0,0,3,4,0,3,0,0,1},
		{0,1,0,0,0,3,0,0,1,0},
		{0,0,1,0,3,0,0,1,0,0},
		{0,0,0,1,2,2,1,0,0,0},
		{0,0,0,0,1,1,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0}
	},
	{
		{1,1,1,1,1,1,1,0,1,1},
		{0,1,2,0,0,4,1,1,1,0},
		{0,0,1,0,0,0,0,0,1,0},
		{0,0,1,3,0,0,3,0,1,1},
		{0,0,1,0,0,0,0,0,2,1},
		{0,0,1,0,0,3,0,1,1,1},
		{0,0,1,0,0,0,0,1,0,0},
		{0,0,1,0,3,0,0,1,0,0},
		{0,1,2,0,0,0,0,2,1,0},
		{1,1,1,1,1,1,1,1,1,1}
	}
};


SDL_Texture* ItemTex[7];	//图片指针数组
void loadTex()
{
	//加载一张图片
	ItemTex[0] = loadTexture("./images/0.bmp");
	ItemTex[1] = loadTexture("./images/1.bmp");
	ItemTex[2] = loadTexture("./images/2.bmp");
	ItemTex[3] = loadTexture("./images/3.bmp");
	ItemTex[4] = loadTexture("./images/4.bmp");
	ItemTex[5] = loadTexture("./images/5.bmp");
	ItemTex[6] = loadTexture("./images/6.bmp");
}

//渲染
#define GRID_SIZE 64	//图片宽度
void render()
{
	for (int r = 0; r < 10; r++)
	{
		for (int c = 0; c < 10; c++)
		{
			SDL_Rect destRect = {c * GRID_SIZE ,r * GRID_SIZE, GRID_SIZE, GRID_SIZE};
			SDL_RenderCopy(
				gGame.render,
				ItemTex[map[level][r][c]],
				NULL,
				&destRect);
		}
	}
	//渲染器登场
	SDL_RenderPresent(gGame.render);
}

//移动&&推箱子
void move(SDL_KeyboardEvent* ev)
{
	//先找到玩家的位置 (r,c)
	int r = 0, c = 0;
	bool isEnd = false;  // 退出双层循环
	for (int i = 0; i < 10; i++)
	{
		for (int k = 0; k < 10; k++)
		{
			//找到玩家 或者站在目的地上的玩家
			if (map[level][i][k] == PLAYER || map[level][i][k] == PLAYER + DEST)
			{
				r = i;
				c = k;
				isEnd = true;
				break;
			}
			if (isEnd == true)
				break;
		}
	}

	switch (ev->keysym.sym)
	{
	case SDLK_UP:
		//玩家移动的情况:玩家的前面是空地；玩家的前面是目的地
		if (map[level][r - 1][c] == SPACE || map[level][r - 1][c] == DEST)
		{
			//先把玩家移动到前面
			map[level][r - 1][c] += PLAYER;
			//然后把玩家从原来的位置删除
			map[level][r][c] -= PLAYER;
		}
		//玩家的前面是箱子
		else if (map[level][r - 1][c] == BOX || map[level][r - 1][c] == BOX + DEST)
		{
			//能够推箱子的情况:箱子的前面是空地；箱子的前面是目的地
			if (map[level][r - 2][c] == SPACE || map[level][r - 2][c] == DEST)
			{
				//把箱子移动到箱子前面
				map[level][r - 2][c] += BOX;
				//把箱子从原来的位置清除掉
				map[level][r - 1][c] -= BOX;
				//把玩家移动到原来箱子的位置
				map[level][r - 1][c] += PLAYER;
				//把玩家从原来的位置清除
				map[level][r][c] -= PLAYER;
			}
		}
		break;
	case SDLK_DOWN:
		//玩家移动的情况:玩家的前面是空地；玩家的前面是目的地
		if (map[level][r + 1][c] == SPACE || map[level][r + 1][c] == DEST)
		{
			//先把玩家移动到前面
			map[level][r + 1][c] += PLAYER;
			//然后把玩家从原来的位置删除
			map[level][r][c] -= PLAYER;
		}
		//玩家的前面是箱子
		else if (map[level][r + 1][c] == BOX || map[level][r + 1][c] == BOX + DEST)
		{
			//能够推箱子的情况:箱子的前面是空地；箱子的前面是目的地
			if (map[level][r + 2][c] == SPACE || map[level][r + 2][c] == DEST)
			{
				//把箱子移动到箱子前面
				map[level][r + 2][c] += BOX;
				//把箱子从原来的位置清除掉
				map[level][r + 1][c] -= BOX;
				//把玩家移动到原来箱子的位置
				map[level][r + 1][c] += PLAYER;
				//把玩家从原来的位置清除
				map[level][r][c] -= PLAYER;
			}
		}
		break;
	case SDLK_LEFT:
		//玩家移动的情况:玩家的前面是空地；玩家的前面是目的地
		if (map[level][r][c - 1] == SPACE || map[level][r][c - 1] == DEST)
		{
			//先把玩家移动到前面
			map[level][r][c - 1] += PLAYER;
			//然后把玩家从原来的位置删除
			map[level][r][c] -= PLAYER;
		}
		//玩家的前面是箱子
		else if (map[level][r][c - 1] == BOX || map[level][r][c - 1] == BOX + DEST)
		{
			//能够推箱子的情况:箱子的前面是空地；箱子的前面是目的地
			if (map[level][r][c - 2] == SPACE || map[level][r][c - 2] == DEST)
			{
				//把箱子移动到箱子前面
				map[level][r][c - 2] += BOX;
				//把箱子从原来的位置清除掉
				map[level][r][c - 1] -= BOX;
				//把玩家移动到原来箱子的位置
				map[level][r][c - 1] += PLAYER;
				//把玩家从原来的位置清除
				map[level][r][c] -= PLAYER;
			}
		}
		break;
	case SDLK_RIGHT:
		//玩家移动的情况:玩家的前面是空地；玩家的前面是目的地
		if (map[level][r][c + 1] == SPACE || map[level][r][c + 1] == DEST)
		{
			//先把玩家移动到前面
			map[level][r][c + 1] += PLAYER;
			//然后把玩家从原来的位置删除
			map[level][r][c] -= PLAYER;
		}
		//玩家的前面是箱子
		else if (map[level][r][c + 1] == BOX || map[level][r][c + 1] == BOX + DEST)
		{
			//能够推箱子的情况:箱子的前面是空地；箱子的前面是目的地
			if (map[level][r][c + 2] == SPACE || map[level][r][c + 2] == DEST)
			{
				//把箱子移动到箱子前面
				map[level][r][c + 2] += BOX;
				//把箱子从原来的位置清除掉
				map[level][r][c + 1] -= BOX;
				//把玩家移动到原来箱子的位置
				map[level][r][c + 1] += PLAYER;
				//把玩家从原来的位置清除
				map[level][r][c] -= PLAYER;
			}
		}
		break;
	}

}

//判断是否过关
bool judge()
{
	for (int i = 0; i < 10; i++)
	{
		for (int k = 0; k < 10; k++)
		{
			//如果找到了箱子，就说明没有过关
			if (map[level][i][k] == BOX)
			{
				return false;
			}
		}
	}
	return true;
}

int button(const char* ch)
{
	//设置按钮
	const SDL_MessageBoxButtonData buttons[] = {
		{ SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 0, u8"退出游戏"},
		//{ SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, u8"重新开始" },
	};
	//设置对话框颜色
	const SDL_MessageBoxColorScheme colorScheme = {
		{ /* .colors (.r, .g, .b) */
			/* [SDL_MESSAGEBOX_COLOR_BACKGROUND] */
			{ 255,   0,   0 },
			/* [SDL_MESSAGEBOX_COLOR_TEXT] */
			{   0, 255,   0 },
			/* [SDL_MESSAGEBOX_COLOR_BUTTON_BORDER] */
			{ 255, 255,   0 },
			/* [SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND] */
			{   0,   0, 255 },
			/* [SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED] */
			{ 255,   0, 255 }
		}
	};
	//填充SDL_MessageBoxData结构体
	const SDL_MessageBoxData messageboxdata = {
		SDL_MESSAGEBOX_INFORMATION, /* .flags */
		NULL, /* .window */
		u8"提示", /* .title */
		ch, /* .message */
		SDL_arraysize(buttons), /* .numbuttons */
		buttons, /* .buttons */
		&colorScheme /* .colorScheme */
	};

	int buttonid;  //buttonid参数会存储最后按下的按钮的id
	//调用函数
	if (SDL_ShowMessageBox(&messageboxdata, &buttonid) < 0)
	{
		SDL_Log(u8"对话框创建失败");
	}
	else
	{
		SDL_Log(u8"选择的是: %s", buttons[buttonid].text);
	}
	return 0;
}

int main(int argc, char* argv[])
{
	game_init("PushBox", 640, 640);
	loadTex();

	while (game_running())
	{
		// 事件循环
		SDL_Event ev = {0};
		while (SDL_PollEvent(&ev))
		{
			if (ev.type == SDL_QUIT)
			{
				gamer_Done();
				break;
			}
			else if (ev.type == SDL_KEYDOWN)
			{
				move(&ev.key);
				break;
			}
			else
			{
				break;
			}

		}

		if (judge())
		{
			level++;	//4
			int result;
			if (level == 4)
			{
				printf("恭喜你，通关了\n");
				result = button(u8"恭喜你，通关了");
				printf("%d", result);
				if (result == 0)
				{
					printf("退出游戏");
					exit(0);
				}
			}
			else
			{
				printf("恭喜你，过关了！按进入下一关\n");
			}

		}

		render();
	}

	game_clean();
	return 0;
}