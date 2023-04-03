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
bool isOver = false;   // ʧ��(����)
bool isWin = false;    // ʤ��

int main(void)
{
	initgraph(COL * 40, ROW * 40, EW_SHOWCONSOLE);
	//��������
	mciSendString("open ./images/start.mp3", NULL, 0, NULL);
	mciSendString("play ./images/start.mp3", NULL, 0, NULL);

	srand((unsigned int)time(NULL));
	//ɨ�� ����
	int map[ROW][COL] = {0};
	// ͨ�����������չ�ָ��û���, ��ԴͼƬ���������������
	IMAGE imgs[12];
	initMap(map);
	loadImg(imgs);
	showMap(map);

	while (true)
	{
		mouseEvent(map);
		drawMap(map, imgs);

		HWND ret = GetHWnd();
		SetWindowText(ret, "ɨ��");
		if (isOver || isWin)
		{
			char text[40] = {0};
			if (isOver)
			{
				strcpy(text, "��㵽����, �Ƿ���������һ�� ?");
			}
			else
			{
				strcpy(text, "�������,�Ƿ�����һ��?");
			}
			int result = MessageBox(ret, text, "��ʾ", MB_OKCANCEL);
			if (result == IDOK)
			{
				initMap(map);
				isOver = false;
				isWin = false;
			}
			else
			{
				//exit(EXIT_FAILURE);//�쳣�˳�
				exit(0);//�����˳�

			}

		}
	}

	getchar();
	return 0;
}

void initMap(int map[][10])
{
	//��ʼ��ȫΪ0
	memset(map, 0, ROW * COL * 4);
	//���10���� ��-1
	for (int k = 0; k < 10;)
	{
		int r = rand() % ROW;
		int c = rand() % COL;
		if (map[r][c] != -1)
		{
			map[r][c] = -1;
			// ����������Ϊ���ĵľŹ���
			for (int i = r - 1; i <= r + 1; i++)
			{
				for (int j = c - 1; j <= c + 1; j++)
				{
					// ������ʾ�Ļ�,ͨ�����ȵ�������������Խ��Ķ���
					if ((i >= 0 && i < ROW && j >= 0 && j < COL) && map[i][j] != -1)
					{
						map[i][j] ++;
					}
				}
			}
			k++;
		}
	}

	//���ܸ���  // ��19(29) ���� 21-28 //��� 31 //����ͼ 30
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
	//��ͼƬ
	for (int i = 0; i < ROW; i++)   //��Ӧy
	{
		for (int j = 0; j < COL; j++) //��Ӧx
		{
			if (map[i][j] >= 0 && map[i][j] <= 8)
			{

				putimage(j * 40, i * 40, &imgs[map[i][j]]); //��ͼ���
			}
			else if (map[i][j] == -1)  //���� 
			{
				putimage(j * 40, i * 40, &imgs[9]);
			}

			else if (map[i][j] >= 19 && map[i][j] <= 28)
			{
				putimage(j * 40, i * 40, imgs + 10); //������ͼ:
			}
			else if (map[i][j] > 28)  //���
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
		//�����Ӧ������
		int r = msg.y / 40;
		int c = msg.x / 40;
		// ����������򿪶�Ӧ����, -20
		if (msg.uMsg == WM_LBUTTONDOWN)
		{
			// ������Ӳ���
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
				openNull(map, r, c);  //�հ�,ը��һƬ
				jugde(map, r, c);  // ����
				showMap(map);
			}
		}
		// �Ҽ����
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
			else if (map[r][c] > 28) //�Ѿ���ǹ���,ȡ�����
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
		// ������Χ��
		for (int i = r - 1; i <= r + 1; i++)
		{
			for (int j = c - 1; j <= c + 1; j++)
			{
				// ��Χ�ĸ���û�д�,�ʹ�
				if ((i >= 0 && i < ROW && j >= 0 && j < COL) && map[i][j] >= 19 && map[i][j] <= 28)
				{
					map[i][j] -= 20;
					openNull(map, i, j);  // �ݹ�

				}
			}
		}
	}
}

void jugde(int map[][10], int r, int c)
{
	// ��������
	if (map[r][c] == -1)
	{
		// �����е��׶���
		for (int i = 0; i < ROW; i++)
		{
			for (int j = 0; j < COL; j++)
			{
				if (map[i][j] == 19)
					map[i][j] -= 20;
				//��ǵ���ҲҪ��
				else if (map[i][j] == 39)
					map[i][j] -= 40;
			}
		}
		isOver = true;
	}

	//��Ӧ�õ㿪�ĸ��Ӷ��㿪�ˣ���Ϸ��ʤ����
	int cnt = 0;
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			if (map[i][j] >= 0 && map[i][j] <= 8) // ͬ�Ƶ㿪��
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
	int result = MessageBox(ret, "��㵽����,�Ƿ���������һ��?", "��ʾ", MB_OKCANCEL);
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
	int result = MessageBox(ret, "�������,�Ƿ�����һ��?", "��ʾ", MB_OKCANCEL);
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