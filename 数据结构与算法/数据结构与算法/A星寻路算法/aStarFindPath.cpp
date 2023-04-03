#include <iostream>
#include <vector>

using namespace std;
// y
#define ROWS 10
// x
#define COLS 10

// 直线代价
#define ZXDJ 10
// 斜线代价
#define XXDJ 14
// 坐标类
struct MyPoint
{
	int y;
	int x;
	int g;
	int f;
	int h;
	void setF() { f = g + h; }
	friend bool operator==(const MyPoint& p1, const MyPoint& p2);
};

bool operator==(const MyPoint& p1, const MyPoint& p2)
{
	if (p1.x == p2.x && p1.y == p2.y)
		return true;
	return false;
}

// 寻路顺序
enum  dirent { p_up, p_left, p_down, p_right, p_lup, p_ldown, p_rup, p_rdown };
// 辅助地图节点类型
struct PathNode
{
	bool isFind;  // 是否走过  0 false 1 true
};

// 八叉树
struct treeNode
{
	MyPoint   pos;
	treeNode* pParent;
	vector<treeNode*> child;   // 指针数组 保存指向当前节点的孩子指针

	treeNode(int x, int y)
	{
		pos.x = x;
		pos.y = y;
		pParent = NULL;
	}

	treeNode(MyPoint p)
	{
		pos = p;
		pParent = NULL;
	}
};

bool canWalk(int map[ROWS][COLS], PathNode pathMap[ROWS][COLS], MyPoint pos);
int getH(MyPoint endPos, MyPoint Pos);


int main(void)
{
	// 0. 地图点类型辅助地图类型辅助地图
	int map[ROWS][COLS] = {

		{ 0, 1, 1, 0, 1, 0, 0, 0, 0, 0  },
		{ 0, 0, 1, 0, 1, 0, 0, 0, 0, 0  },
		{ 0, 0, 1, 0, 1, 0, 0, 0, 0, 0  },
		{ 0, 0, 1, 0, 1, 0, 0, 0, 0, 0  },
		{ 0, 0, 1, 0, 1, 0, 0, 0, 0, 0  },
		{ 0, 0, 1, 0, 1, 0, 0, 0, 0, 0  },
		{ 0, 0, 1, 1, 1, 0, 0, 0, 0, 0  },
		{ 0, 0, 0, 1, 1, 0, 0, 0, 0, 0  },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  },
		{ 0, 0, 0, 0, 1, 0, 0, 0, 0, 0  },

	};
	// 1.2 辅助地图 (记录当前试探方向,记录有没有走过)
	PathNode pathMap[ROWS][COLS] = {0};
	MyPoint begPos = {2,1};
	MyPoint endPos = {3,8};

	// 1. 创建一颗八叉树: 存储寻路过程中所有的节点―找到终点后找出路径
	treeNode* pRoot = NULL;
	// 1.1 起点标记走过
	pathMap[begPos.y][begPos.x].isFind = true;
	// 1.2 起点成为树的根节点
	pRoot = new treeNode(begPos);


	// 2. 准备一个数组: 存储所有待评估的点   // 核心
	vector<treeNode*> buff;
	vector<treeNode*>::iterator it;
	vector<treeNode*>::iterator itMin;

	// 3. 寻路
	// 当前点
	treeNode* pCurrent = pRoot;
	// 临时点
	treeNode* pChild = NULL;
	bool needFind = false;
	while (!needFind)
	{
		//3.1 一个点触发8个点  // 计算代价值g
		for (int i = 0; i < 8; i++)
		{
			pChild = new treeNode(pCurrent->pos);  // 以当前点产生临时点
			switch (i)
			{
			case p_up:
				pChild->pos.y--;
				pChild->pos.g += ZXDJ;
				break;
			case p_down:
				pChild->pos.y++;
				pChild->pos.g += ZXDJ;
				break;
			case p_left:
				pChild->pos.x--;
				pChild->pos.g += ZXDJ;
				break;
			case p_right:
				pChild->pos.x++;
				pChild->pos.g += ZXDJ;
				break;
			case p_lup:
				pChild->pos.x--;
				pChild->pos.y--;
				pChild->pos.g += XXDJ;
				break;
			case p_ldown:
				pChild->pos.x--;
				pChild->pos.y++;
				pChild->pos.g += XXDJ;
				break;
			case p_rup:
				pChild->pos.x++;
				pChild->pos.y--;
				pChild->pos.g += XXDJ;
				break;
			case p_rdown:
				pChild->pos.x++;
				pChild->pos.y++;
				pChild->pos.g += XXDJ;
				break;
			}

			// 能走
			if (canWalk(map, pathMap, pChild->pos))
			{
				//计算和值 和 评估代价
				pChild->pos.h = getH(endPos, pChild->pos);
				pChild->pos.setF();
				// 入树
				pCurrent->child.push_back(pChild);
				pChild->pParent = pCurrent;
				// 存入数组
				buff.push_back(pChild);
			}
			else
			{
				delete pChild;
			}
		} // end of for(i)


		//3.3 从buff数组中找出f值最小的那一个
		itMin = buff.begin();
		for (it = buff.begin(); it != buff.end(); it++)
		{
			itMin = (*itMin)->pos.f < (*it)->pos.f ? itMin : it;
		}
		//3.4当前点变成f值最小的那一个 // 核心
		pCurrent = *itMin;
		// 标记走过
		pathMap[pCurrent->pos.y][pCurrent->pos.x].isFind = true;
		//3.5把f值最小的那一个从buff数组中干掉
		buff.erase(itMin);
		//3.6判断是否找到终点
		if (pCurrent->pos == endPos)
		{
			needFind = true;
			break;
		}
		//3.7如果buff数组空了，整个循环都要结束
		if (buff.size() == 0)
		{
			cout << "没找到终点, 没路了";
			needFind = true;
			break;
		}
	} // end of while(true)

	if (needFind)
	{
		cout << "\n找到终点 \n";
		cout << "path: ";
		while (pCurrent)
		{
			cout << "(" << pCurrent->pos.y << "，"
				<< pCurrent->pos.x << ") ";
			pCurrent = pCurrent->pParent;
		}
		cout << endl;
	}

	return 0;
}


bool canWalk(int map[ROWS][COLS], PathNode pathMap[ROWS][COLS], MyPoint pos)
{
	//不在地图范围内
	if (pos.y < 0 || pos.y >= ROWS || pos.x < 0 || pos.x >= COLS)
		return false;
	//走过
	if (pathMap[pos.y][pos.x].isFind)
		return false;
	// 是障碍物
	if (map[pos.y][pos.x])
		return false;

	return true;
}



int getH(MyPoint endPos, MyPoint Pos)
{
	int x = abs(endPos.x - Pos.x);
	int y = abs(endPos.y - Pos.y);

	return (x + y) * ZXDJ;
}
