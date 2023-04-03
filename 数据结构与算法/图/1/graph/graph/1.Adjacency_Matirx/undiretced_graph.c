#include <stdio.h>
#include <stdlib.h>

#define MAX 100

struct AMG_Graph
{
	int vex_num, edge_num;

	char Vex[MAX];
	int Edge[MAX][MAX];
};

struct AMG_Graph *Create_AMG_Graph(void);
void Show_AMG_Graph(struct AMG_Graph *graph);
int search_vex(struct AMG_Graph *graph, char c);

int main(void)
{
	struct AMG_Graph *ud_graph;

	ud_graph = Create_AMG_Graph();
	Show_AMG_Graph(ud_graph);

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
			graph->Edge[i][j] = graph->Edge[j][i] = 1;
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
