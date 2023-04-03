#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

#define MAX 100

struct AdjNode
{
	int index;
	struct AdjNode *next;
};

struct VexNode
{
	char node;
	struct AdjNode *first;
};

struct ALG_Graph
{
	int vex_num, edge_num;
	struct VexNode Vex[MAX];
};

struct ALG_Graph *Create_ALG_Graph(void);
int search_vex(struct ALG_Graph *graph, char c);
void create_adj_node_list(struct ALG_Graph *graph, int i, int j);
void Show_ALG_Graph(struct ALG_Graph *graph);
void BFS_ALG(struct ALG_Graph *graph);

int main(void)
{
	struct ALG_Graph *d_graph;
	d_graph = Create_ALG_Graph();
	Show_ALG_Graph(d_graph);

	printf("Traverse the graph through BFS:\n");  // 提示信息通过广度优先
	BFS_ALG(d_graph);  // 调用

	return 0;
}

struct ALG_Graph *Create_ALG_Graph(void)
{
	int i, j;
	char u, v;

	struct ALG_Graph *graph;

	graph = (struct ALG_Graph *)malloc(sizeof(struct ALG_Graph));

	printf("Please enter the number of vex: ");
	scanf("%d", &graph->vex_num);
	printf("Please enter the number of edge: ");
	scanf("%d", &graph->edge_num);
	while(getchar() != '\n');

	printf("Please enter vertex:\n");
	for(i = 0; i < graph->vex_num; i++)
	{
		graph->Vex[i].node = getchar();
		while(getchar() != '\n');
	}

	for(i = 0; i < graph->vex_num; i++)
	{
		graph->Vex[i].first = NULL;
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
			create_adj_node_list(graph, i, j);
		else
		{
			printf("You have entered wrong vex, please enter again.\n");
			graph->edge_num++;
		}
	}
	return graph;
}

int search_vex(struct ALG_Graph *graph, char c)
{
	int i;

	for(i = 0; i < graph->vex_num; i++)
	{
		if(c == graph->Vex[i].node)
			return i;
	}

	return -1;
}

void create_adj_node_list(struct ALG_Graph *graph, int i, int j)
{
	struct AdjNode *s = (struct AdjNode *)malloc(sizeof(struct AdjNode));
	s->index = j;
	s->next = graph->Vex[i].first;
	graph->Vex[i].first = s;
}

void Show_ALG_Graph(struct ALG_Graph *graph)   
{
	int i;
	struct AdjNode *t;

	printf("Show the ALG Graph:\n");

	for(i = 0; i < graph->vex_num; i++)
	{
		printf("%c: ", graph->Vex[i].node);
		t = graph->Vex[i].first;
		while(t != NULL)
		{
			printf("%d ", t->index);
			t = t->next;
		}
		printf("\n");
	}
}

void BFS_ALG(struct ALG_Graph *graph)   // 邻接表的广度优先实现
{
	int u;
	struct AdjNode *p;
	int n;
	int i;

	int visited[MAX] = {0};  // 定义的全零数组

for(i = 0; i < graph->vex_num; i++)   //增加一个for循环 . 依次访问所有的.一个不啦
{
  if(visited[i] == 0) //如果没有被访问就执行
  {
	printf("%c ", graph->Vex[i].node);  // 打印显示第一个顶点
	visited[i] = 1;   // 标记
	enqueue(i);   // 入队列

	while(!is_empty())
	{
		u = dequeue();  // 初队列,出的是编号
		p = graph->Vex[u].first;   // 访问第一个指针

		while(p)   // 不为空执行
		{
			n = p->index;  // 在下一个
			if(visited[n] == 0)   //  判断是不是没有访问过
			{
				visited[n] = 1;  // 标记
				enqueue(n);
				printf("%c ", graph->Vex[n].node);  // 打印显示
			}
			p = p->next;  // 更新位置
		}
	}
  }
}
	printf("\n");
}











