#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

#define MAX 100

struct AMG_Graph   // 邻接矩阵
{
	int vex_num, edge_num;

	char Vex[MAX];
	int Edge[MAX][MAX];
};

struct AMG_Graph *Create_AMG_Graph(void);
void Show_AMG_Graph(struct AMG_Graph *graph);
int search_vex(struct AMG_Graph *graph, char c);
void DFS_AMG(struct AMG_Graph *graph);

int main(void)
{
	struct AMG_Graph *d_graph;

	d_graph = Create_AMG_Graph();
	Show_AMG_Graph(d_graph);

	printf("Traverse the graph through DFS:\n");
	DFS_AMG(d_graph);   // 调用深度优先的实现

	return 0;
}

struct AMG_Graph *Create_AMG_Graph(void)
{
	int i, j;
	char u, v;

	struct AMG_Graph *graph;

	graph = (struct AMG_Graph *)malloc(sizeof(struct AMG_Graph));

	printf("Please enter the number of vex: ");
	scanf("%d", &graph->vex_num);
	printf("Please enter the number of edge: ");
	scanf("%d", &graph->edge_num);

	while(getchar() != '\n');

	printf("Please enter vertex:\n");
	for(i = 0; i < graph->vex_num; i++)
	{
		graph->Vex[i] = getchar();
		while(getchar() != '\n');
	}

	for(i = 0; i < graph->vex_num; i++)
	{
		for(j = 0; j < graph->vex_num; j++)
			graph->Edge[i][j] = 0;
	}

	while(graph->edge_num--)
	{
		printf("Please enter the vex that connect each other by edge:\n");
		u = getchar();
		while(getchar() != '\n');
		v = getchar();
		while(getchar() != '\n');

		i = search_vex(graph, u);
		j = search_vex(graph, v);

		if(i != -1 && j != -1)
			graph->Edge[i][j] = 1;
		else
		{
			printf("You have entered wrong vex, please enter again.\n");
			graph->edge_num++;
		}

	}

	return graph;
}

void Show_AMG_Graph(struct AMG_Graph *graph)
{
	int i, j;

	printf("Show the vex: \n");
	for(i = 0; i < graph->vex_num; i++)
		printf("%c ", graph->Vex[i]);
	printf("\n");

	printf("Show the adjacency matrices:\n");
	for(i = 0; i< graph->vex_num; i++)
	{
		for(j = 0; j < graph->vex_num; j++)
			printf("%d\t", graph->Edge[i][j]);
		printf("\n");
	}
}

int search_vex(struct AMG_Graph *graph, char c)
{
	int i;

	for(i = 0; i < graph->vex_num; i++)
	{
		if(c == graph->Vex[i])
			return i;
	}

	return -1;
}

// 深度优先实现
void DFS_AMG(struct AMG_Graph *graph)   
{
	int i, j;
	int u;

	int visited[MAX] = {0};

	for(i = 0; i < graph->vex_num; i++)  // 遍历所有点
	{
		if(visited[i] == 0)
		{
			printf("%c ", graph->Vex[i]);  // 打印第一个顶点
			visited[i] = 1;
			push(i);   // 入栈
			while(!is_empty())
			{
				u = stack[top-1]; // 通过访问top获取到编号, ps: top指针指向空位置的  (按上图所例 第二次 u为1了代表b 第三次 为2)
				for(j = 0; j < graph->vex_num; j++)
				{
					if((graph->Edge[u][j] == 1) && (visited[j] == 0))   // 不为0并且未标记的就遍历
					{
						visited[j] = 1;  // 标志
						push(j);  // 入栈
						printf("%c ", graph->Vex[j]);  // 显示对应字符
						break;   // 结束这个循环for  // 不 用break就变成广度优先了 (关键)
					}
				}
				if(j == graph->vex_num)   // 找到来了最后的点开始往后退,有进行while循环 (无路可走)
					pop(); // 出栈了
			}
		}
	}
	printf("\n");
}
