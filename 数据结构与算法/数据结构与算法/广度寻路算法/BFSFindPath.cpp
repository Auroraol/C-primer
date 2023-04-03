#include <iostream>
#include <vector>

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

// 寻路顺序, 这用来判断是那个方向的点
enum  dirent { p_up, p_left, p_down, p_right };
// 辅助地图节点类型
struct PathNode
{
	bool isFind;  // 是否走过  0 false 1 true
};

// 四叉树
struct treeNode
{
	MyPoint   pos; // 数据
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


int main(void)
{
	// 0. 地图点类型辅助地图类型辅助地图
	int map[ROWS][COLS] = {

		{ 0, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 0, 0, 0, 0, 0, 1, 0, 0, 0, 1 },
		{ 0, 0, 1, 0, 0, 1, 0, 1, 0, 1 },
		{ 0, 0, 1, 0, 1, 1, 0, 1, 0, 1 },
		{ 0, 0, 0, 0, 1, 1, 0, 0, 0, 1 },
		{ 0, 0, 1, 0, 1, 1, 0, 1, 1, 1 },
		{ 0, 0, 1, 0, 1, 1, 0, 1, 0, 1 },
		{ 0, 0, 1, 0, 1, 1, 0, 1, 0, 1 },
		{ 0, 0, 1, 0, 0, 0, 0, 0, 0, 1 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },

	};
	// 1.2 辅助地图 (记录当前试探方向,记录有没有走过)
	PathNode pathMap[ROWS][COLS] = {0};
	MyPoint begPos = {1,1};
	MyPoint endPos = {1,8};

	// 1. 创建一颗四叉树:存储寻路过程中所有的节点―找到终点后找出路径
	treeNode* pRoot = NULL;
	// 1.1 起点标记走过
	pathMap[begPos.y][begPos.x].isFind = true;
	// 1.2 起点成为树的根节点
	pRoot = new treeNode(begPos);


	// 2. 准备一个数组:存储当前层的节点   // 核心
	vector<treeNode*> current;  // 当前层
	current.push_back(pRoot);

	vector<treeNode*> next;     // 下一层

	// 3. 寻路
	MyPoint curPos;  // 当前点
	MyPoint tempPos;  // 临时点
	treeNode* pChild = NULL;   // 新节点
	bool isFindEnd = false;
	while (true)
	{
		next.clear();  // 每次清空下一层数组
		// 3.1 一层一层走

		for (int i = 0; i < current.size(); i++)  // 3.2 当前层每一个
		{
			curPos = current.at(i)->pos;
			for (int j = 0; j < 4; j++)  // 当前点引发四个点
			{
				switch (j)  // 判断是那个方向的点 
				{
				case p_up:
					tempPos.y = curPos.y - 1;
					tempPos.x = curPos.x;
					break;
				case p_down:
					tempPos.y = curPos.y + 1;
					tempPos.x = curPos.x;
					break;
				case p_left:
					tempPos.y = curPos.y;
					tempPos.x = curPos.x - 1;
					break;
				case p_right:
					tempPos.y = curPos.y;
					tempPos.x = curPos.x + 1;
					break;
				}

				if (canWalk(map, pathMap, tempPos))//canWalk() 3.2.2判断tempPos能不能走
				{
					//能走:
					//3.2.2.1创建新节点
					pChild = new treeNode(tempPos);
					//3.2.2.2新节点入树 (这个就是N叉树的插入)
					current[i]->child.push_back(pChild);
					pChild->pParent = current[i];
					//3.2.2.3标记走过
					pathMap[tempPos.y][tempPos.x].isFind = true;

					//3.2.2.4 存入下一层的数组中
					next.push_back(pChild);
				}
				// 3.3 如果有一个点是终点， 可以结束了
				if (tempPos == endPos)
				{
					isFindEnd = true;
					break;
				}
			}//end of for(j)

			if (isFindEnd)
				break;
		}// end of for(i)

		// 3.4 如果新的一层节点数为0，地图已经被探索完毕，整个寻路过程结束
		if (next.size() == 0)
			break;

		current = next;  // 切换到下一层
		if (isFindEnd)
			break;
	}// end of while(1);


	if (isFindEnd)
	{
		cout << "\n找到终点 \n";
		cout << "path: ";
		while (pChild)
		{
			cout << "(" << pChild->pos.y << "，"
				<< pChild->pos.x << ") ";
			pChild = pChild->pParent;
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