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

	printf("Traverse the graph through BFS:\n");  // 显示用bfs的方式遍历 
	BFS_ALG(d_graph);  // 邻接表

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

void BFS_ALG(struct ALG_Graph *graph)
{
	int u;
	struct AdjNode *p;
	int n;

	int visited[MAX] = {0};

	printf("%c ", graph->Vex[0].node);
	visited[0] = 1;
	enqueue(0);

	while(!is_empty())
	{
		u = dequeue();
		p = graph->Vex[u].first;

		while(p)
		{
			n = p->index;
			if(visited[n] == 0)
			{
				visited[n] = 1;
				enqueue(n);
				printf("%c ", graph->Vex[n].node);
			}
			p = p->next;
		}
	}
	printf("\n");
}











