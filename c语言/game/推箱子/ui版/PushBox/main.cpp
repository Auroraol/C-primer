#include "Game.h"
#include <stdio.h>
#include <conio.h>
#include <time.h>

enum date
{
	SPACE, WALL, DEST, BOX, PLAYER
};

int level = 0;	//��ǰ���ڹؿ�

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


SDL_Texture* ItemTex[7];	//ͼƬָ������
void loadTex()
{
	//����һ��ͼƬ
	ItemTex[0] = loadTexture("./images/0.bmp");
	ItemTex[1] = loadTexture("./images/1.bmp");
	ItemTex[2] = loadTexture("./images/2.bmp");
	ItemTex[3] = loadTexture("./images/3.bmp");
	ItemTex[4] = loadTexture("./images/4.bmp");
	ItemTex[5] = loadTexture("./images/5.bmp");
	ItemTex[6] = loadTexture("./images/6.bmp");
}

//��Ⱦ
#define GRID_SIZE 64	//ͼƬ���
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
	//��Ⱦ���ǳ�
	SDL_RenderPresent(gGame.render);
}

//�ƶ�&&������
void move(SDL_KeyboardEvent* ev)
{
	//���ҵ���ҵ�λ�� (r,c)
	int r = 0, c = 0;
	bool isEnd = false;  // �˳�˫��ѭ��
	for (int i = 0; i < 10; i++)
	{
		for (int k = 0; k < 10; k++)
		{
			//�ҵ���� ����վ��Ŀ�ĵ��ϵ����
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
		//����ƶ������:��ҵ�ǰ���ǿյأ���ҵ�ǰ����Ŀ�ĵ�
		if (map[level][r - 1][c] == SPACE || map[level][r - 1][c] == DEST)
		{
			//�Ȱ�����ƶ���ǰ��
			map[level][r - 1][c] += PLAYER;
			//Ȼ�����Ҵ�ԭ����λ��ɾ��
			map[level][r][c] -= PLAYER;
		}
		//��ҵ�ǰ��������
		else if (map[level][r - 1][c] == BOX || map[level][r - 1][c] == BOX + DEST)
		{
			//�ܹ������ӵ����:���ӵ�ǰ���ǿյأ����ӵ�ǰ����Ŀ�ĵ�
			if (map[level][r - 2][c] == SPACE || map[level][r - 2][c] == DEST)
			{
				//�������ƶ�������ǰ��
				map[level][r - 2][c] += BOX;
				//�����Ӵ�ԭ����λ�������
				map[level][r - 1][c] -= BOX;
				//������ƶ���ԭ�����ӵ�λ��
				map[level][r - 1][c] += PLAYER;
				//����Ҵ�ԭ����λ�����
				map[level][r][c] -= PLAYER;
			}
		}
		break;
	case SDLK_DOWN:
		//����ƶ������:��ҵ�ǰ���ǿյأ���ҵ�ǰ����Ŀ�ĵ�
		if (map[level][r + 1][c] == SPACE || map[level][r + 1][c] == DEST)
		{
			//�Ȱ�����ƶ���ǰ��
			map[level][r + 1][c] += PLAYER;
			//Ȼ�����Ҵ�ԭ����λ��ɾ��
			map[level][r][c] -= PLAYER;
		}
		//��ҵ�ǰ��������
		else if (map[level][r + 1][c] == BOX || map[level][r + 1][c] == BOX + DEST)
		{
			//�ܹ������ӵ����:���ӵ�ǰ���ǿյأ����ӵ�ǰ����Ŀ�ĵ�
			if (map[level][r + 2][c] == SPACE || map[level][r + 2][c] == DEST)
			{
				//�������ƶ�������ǰ��
				map[level][r + 2][c] += BOX;
				//�����Ӵ�ԭ����λ�������
				map[level][r + 1][c] -= BOX;
				//������ƶ���ԭ�����ӵ�λ��
				map[level][r + 1][c] += PLAYER;
				//����Ҵ�ԭ����λ�����
				map[level][r][c] -= PLAYER;
			}
		}
		break;
	case SDLK_LEFT:
		//����ƶ������:��ҵ�ǰ���ǿյأ���ҵ�ǰ����Ŀ�ĵ�
		if (map[level][r][c - 1] == SPACE || map[level][r][c - 1] == DEST)
		{
			//�Ȱ�����ƶ���ǰ��
			map[level][r][c - 1] += PLAYER;
			//Ȼ�����Ҵ�ԭ����λ��ɾ��
			map[level][r][c] -= PLAYER;
		}
		//��ҵ�ǰ��������
		else if (map[level][r][c - 1] == BOX || map[level][r][c - 1] == BOX + DEST)
		{
			//�ܹ������ӵ����:���ӵ�ǰ���ǿյأ����ӵ�ǰ����Ŀ�ĵ�
			if (map[level][r][c - 2] == SPACE || map[level][r][c - 2] == DEST)
			{
				//�������ƶ�������ǰ��
				map[level][r][c - 2] += BOX;
				//�����Ӵ�ԭ����λ�������
				map[level][r][c - 1] -= BOX;
				//������ƶ���ԭ�����ӵ�λ��
				map[level][r][c - 1] += PLAYER;
				//����Ҵ�ԭ����λ�����
				map[level][r][c] -= PLAYER;
			}
		}
		break;
	case SDLK_RIGHT:
		//����ƶ������:��ҵ�ǰ���ǿյأ���ҵ�ǰ����Ŀ�ĵ�
		if (map[level][r][c + 1] == SPACE || map[level][r][c + 1] == DEST)
		{
			//�Ȱ�����ƶ���ǰ��
			map[level][r][c + 1] += PLAYER;
			//Ȼ�����Ҵ�ԭ����λ��ɾ��
			map[level][r][c] -= PLAYER;
		}
		//��ҵ�ǰ��������
		else if (map[level][r][c + 1] == BOX || map[level][r][c + 1] == BOX + DEST)
		{
			//�ܹ������ӵ����:���ӵ�ǰ���ǿյأ����ӵ�ǰ����Ŀ�ĵ�
			if (map[level][r][c + 2] == SPACE || map[level][r][c + 2] == DEST)
			{
				//�������ƶ�������ǰ��
				map[level][r][c + 2] += BOX;
				//�����Ӵ�ԭ����λ�������
				map[level][r][c + 1] -= BOX;
				//������ƶ���ԭ�����ӵ�λ��
				map[level][r][c + 1] += PLAYER;
				//����Ҵ�ԭ����λ�����
				map[level][r][c] -= PLAYER;
			}
		}
		break;
	}

}

//�ж��Ƿ����
bool judge()
{
	for (int i = 0; i < 10; i++)
	{
		for (int k = 0; k < 10; k++)
		{
			//����ҵ������ӣ���˵��û�й���
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
	//���ð�ť
	const SDL_MessageBoxButtonData buttons[] = {
		{ SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 0, u8"�˳���Ϸ"},
		//{ SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, u8"���¿�ʼ" },
	};
	//���öԻ�����ɫ
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
	//���SDL_MessageBoxData�ṹ��
	const SDL_MessageBoxData messageboxdata = {
		SDL_MESSAGEBOX_INFORMATION, /* .flags */
		NULL, /* .window */
		u8"��ʾ", /* .title */
		ch, /* .message */
		SDL_arraysize(buttons), /* .numbuttons */
		buttons, /* .buttons */
		&colorScheme /* .colorScheme */
	};

	int buttonid;  //buttonid������洢����µİ�ť��id
	//���ú���
	if (SDL_ShowMessageBox(&messageboxdata, &buttonid) < 0)
	{
		SDL_Log(u8"�Ի��򴴽�ʧ��");
	}
	else
	{
		SDL_Log(u8"ѡ�����: %s", buttons[buttonid].text);
	}
	return 0;
}

int main(int argc, char* argv[])
{
	game_init("PushBox", 640, 640);
	loadTex();

	while (game_running())
	{
		// �¼�ѭ��
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
				printf("��ϲ�㣬ͨ����\n");
				result = button(u8"��ϲ�㣬ͨ����");
				printf("%d", result);
				if (result == 0)
				{
					printf("�˳���Ϸ");
					exit(0);
				}
			}
			else
			{
				printf("��ϲ�㣬�����ˣ���������һ��\n");
			}

		}

		render();
	}

	game_clean();
	return 0;
}