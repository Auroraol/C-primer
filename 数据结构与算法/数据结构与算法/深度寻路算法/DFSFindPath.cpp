#include "myStack.h"
#include <iostream>


using namespace std;

// y
#define ROWS 10
// x
#define COLS 10

// 坐标
struct MyPoint
{
	int y;
	int x;
	/*bool operator==(const MyPoint& p)
	{
		if (p.x == this->x && p.y == this->y)
			return true;
		return false;
	}*/
	friend bool operator==(const MyPoint& p1, const MyPoint& p2);
};

bool operator==(const MyPoint& p1, const MyPoint& p2)
{
	if (p1.x == p2.x && p1.y == p2.y)
		return true;
	return false;
}


// 寻路顺序
enum  dirent { p_up, p_left, p_down, p_right };
// 辅助地图节点类型
struct PathNode
{
	int dir;      // 当前试探方向
	bool isFind;  // 是否走过  0 false 1 true
};


int main(void)
{
	// 1. 寻路前的准备
	// 1.1 地图
	int map[ROWS][COLS] = {

		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 0, 1, 0, 1, 1, 0, 1, 0, 1 },
		{ 1, 0, 1, 0, 1, 0, 0, 1, 0, 1 },
		{ 1, 0, 1, 0, 1, 1, 0, 1, 0, 1 },
		{ 1, 0, 0, 0, 1, 1, 0, 0, 0, 1 },
		{ 1, 0, 1, 0, 1, 1, 0, 1, 1, 1 },
		{ 1, 0, 1, 0, 1, 1, 0, 1, 1, 1 },
		{ 1, 0, 1, 0, 1, 1, 0, 1, 1, 1 },
		{ 1, 0, 1, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },

	};

	// 1.2 辅助地图 (记录当前试探方向,记录有没有走过)
	PathNode pathMap[ROWS][COLS] = {0};

	// 1.3 栈
	MyStack<MyPoint> stack;

	// 1.4 起点  终点 标记起点走过 起点入栈
	MyPoint begPos = {1,1};
	MyPoint endPos = {1,8};
	// 1.4.1 标记起点走过 
	pathMap[begPos.y][begPos.x].isFind = true;
	// 1.4.2起点入栈
	stack.push(begPos);

	// 2. 寻路
	MyPoint currentPos = begPos;
	MyPoint searchPos;  //试探点
	bool isFindEnd = false;
	while (true)
	{
		// 2.1 确定试探点
		searchPos = currentPos;
		//2.1.1 根据当前点的当前试探方向，确定试探点
		switch (pathMap[currentPos.y][currentPos.x].dir)
		{
		case p_up:
			searchPos.y--;
			pathMap[currentPos.y][currentPos.x].dir++;
			// 2.2 判断能不能走(走过的不走了)
			if (pathMap[searchPos.y][searchPos.x].isFind == false
				&& map[searchPos.y][searchPos.x] == 0)  // 没走过并且不是障碍物
			{
				// 2.3 走
				currentPos = searchPos;

				// 2.4 入栈
				stack.push(searchPos);
				// 2.5 标记走过
				pathMap[searchPos.y][searchPos.x].isFind = true;
			}
			break;
		case p_left:
			searchPos.x--;
			pathMap[currentPos.y][currentPos.x].dir++;
			// 2.2 判断能不能走
			if (pathMap[searchPos.y][searchPos.x].isFind == false
				&& map[searchPos.y][searchPos.x] == 0)  // 没走过并且不是障碍物
			{
				// 2.3 走
				currentPos = searchPos;

				// 2.4 入栈
				stack.push(searchPos);
				// 2.5 标记走过
				pathMap[searchPos.y][searchPos.x].isFind = true;
			}
			break;
		case p_down:
			searchPos.y++;
			pathMap[currentPos.y][currentPos.x].dir++;
			// 2.2 判断能不能走
			if (pathMap[searchPos.y][searchPos.x].isFind == false && map[searchPos.y][searchPos.x] == 0)  // 没走过并且不是障碍物
			{
				// 2.3 走
				currentPos = searchPos;

				// 2.4 入栈
				stack.push(searchPos);
				// 2.5 标记走过
				pathMap[searchPos.y][searchPos.x].isFind = true;
			}
			break;

		case p_right:
			searchPos.x++;
			/*pathMap[currentPos.y][currentPos.x].dir++;*/  // 不用在改方向了
			// 2.2 判断能不能走
			if (pathMap[searchPos.y][searchPos.x].isFind == false
				&& map[searchPos.y][searchPos.x] == 0)  // 没走过并且不是障碍物
			{
				// 2.3 走
				currentPos = searchPos;

				// 2.4 入栈
				stack.push(searchPos);
				// 2.5 标记走过
				pathMap[searchPos.y][searchPos.x].isFind = true;
			}
			else // 2.6 不能走就必须回退
			{
				stack.pop();  // 删除栈顶元素
				currentPos = stack.getTop(); // 跳到当前栈顶元素
			}
			break;
		default: break;
		}


		// 如果找到终点
		if (currentPos == endPos)
		{
			isFindEnd = true;
			break;
		}

		// 如果整个地图中都没有终点
		if (stack.isEmpty())
			break;
	}


	// 判断是什么原因结束寻路的
	if (isFindEnd)
	{
		cout << "\n找到终点 \n";
		cout << "path: ";
		while (!stack.isEmpty())
		{
			cout << "(" << stack.getTop().y << "，"
				<< stack.getTop().x << ") ";
			stack.pop();
		}
		cout << endl;
	}
	else
	{
		cout << "\n没有找到终点!\n";
	}

	return 0;
}

