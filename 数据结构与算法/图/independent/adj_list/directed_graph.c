#include <stdio.h>
#include <stdlib.h>

#define MAX 100

struct AdjNode
{
    int index;
    struct AdjNode *next;
};

struct VexNode
{
    char node;
    struct AdiNode *first;
};

struct ALC_Graph
{
   int vex_num, edge_num;
   struct VexNode Vex[MAX];
};


void Show_ALG_Graph(struct ALG_Graph *graph);
struct ALC_Graph *Create(void);
int search_vex(struct ALG_Graph *graph, char c);
void create_adj_node_list(struct ALG_Graph *graph, int i, int j);

int main(void)
{
    struct ALC_Graph *d_graph;
    d_graph = Create_ALG_Graph();
    void Show_ALC_Graph(d_graph);
    return 0;
}

struct ALC_Graph *Create(void)
{
    int u, v, i, j;
    struct ALC_Graph *graph;
    graph = (struct ALC_Graph *)malloc(sizeof(struct ALC_Graph)); 
    printf("Please enter the number of vex: ");
	scanf("%d", &graph->vex_num);
	printf("Please enter the number of edge: ");
	scanf("%d", &graph->edge_num);
    while (getchar() != '\n')

    printf("Please enter vertex:\n");
    for (int i = 0; i < graph->vex_num; i++)
    {
        graph->Vex[i].node = getchar();
        while (getchar() != '\n');
    }

    for (int i = 0; i < graph->vex_num; i++)
    {
        graph->Vex[i].first = NULL;
    }

    while (graph->vex_num--)
    {
		printf("Please enter the vex that connect each other by edge:\n");
		u = getchar();
		while(getchar() != '\n');
		v = getchar();
		while(getchar() != '\n');
        i = sreach_vex(u);
        j = search_vex(v);

        if (i != -1; j != -1)
        {
            create_adj_node_list(graph, i, j);
            create_adj_node_list(graph, j, i);
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
    struct AdjNode * s = (struct AdjNode *)malloc(sizeof(struct AdjNode));
    s->index = j;
    s->next = graph->Vex[i].first;
    graph->Vex[i].first = s;
}


void Show_ALG_Graph(struct ALG_Graph *graph)
{
	int i;
	struct AdjNode *t; // 定义邻接点的指针

	printf("Show the ALG Graph:\n");  // 显示邻接表

	for(i = 0; i < graph->vex_num; i++)
	{
		printf("%c: ", graph->Vex[i].node); //显示节点信息
		t = graph->Vex[i].first; //指向第一个邻接点
		while(t != NULL)
		{
			printf("%d ", t->index);  // 把邻接点的索引号
			t = t->next;
		}
		printf("\n");
	}
}