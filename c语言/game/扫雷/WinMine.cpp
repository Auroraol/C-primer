#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <easyx.h>
#include <graphics.h>
#include <mmsystem.h>
#pragma comment (lib, "winmm.lib")

enum MyEnum
{
	ROW = 10,
	COL = 10
};

void initMap(int map[][10]);
void loadImg(IMAGE imgs[]);
void drawMap(int(*map)[10], IMAGE* imgs);
void showMap(int(*arr)[10]);
void mouseEvent(int map[][10]);
void openNull(int map[][10], int r, int c);
void jugde(int map[][10], int r, int c);
bool isOver = false;   // 失败(踩雷)
bool isWin = false;    // 胜利

int main(void)
{
	initgraph(COL * 40, ROW * 40, EW_SHOWCONSOLE);
	//播放音乐
	mciSendString("open ./images/start.mp3", NULL, 0, NULL);
	mciSendString("play ./images/start.mp3", NULL, 0, NULL);

	srand((unsigned int)time(NULL));
	//扫雷 数据
	int map[ROW][COL] = {0};
	// 通过界面把数据展现给用户看, 资源图片的名字是有意义的
	IMAGE imgs[12];
	initMap(map);
	loadImg(imgs);
	showMap(map);

	while (true)
	{
		mouseEvent(map);
		drawMap(map, imgs);

		HWND ret = GetHWnd();
		SetWindowText(ret, "扫雷");
		if (isOver || isWin)
		{
			char text[40] = {0};
			if (isOver)
			{
				strcpy(text, "你点到雷了, 是否重新再来一把 ?");
			}
			else
			{
				strcpy(text, "你过关了,是否再来一把?");
			}
			int result = MessageBox(ret, text, "提示", MB_OKCANCEL);
			if (result == IDOK)
			{
				initMap(map);
				isOver = false;
				isWin = false;
			}
			else
			{
				//exit(EXIT_FAILURE);//异常退出
				exit(0);//正常退出

			}

		}
	}

	getchar();
	return 0;
}

void initMap(int map[][10])
{
	//初始化全为0
	memset(map, 0, ROW * COL * 4);
	//随机10个雷 雷-1
	for (int k = 0; k < 10;)
	{
		int r = rand() % ROW;
		int c = rand() % COL;
		if (map[r][c] != -1)
		{
			map[r][c] = -1;
			// 遍历以雷区为中心的九宫格
			for (int i = r - 1; i <= r + 1; i++)
			{
				for (int j = c - 1; j <= c + 1; j++)
				{
					// 索引表示的话,通过长度的限制消除数组越界的东西
					if ((i >= 0 && i < ROW && j >= 0 && j < COL) && map[i][j] != -1)
					{
						map[i][j] ++;
					}
				}
			}
			k++;
		}
	}

	//加密格子  // 雷19(29) 数子 21-28 //标记 31 //加密图 30
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			map[i][j] += 20;
		}
	}

}

void loadImg(IMAGE imgs[])
{
	for (int i = 0; i < 12; i++)
	{
		char image[20] = {0};
		sprintf(image, "./images/%d.jpg", i);
		loadimage(imgs + i, image, 40, 40);
	}

	for (int i = 0; i < 12; i++)
	{
		char image[20] = {0};
		sprintf(image, "./images/%d.jpg", i);
		loadimage(imgs + i, image, 40, 40);
	}
}

void drawMap(int(*map)[10], IMAGE* imgs)
{
	//贴图片
	for (int i = 0; i < ROW; i++)   //对应y
	{
		for (int j = 0; j < COL; j++) //对应x
		{
			if (map[i][j] >= 0 && map[i][j] <= 8)
			{

				putimage(j * 40, i * 40, &imgs[map[i][j]]); //画图理解
			}
			else if (map[i][j] == -1)  //贴雷 
			{
				putimage(j * 40, i * 40, &imgs[9]);
			}

			else if (map[i][j] >= 19 && map[i][j] <= 28)
			{
				putimage(j * 40, i * 40, imgs + 10); //加密贴图:
			}
			else if (map[i][j] > 28)  //标记
			{
				putimage(j * 40, i * 40, imgs + 11);
			}
		}
	}
}

void showMap(int(*arr)[10])
{
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			printf("%2d ", arr[i][j]);
		}
		printf("\n");
	}
	printf("\n\n");
}

void mouseEvent(int map[][10])
{
	if (MouseHit())
	{
		MOUSEMSG msg = GetMouseMsg();
		//求出对应的行列
		int r = msg.y / 40;
		int c = msg.x / 40;
		// 鼠标左键点击打开对应格子, -20
		if (msg.uMsg == WM_LBUTTONDOWN)
		{
			// 点击格子播放
			mciSendString("close click", NULL, 0, NULL);
			mciSendString("open ./images/click.wav alias click", NULL, 0, NULL);
			mciSendString("play click", NULL, 0, NULL);

			if (map[r][c] >= 19 && map[r][c] <= 28)
			{
				map[r][c] -= 20;
				if (map[r][c] == 0)
				{
					mciSendString("close search", NULL, 0, NULL);
					mciSendString("open ./images/search.wav alias search", NULL, 0, NULL);
					mciSendString("play search", NULL, 0, NULL);
				}
				openNull(map, r, c);  //空白,炸开一片
				jugde(map, r, c);  // 踩雷
				showMap(map);
			}
		}
		// 右键标记
		else if (msg.uMsg == WM_RBUTTONDOWN)
		{
			mciSendString("close rightClick", NULL, 0, NULL);
			mciSendString("open ./images/rightClick.wav alias rightClick", NULL, 0, NULL);
			mciSendString("play rightClick", NULL, 0, NULL);
			if (map[r][c] >= 19 && map[r][c] <= 28)
			{
				map[r][c] += 20;
				showMap(map);
			}
			else if (map[r][c] > 28) //已经标记过了,取消标记
			{
				map[r][c] -= 20;
			}
		}

	}
}

void openNull(int map[][10], int r, int c)
{
	if (map[r][c] == 0)
	{
		// 遍历周围的
		for (int i = r - 1; i <= r + 1; i++)
		{
			for (int j = c - 1; j <= c + 1; j++)
			{
				// 周围的格子没有打开,就打开
				if ((i >= 0 && i < ROW && j >= 0 && j < COL) && map[i][j] >= 19 && map[i][j] <= 28)
				{
					map[i][j] -= 20;
					openNull(map, i, j);  // 递归

				}
			}
		}
	}
}

void jugde(int map[][10], int r, int c)
{
	// 如果点的雷
	if (map[r][c] == -1)
	{
		// 把所有的雷都打开
		for (int i = 0; i < ROW; i++)
		{
			for (int j = 0; j < COL; j++)
			{
				if (map[i][j] == 19)
					map[i][j] -= 20;
				//标记的雷也要打开
				else if (map[i][j] == 39)
					map[i][j] -= 40;
			}
		}
		isOver = true;
	}

	//把应该点开的格子都点开了，游戏就胜利了
	int cnt = 0;
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			if (map[i][j] >= 0 && map[i][j] <= 8) // 同计点开的
			{
				cnt++;
			}
		}
	}
	if (cnt == ROW * COL - 10)
	{
		isWin = true;
	}
}

/*
if (isOver)
{
	HWND ret = GetHWnd();
	int result = MessageBox(ret, "你点到雷了,是否重新再来一把?", "提示", MB_OKCANCEL);
	if (result == IDOK)
	{
		initMap(map);
		isOver = false;
	}
	else
	{
		exit(EXIT_FAILURE);
	}
}

if (isWin)
{
	HWND ret = GetHWnd();
	int result = MessageBox(ret, "你过关了,是否再来一把?", "提示", MB_OKCANCEL);
	if (result == IDOK)
	{
		initMap(map);
		isWin = false;
	}
	else
	{
		exit(EXIT_FAILURE);
	}
}
*/