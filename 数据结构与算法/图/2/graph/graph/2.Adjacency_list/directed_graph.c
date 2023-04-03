#include <stdio.h>
#include <stdlib.h>

#define MAX 100

struct AdjNode // 邻接点表
{
	int index; // 索引编号信息
	struct AdjNode *next; // 指向下一个邻接点的指针
};

struct VexNode  // 节点表
{
	char node;  // 顶点信息
	struct AdjNode *first;  // 指向下一个邻接点的指针(第一个邻接点的)
};

struct ALG_Graph  // 
{
	int vex_num, edge_num;   //顶点的个数和边的个数
	struct VexNode Vex[MAX]; //结构体数组(由顶点的信息和指向邻接点的指针构成)
};

struct ALG_Graph *Create_ALG_Graph(void);
int search_vex(struct ALG_Graph *graph, char c);
void create_adj_node_list(struct ALG_Graph *graph, int i, int j);
void Show_ALG_Graph(struct ALG_Graph *graph);

int main(void)
{
	struct ALG_Graph *d_graph;
	d_graph = Create_ALG_Graph();  //调用创建邻接表的函数
	Show_ALG_Graph(d_graph);

	return 0;
}

struct ALG_Graph *Create_ALG_Graph(void) //// 创建邻接表
{
	int i, j;
	char u, v;

	struct ALG_Graph *graph;

	graph = (struct ALG_Graph *)malloc(sizeof(struct ALG_Graph));

	printf("Please enter the number of vex: ");
	scanf("%d", &graph->vex_num);
	printf("Please enter the number of edge: ");
	scanf("%d", &graph->edge_num);
	//while(getchar() != '\n');
	getchar();
	 

	printf("Please enter vertex:\n");
	for(i = 0; i < graph->vex_num; i++)
	{
		//graph->Vex[i].node = getchar(); // Vex[i].node 录入顶点信息
		//while(getchar() != '\n');
		scanf(" %c", &graph->Vex[i].node); // Vex[i].node 录入顶点信息
	}

	for(i = 0; i < graph->vex_num; i++)
	{
		graph->Vex[i].first = NULL;  // Vex[i].first 初始化指向下一个邻接点的指针(第一个邻接点的)现在应该是空指针
	}

	while(graph->edge_num--)  // 关系
	{
		printf("Please enter the vex that connect each other by edge:\n");
		u = getchar();
		while(getchar() != '\n');
		v = getchar();
		while(getchar() != '\n');

		i = search_vex(graph, u);
		j = search_vex(graph, v);

		if(i != -1 && j != -1)   // 找到相应的关系开始创建邻接点表了
			create_adj_node_list(graph, i, j); // i 和 j 是出发点和邻接点
		else
		{
			printf("You have entered wrong vex, please enter again.\n");
			graph->edge_num++;
		}
	}
	return graph;
}

int search_vex(struct ALG_Graph *graph, char c)  //找对应的索引号
{
	int i;

	for(i = 0; i < graph->vex_num; i++)
	{
		if(c == graph->Vex[i].node)
			return i;
	}

	return -1;
}
// 创建邻接表
void create_adj_node_list(struct ALG_Graph *graph, int i, int j)   // 比较复杂的函数  //如图
{
	struct AdjNode *s = (struct AdjNode *)malloc(sizeof(struct AdjNode));  // 创建邻接表
	s->index = j; // 填充的是邻接点的索引编号
	s->next = graph->Vex[i].first;  //连接
	graph->Vex[i].first = s;  // 指向当前的位置
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












