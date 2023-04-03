#include <stdio.h>
#include <string.h>
// 图结构

#define WUXIANG 0
#define VERTEXS 6

struct Graph
{
	int vertex_num;        // 顶点个数
	int edge_num;          // 边个数
	char* pVertex;
	//int* ppEdge;     // 技巧一维数组表示二维数组
	int** ppEdge;      // 用动态二维数组

};

// 创建图对象
Graph* createGraph();
// 初始化图对象
void initGraph(Graph* g);
// 初始化图对象
void initGraph(Graph* g, int vertex_num, int lines, char* str, int map[VERTEXS][VERTEXS]);
// 释放图对象
void destroyGraph(Graph* g);
// 获取顶点所在的下标, 如果没与返回-1 
int _getIdx(Graph* g, char c);
// 显示图
void show(Graph* g);

#if 0
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
	// 释放图对象
	destroyGraph(g);
	while (1);
	return 0;
}
#endif

//创建图对象
Graph* createGraph()
{
	Graph* graph = new Graph;
	graph->edge_num = graph->vertex_num = 0;
	graph->ppEdge = NULL;
	graph->pVertex = NULL;

	// 或者 memset(grap, 0, sizeof(Graph))
	return graph;
}

// 初始化图对象
void initGraph(Graph* g, int vertexs, int lines, char* str, int map[VERTEXS][VERTEXS])
{
	g->vertex_num = vertexs;
	g->edge_num = lines;
	// 开内存
	g->pVertex = new char[g->vertex_num];  // 存放顶点信息的一维数组

	// 边的二维数组
	g->ppEdge = new int* [g->vertex_num];
	for (int i = 0; i < g->vertex_num; i++)
	{
		g->ppEdge[i] = new int[g->vertex_num];
		memset(g->ppEdge[i], 0, sizeof(int) * vertexs);
	}

	memcpy(g->pVertex, str, vertexs);
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
	scanf_s("%d", &(g->vertex_num));
	printf("请输入边的个数: ");
	scanf_s("%d", &(g->edge_num));

	// 开内存
	g->pVertex = new char[g->vertex_num + 1];  // 存放顶点信息的一维数组

	// 边的二维数组
	g->ppEdge = new int* [g->vertex_num];
	for (int i = 0; i < g->vertex_num; i++)
	{
		g->ppEdge[i] = new int[g->vertex_num];
		memset(g->ppEdge[i], 0, sizeof(int) * g->vertex_num);
	}

	// 赋值
	printf("请输入顶点: ");
	scanf("%s", g->pVertex);

	char buff[5] = {0};
	int srcIdx, dstIdx;
	for (int i = 0; i < g->edge_num; i++)
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

//释放图对象
void destroyGraph(Graph* g)
{


}

int _getIdx(Graph* g, char c)
{
	for (int i = 0; i < g->vertex_num; i++)
	{
		if (c == g->pVertex[i]) return i;
	}
	return -1;
}

void show(Graph* g)
{
	for (int i = 0; i <= g->vertex_num; i++)
	{
		for (int j = 0; j <= g->vertex_num; j++)
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