#include "game.h"
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <time.h>

#define ROWS (10 + 2)
#define COLS (10 + 2)
#define texttureSize 40

// 保存前后点击下标
typedef struct
{
	int row;
	int col;

}Index;
Index begin = {-1, -1}, end = {-1, -1};
bool state = false;  // 记录是那次点击

// 图片
SDL_Texture* bkTex;
SDL_Texture* ItemTex[16];	//图片指针数组
void loadTex()
{

	// 加载背景图
	bkTex = textureLoad("./assets/texture/bg.png");
	//加16张载图片  //索引为0的是第一张图片
	char filename[30] = {0};
	for (int i = 0; i < 16; i++)
	{
		SDL_snprintf(filename, 30, "./assets/texture/%d.png", i + 1);
		ItemTex[i] = textureLoad(filename);
	}
}

void initMap(int(*map)[COLS]);
void show(int(*map)[COLS]);
void draw(int(*map)[COLS]);
void swap(int* x, int* y);
void mouseEvent(SDL_MouseButtonEvent* ev);
bool clear(int(*map)[COLS], Index* begin, Index* end);
bool isblock(int(*map)[COLS], int r, int c);
bool horizontal_wipeint(int(*map)[COLS], Index* begin, Index* end);
bool vertical_wipe(int(*map)[COLS], Index* begin, Index* end);
bool a_corner_wipe(int(*map)[COLS], Index* begin, Index* end);
bool two_corners_wipe(int(*map)[COLS], Index* begin, Index* end);


int main(int argc, char* argv[])
{
	game_init(u8"连连看", COLS * texttureSize, ROWS * texttureSize);
	loadTex();

	int map[ROWS][COLS] = {0};
	initMap(map);
	show(map);

	while (game_running())
	{
		SDL_Event ev = {0};
		while (SDL_PollEvent(&ev))
		{
			if (ev.type == SDL_QUIT)
				gamer_Done();
			else if (ev.type == SDL_MOUSEBUTTONDOWN)
			{
				mouseEvent(&ev.button);

				// 消除(核心)
				if (clear(map, &begin, &end))
				{
					SDL_Log("can claer");
					map[begin.row][begin.col] = 0;
					map[end.row][end.col] = 0;
					// 黑窗口消失
					begin = {-1 , -1};
					end = {-1, -1};
				}
			}
		}
		//SDL_RenderClear(ggame.renderer);
		draw(map);
		SDL_RenderPresent(ggame.renderer);
	}

	gameClear();
	return 0;
}

void swap(int* x, int* y)
{
	int temp = *y;
	*y = *x;
	*x = temp;
}

void initMap(int(*map)[COLS])
{
	srand((unsigned int)time(NULL));
	//用不同的数据来表示不同的动物，每种动物来五对(10个)，一共需要10种动物
	for (int i = 1; i < ROWS - 1; i++)
	{
		for (int j = 1; j < COLS - 1; j++)
		{
			map[i][j] = i;  // 初始存储数据 1-10
		}
	}

	// 打乱数组
	for (int i = 1; i < ROWS - 1; i++)
	{
		for (int j = 1; j < COLS - 1; j++)
		{
			// 随机找到两个下标 [0, 11] -> [1,10]
			int r = rand() % (ROWS - 2) + 1;
			int c = rand() % (COLS - 2) + 1;

			swap(&map[i][j], &map[r][c]);
		}
	}
}

void draw(int(*map)[COLS])
{
	// 画背景图
	SDL_RenderCopy(ggame.renderer, bkTex, NULL, NULL);


	// 画图片
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			if (map[i][j] != 0)
			{
				SDL_Rect rec = {j * texttureSize, i * texttureSize,  texttureSize, texttureSize};
				SDL_RenderCopy(ggame.renderer, ItemTex[map[i][j]], NULL, &rec);
			}
		}
	}


	// 绘制矩形
	if (begin.row != -1)
	{

		SDL_Rect re1 = {begin.col * texttureSize, begin.row * texttureSize, texttureSize, texttureSize};
		SDL_RenderDrawRect(ggame.renderer, &re1);
	}
	if (end.row != -1)
	{
		SDL_Rect re2 = {end.col * texttureSize, end.row * texttureSize, texttureSize, texttureSize};
		SDL_RenderDrawRect(ggame.renderer, &re2);
	}

}

void show(int(*map)[COLS])
{
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			printf("%-2d ", map[i][j]);
		}
		printf("\n");
	}
}

void mouseEvent(SDL_MouseButtonEvent* ev)
{
	SDL_Log("%s", __FUNCTION__); //显示所在函数名

	if (ev->button == SDL_BUTTON_LEFT)
	{
		if (state == false)
		{
			begin.col = ev->x / texttureSize;  //得到行列
			begin.row = ev->y / texttureSize;
			SDL_Log(u8"第一次点击: 行=%d , 列=%d", begin.row + 1, begin.col + 1);
		}
		else
		{
			end.col = ev->x / texttureSize;  //得到行列
			end.row = ev->y / texttureSize;
			SDL_Log(u8"第二次点击: 行=%d , 列=%d", end.row + 1, end.col + 1);
		}
		state = !state; // 点击后就切换状态
	}
}

// 判断是否是障碍物 是返回true
bool isblock(int(*map)[COLS], int r, int c)
{
	return map[r][c];   // 没有障碍为0,返回false
}

// 水平消除 能消除返回true
bool horizontal_wipeint(int(*map)[COLS], Index* begin, Index* end)
{
	if (begin->row != end->row)
	{
		return false;
	}

	// 求出小的那个行
	int minC = std::min(begin->col, end->col);
	int maxC;
	if (minC == begin->col)
	{
		maxC = end->col;
	}
	else
	{
		maxC = begin->col;
	}

	// 从最小的开始遍历
	for (int col = minC + 1; col < maxC; col++)
	{
		if (isblock(map, begin->row, col))  // 有阻碍
		{
			return false;
		}
	}
	return true;
}

bool vertical_wipe(int(*map)[COLS], Index* begin, Index* end)
{
	if (begin->col != end->col)
	{
		return false;
	}

	// 求出小的那个行
	int minR = std::min(begin->row, end->row);
	int maxR;
	if (minR == begin->row)
	{
		maxR = end->row;
	}
	else
	{
		maxR = begin->row;
	}

	// 从最小的开始遍历
	for (int row = minR + 1; row < maxR; row++)
	{
		if (isblock(map, row, begin->col))  // 有阻碍
		{
			return false;
		}
	}
	return true;
}

bool a_corner_wipe(int(*map)[COLS], Index* begin, Index* end)
{
	//找到与这两个点有关系的拐角点
	Index t1 = {begin->row, end->col}, t2 = {end->row, begin->col};

	//判断第一个拐点和两个点的关系
	if (!isblock(map, t1.row, t1.col)) // 拐点不是障碍物
	{
		if (horizontal_wipeint(map, &t1, begin) && vertical_wipe(map, &t1, end)   // t1和 第一次点击点,第二次点击点 
			|| horizontal_wipeint(map, &t1, end) && vertical_wipe(map, &t1, begin))
		{
			return true;
		}
	}

	if (!isblock(map, t2.row, t2.col))
	{
		if (horizontal_wipeint(map, &t2, begin) && vertical_wipe(map, &t2, end)   // t1和 第一次点击点,第二次点击点 
			|| horizontal_wipeint(map, &t2, end) && vertical_wipe(map, &t2, begin))
		{
			return true;
		}
	}

	return false;
}


bool two_corners_wipe(int(*map)[COLS], Index* begin, Index* end)
{
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			// 去除没有关系的下标
			if (i != begin->row && i != end->row && j != begin->col && j != end->col)
			{
				continue;
			}
			// 排除点击的两个点
			if (i == begin->row && j == begin->col || i == end->row && j == end->col)
			{
				continue;
			}

			// 判断满足的点是否是障碍物, 是就继续跳过
			if (isblock(map, i, j))
			{
				continue;
			}

			//保存可能是拐点的点
			Index t = {i , j};
			// t1和 第一次点击点,第二次点击点 

			if ((horizontal_wipeint(map, &t, begin) || vertical_wipe(map, &t, begin)) && a_corner_wipe(map, &t, end) ||
				(horizontal_wipeint(map, &t, end) || vertical_wipe(map, &t, end)) && a_corner_wipe(map, &t, begin))
			{
				return true;
			}
		}
	}

	return false;
}

bool clear(int(*map)[COLS], Index* begin, Index* end)
{
	// 是同一个
	if (begin->row == end->row && begin->col == end->col)
	{
		return false;
	}
	// 不是同一种
	if (map[begin->row][begin->col] != map[end->row][end->col])
	{
		return false;
	}

	bool flag = false;
	// 水平消除  
	flag |= horizontal_wipeint(map, begin, end);  // 有后面决定真假
	//水平消除
	// 垂直消除
	flag |= vertical_wipe(map, begin, end);
	// 一个拐角的消除
	flag |= a_corner_wipe(map, begin, end);
	// 两个拐角消除
	flag |= two_corners_wipe(map, begin, end);

	return flag;
}
