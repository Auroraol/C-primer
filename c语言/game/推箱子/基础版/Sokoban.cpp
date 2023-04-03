#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

/* 推箱子
*  1.数据: 空地0 墙1 目的地2 箱子3 玩家4
* WALL：▓
  DEST：☆
  BOX：■
  PLAYER：♀
  BOX+DEST：★
  PLAYER+DEST：※
	2. 数据储存: 数组
*/

//#define SPACE     0 //空地
//#define WALL      1 //墙
//#define DEST      2 //目的地
//#define BOX       3 //箱子
//#define PLAYER    4 //玩家

enum date
{
	SPACE, WALL, DEST, BOX, PLAYER
};

//玩家站在目的地 BOX + DEST：     5
//箱子站在目的地 PLAYER + DEST：  6

int level = 0;	//当前所在关卡

int map[3][10][10] = {
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

void show()
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			switch (map[level][i][j])
			{
			case SPACE:
				printf("  ");
				break;
			case WALL:
				printf("▓ ");
				break;
			case DEST:
				printf("☆");
				break;
			case BOX:
				printf("■");
				break;
			case PLAYER:
				printf("♀");
				break;
			case PLAYER + DEST:		//玩家站在目的地
				printf("※");
				break;
			case BOX + DEST:		//箱子站在目的地
				printf("★");
				break;
			}
		}
		printf("\n");
	}
}

void move()
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

	// 获取按键操作
	int key = _getch(); //  _getch(); 输入之后不需要按回车
	//printf("%d", key);
	/*
	* 上建72
	* 下键80
	* 左键75
	* 右键77
	*/

	switch (key)
	{
	case 72:
	case 'w':
	case 'W':
		//玩家移动的情况:玩家的前面是空地；玩家的前面是箱子的目的地
		if (map[level][r - 1][c] == SPACE || map[level][r - 1][c] == DEST)
		{
			//先把玩家移动到前面
			map[level][r - 1][c] += PLAYER;
			//然后把玩家从原来的位置删除
			map[level][r][c] -= PLAYER;
		}
		// 能够推箱子的情况:
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
	case 80:
	case 's':
	case 'S':

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
	case 75:
	case 'a':
	case 'A':
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
	case 77:
	case 'd':
	case 'D':
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

// 判断是否通过
bool judge()
{   // 没有箱子就是通关
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


int main(void)
{
	// 游戏都有一个循环
	bool isDone = false;
	while (!isDone)
	{
		// 清除屏幕
		system("cls");
		show();
		if (judge())
		{
			level++;
			if (level == 3)
			{
				printf("恭喜你，通关了，奖励一杯卡布奇洛\n");
				isDone = true;
				exit(EXIT_FAILURE);
			}
			else
				printf("恭喜你，过关了！按任意键进入下一关\n");
		}
		move();
	}

	return 0;
}

