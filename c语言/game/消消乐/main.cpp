#include "game.h"
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <time.h>

#define ROWS (10 + 2)
#define COLS (10 + 2)
#define texttureSize 40

// ����ǰ�����±�
typedef struct
{
	int row;
	int col;

}Index;
Index begin = {-1, -1}, end = {-1, -1};
bool state = false;  // ��¼���Ǵε��

// ͼƬ
SDL_Texture* bkTex;
SDL_Texture* ItemTex[16];	//ͼƬָ������
void loadTex()
{

	// ���ر���ͼ
	bkTex = textureLoad("./assets/texture/bg.png");
	//��16����ͼƬ  //����Ϊ0���ǵ�һ��ͼƬ
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
	game_init(u8"������", COLS * texttureSize, ROWS * texttureSize);
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

				// ����(����)
				if (clear(map, &begin, &end))
				{
					SDL_Log("can claer");
					map[begin.row][begin.col] = 0;
					map[end.row][end.col] = 0;
					// �ڴ�����ʧ
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
	//�ò�ͬ����������ʾ��ͬ�Ķ��ÿ�ֶ��������(10��)��һ����Ҫ10�ֶ���
	for (int i = 1; i < ROWS - 1; i++)
	{
		for (int j = 1; j < COLS - 1; j++)
		{
			map[i][j] = i;  // ��ʼ�洢���� 1-10
		}
	}

	// ��������
	for (int i = 1; i < ROWS - 1; i++)
	{
		for (int j = 1; j < COLS - 1; j++)
		{
			// ����ҵ������±� [0, 11] -> [1,10]
			int r = rand() % (ROWS - 2) + 1;
			int c = rand() % (COLS - 2) + 1;

			swap(&map[i][j], &map[r][c]);
		}
	}
}

void draw(int(*map)[COLS])
{
	// ������ͼ
	SDL_RenderCopy(ggame.renderer, bkTex, NULL, NULL);


	// ��ͼƬ
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


	// ���ƾ���
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
	SDL_Log("%s", __FUNCTION__); //��ʾ���ں�����

	if (ev->button == SDL_BUTTON_LEFT)
	{
		if (state == false)
		{
			begin.col = ev->x / texttureSize;  //�õ�����
			begin.row = ev->y / texttureSize;
			SDL_Log(u8"��һ�ε��: ��=%d , ��=%d", begin.row + 1, begin.col + 1);
		}
		else
		{
			end.col = ev->x / texttureSize;  //�õ�����
			end.row = ev->y / texttureSize;
			SDL_Log(u8"�ڶ��ε��: ��=%d , ��=%d", end.row + 1, end.col + 1);
		}
		state = !state; // �������л�״̬
	}
}

// �ж��Ƿ����ϰ��� �Ƿ���true
bool isblock(int(*map)[COLS], int r, int c)
{
	return map[r][c];   // û���ϰ�Ϊ0,����false
}

// ˮƽ���� ����������true
bool horizontal_wipeint(int(*map)[COLS], Index* begin, Index* end)
{
	if (begin->row != end->row)
	{
		return false;
	}

	// ���С���Ǹ���
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

	// ����С�Ŀ�ʼ����
	for (int col = minC + 1; col < maxC; col++)
	{
		if (isblock(map, begin->row, col))  // ���谭
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

	// ���С���Ǹ���
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

	// ����С�Ŀ�ʼ����
	for (int row = minR + 1; row < maxR; row++)
	{
		if (isblock(map, row, begin->col))  // ���谭
		{
			return false;
		}
	}
	return true;
}

bool a_corner_wipe(int(*map)[COLS], Index* begin, Index* end)
{
	//�ҵ������������й�ϵ�Ĺսǵ�
	Index t1 = {begin->row, end->col}, t2 = {end->row, begin->col};

	//�жϵ�һ���յ��������Ĺ�ϵ
	if (!isblock(map, t1.row, t1.col)) // �յ㲻���ϰ���
	{
		if (horizontal_wipeint(map, &t1, begin) && vertical_wipe(map, &t1, end)   // t1�� ��һ�ε����,�ڶ��ε���� 
			|| horizontal_wipeint(map, &t1, end) && vertical_wipe(map, &t1, begin))
		{
			return true;
		}
	}

	if (!isblock(map, t2.row, t2.col))
	{
		if (horizontal_wipeint(map, &t2, begin) && vertical_wipe(map, &t2, end)   // t1�� ��һ�ε����,�ڶ��ε���� 
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
			// ȥ��û�й�ϵ���±�
			if (i != begin->row && i != end->row && j != begin->col && j != end->col)
			{
				continue;
			}
			// �ų������������
			if (i == begin->row && j == begin->col || i == end->row && j == end->col)
			{
				continue;
			}

			// �ж�����ĵ��Ƿ����ϰ���, �Ǿͼ�������
			if (isblock(map, i, j))
			{
				continue;
			}

			//��������ǹյ�ĵ�
			Index t = {i , j};
			// t1�� ��һ�ε����,�ڶ��ε���� 

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
	// ��ͬһ��
	if (begin->row == end->row && begin->col == end->col)
	{
		return false;
	}
	// ����ͬһ��
	if (map[begin->row][begin->col] != map[end->row][end->col])
	{
		return false;
	}

	bool flag = false;
	// ˮƽ����  
	flag |= horizontal_wipeint(map, begin, end);  // �к���������
	//ˮƽ����
	// ��ֱ����
	flag |= vertical_wipe(map, begin, end);
	// һ���սǵ�����
	flag |= a_corner_wipe(map, begin, end);
	// �����ս�����
	flag |= two_corners_wipe(map, begin, end);

	return flag;
}
