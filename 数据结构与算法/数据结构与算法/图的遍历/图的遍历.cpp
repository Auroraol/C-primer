#include <stdio.h>
#include <string.h>
#include <queue>
// 图结构

#define WUXIANG 0
#define VERTEXS 6

struct Graph
{
	int vertexs;
	int edges;
	char* pVertex;
	//int* ppEdge;     // 技巧一维数组表示二维数组
	int** ppEdge;      // 用动态二维数组
};
// 创建图对象
Graph* createGraph();
// 初始化图对象
void initGraph(Graph* g);
// 初始化图对象
void initGraph(Graph* g, int vertexs, int lines, char* str, int map[VERTEXS][VERTEXS]);
// 释放图对象
void destroyGraph(Graph* g);
// 获取顶点所在的下标, 如果没与返回-1
int _getIdx(Graph* g, char c);
// 显示图
//
void show(Graph* g);
// 图的遍历
void travers(Graph* g, char v, bool isDeep);
// 找图中某个顶点的第一个相邻顶点, 没有返回-1
int findFirstVertex(Graph* g, char v, bool isFind[VERTEXS]);
// 找图中某个顶点的下一个相邻顶点, 没有返回-1,找v顶点的idx顶点的下一个顶点
int findNextVertex(Graph* g, char v, int idx);
// 深度优先搜索
void dfs(Graph* g, char v, bool isFind[VERTEXS]);
// 广度优先搜索
void bfs(Graph* g, char v, bool isFind[VERTEXS]);

int main(void)
{
	char buff[7] = "ABCDEF";
	int map[VERTEXS][VERTEXS] = {
		{0 ,0 ,1, 0, 0, 0},
		{0 ,0 ,1, 0, 0, 0},
		{1 ,1 ,0, 1, 1, 1},
		{0 ,0 ,1, 0, 0, 0},
		{0 ,0 ,1, 1, 0, 0},
		{0 ,0 ,1, 0, 0, 0},
	};

	// 创建图对象
	Graph* g = createGraph();
	// 初始化图
//	initGraph(g);
	initGraph(g, VERTEXS, 6, buff, map);
	// 显示图
	show(g);
	//
	printf("\nDFS: ");
	travers(g, 'C', true);
	printf("\n");
	printf("BFS: ");
	travers(g, 'C', false);
	printf("\n");
	// 释放图对象
	destroyGraph(g);
	//while (1);
	return 0;
}

//释放图对象
void destroyGraph(Graph* g)
{
	delete g;
}

//创建图对象
Graph* createGraph()
{
	Graph* graph = new Graph;
	graph->edges = graph->vertexs = 0;
	graph->ppEdge = NULL;
	graph->pVertex = NULL;

	// 或者 memset(grap, 0, sizeof(Graph))
	return graph;
}

// 初始化图对象
void initGraph(Graph* g, int vertexs, int lines, char* str, int map[VERTEXS][VERTEXS])
{
	g->vertexs = vertexs;
	g->edges = lines;
	// 开内存
	g->pVertex = new char[g->vertexs];  // 存放顶点信息的一维数组

	// 边的二维数组
	g->ppEdge = new int* [g->vertexs];
	for (int i = 0; i < g->vertexs; i++)
	{
		g->ppEdge[i] = new int[g->vertexs];
		memset(g->ppEdge[i], 0, sizeof(int) * g->vertexs);
	}

	memcpy(g->pVertex, str, VERTEXS);
	for (int i = 0; i < VERTEXS; i++)
	{
		for (int j = 0; j < VERTEXS; j++)
		{
			g->ppEdge[i][j] = map[i][j];
		}
	}
}

// 初始化图对象
void initGraph(Graph* g)
{
	printf("请输入顶点个数: ");
	scanf("%d", &(g->vertexs));
	printf("请输入边的个数: ");
	scanf("%d", &(g->edges));

	// 开内存
	g->pVertex = new char[g->vertexs + 1];  // 存放顶点信息的一维数组

	// 边的二维数组
	g->ppEdge = new int* [g->vertexs];
	for (int i = 0; i < g->vertexs; i++)
	{
		g->ppEdge[i] = new int[g->vertexs];
		memset(g->ppEdge[i], 0, sizeof(int) * g->vertexs);
	}

	// 赋值
	printf("请输入顶点: ");
	scanf("%s", g->pVertex);

	char buff[5] = {0};
	int srcIdx, dstIdx;
	for (int i = 0; i < g->edges; i++)
	{
		printf("请输入第%d条边(A->B): ", i + 1);
		scanf("%s", buff);
		srcIdx = _getIdx(g, buff[0]);
		dstIdx = _getIdx(g, buff[3]);
		g->ppEdge[srcIdx][dstIdx] = 1;
#if WUXIANG
		// 如果是无向图,加上一行代码
		// g->ppEdge[dstIdx][srcIdx] = 1;
	}
#endif
	}
}

int _getIdx(Graph* g, char c)
{
	for (int i = 0; i < g->vertexs; i++)
	{
		if (c == g->pVertex[i]) return i;
	}
	return -1;
}

void show(Graph* g)
{
	for (int i = 0; i <= g->vertexs; i++)
	{
		for (int j = 0; j <= g->vertexs; j++)
		{
			if (i == 0 && j == 0)//左上角空置
				printf(" ");
			else if (i == 0)
			{
				printf("%c ", g->pVertex[j - 1]);
			}
			else if (j == 0)
				printf("%c ", g->pVertex[i - 1]);
			else
			{
				printf("%d ", g->ppEdge[i - 1][j - 1]);
			}
		}
		printf("\n");
	}
}

// 图遍历
void travers(Graph* g, char v, bool isDeep)
{
	bool isFind[VERTEXS] = {0};   // 存储已经遍历过的顶点
	if (isDeep)
	{
		dfs(g, v, isFind);
	}
	else
	{
		bfs(g, v, isFind);
	}
	printf("\n");
}

// 找图中某个顶点的第一个相邻顶点, 没有返回-1  // cahr v 顶点
int findFirstVertex(Graph* g, char v, bool isFind[VERTEXS])
{
	int n = _getIdx(g, v);
	for (int i = 0; i < VERTEXS; i++)
	{
		if (isFind[i])
			continue;
		if (1 == g->ppEdge[n][i])
			return i;
	}
	return -1;
}

// 找中途某个顶点的下一个相邻顶点, 没有返回-1
//找v顶点的idx顶点的下一个顶点
int findNextVertex(Graph* g, char v, int idx)
{
	int n = _getIdx(g, v);
	for (int i = idx + 1; i < VERTEXS; i++)
	{
		if (1 == g->ppEdge[n][i])
			return i;
	}
	return -1;
}

// 深度优先
void dfs(Graph* g, char v, bool isFind[VERTEXS])
{
	//找v的第一个相邻顶点x，继续找x的第一个相邻顶点―直到没有相邻顶点就结束
	int cur = _getIdx(g, v);
	isFind[cur] = true;  // 标记找过
	printf("%c", v);
	int nextIdx = findFirstVertex(g, v, isFind);  // 获取当前顶点的第一个相邻顶点

	// 然后一条路走到黑
	while (nextIdx != -1) //有路
	{
		if (!isFind[nextIdx]) //一个顶点没有遍历过,及没有走过
		{
			//printf("%c", g->pVertex[nextIdx]);
			//isFind[nextIdx] = true;
			dfs(g, g->pVertex[nextIdx], isFind);
		}
		// 走过
		//找v的下一个相邻顶点，一直到都找完结束
		nextIdx = findNextVertex(g, v, nextIdx);
	}
}

// 广度优先(借助队列)
void bfs(Graph* g, char v, bool isFind[VERTEXS])
{
	using namespace std;
	queue <int> q;
	q.push(_getIdx(g, v));
	isFind[_getIdx(g, v)] = true;
	printf("%c", v);

	int headIdex;
	int idx;
	//  去看
	while (!q.empty())
	{
		headIdex = q.front();
		q.pop();

		int idx = findFirstVertex(g, g->pVertex[headIdex], isFind);  // 找第一个顶点
		while (idx != -1)
		{
			if (!isFind[idx])
			{
				isFind[idx] = true;
				printf("%c", g->pVertex[idx]);
				q.push(idx);
			}
			idx = findNextVertex(g, g->pVertex[headIdex], idx);  // 找下一个
		}
	}
}