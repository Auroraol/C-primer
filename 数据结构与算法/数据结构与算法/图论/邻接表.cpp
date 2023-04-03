#include <stdio.h>
#include <stdlib.h>

#define MAX 100

struct AdjNode // 邻接点表
{
	int index; // 索引编号信息
	struct AdjNode* next; // 指向下一个邻接点的指针
};

struct VexNode  // 节点表
{
	char vertex;  // 顶点信息
	struct AdjNode* first;  // 指向下一个邻接点的指针(第一个邻接点的)
};

struct ALG_Graph  // 
{
	int vertex_num;   //顶点的个数和边的个数
	int edge_num;
	struct VexNode Vex[MAX]; //结构体数组(由顶点的信息和指向邻接点的指针构成)
};

struct ALG_Graph* Create_ALG_Graph(void);
int search_vex(struct ALG_Graph* graph, char c);
void create_adj_node_list(struct ALG_Graph* graph, int i, int j);
void Show_ALG_Graph(struct ALG_Graph* graph);

#if 1

int main(void)
{
	struct ALG_Graph* d_graph;
	d_graph = Create_ALG_Graph();  //调用创建邻接表的函数
	Show_ALG_Graph(d_graph);

	return 0;
}

#endif // 0

struct ALG_Graph* Create_ALG_Graph(void) //// 创建邻接表
{
	struct ALG_Graph* graph;

	graph = (struct ALG_Graph*)malloc(sizeof(struct ALG_Graph));

	printf("请输入顶点个数: ");
	scanf("%d", &graph->vertex_num);
	printf("请输入边的个数: ");
	scanf("%d", &graph->edge_num);
	//while(getchar() != '\n');
	getchar();


	printf("请确定顶点: ");
	for (int i = 0; i < graph->vertex_num; i++)
	{
		//graph->Vex[i].node = getchar(); // Vex[i].node 录入顶点信息
		//while(getchar() != '\n');
		scanf(" %c", &graph->Vex[i].vertex); // Vex[i].node 录入顶点信息
	}

	// 先置为空 
	for (int i = 0; i < graph->vertex_num; i++)
	{
		graph->Vex[i].first = NULL;  // Vex[i].first 初始化指向下一个邻接点的指针(第一个邻接点的)现在应该是空指针
	}

	int count = 1;
	while (graph->edge_num--)  // 录入关系
	{
		char buff[5] = {0};
		int srcIdx, dstIdx;
		printf("请输入第%d条边(A->B): ", count++);
		scanf("%s", buff);
		srcIdx = search_vex(graph, buff[0]);
		dstIdx = search_vex(graph, buff[3]);

		if (dstIdx != -1 && srcIdx != -1)
		{ // 顶点存在, 找到相应的关系开始创建邻接点表了
			create_adj_node_list(graph, srcIdx, dstIdx); // srcIdx 和 dstIdx 是出发点和邻接点
			//create_adj_node_list(graph, dstIdx, srcIdx);  //无向图 
		}

		else
		{
			printf("输入不存在的顶点,请再重新一次.\n");
			graph->edge_num++;
		}
	}
	return graph;
}

int search_vex(struct ALG_Graph* graph, char c)  //找对应的索引号
{
	int i;

	for (i = 0; i < graph->vertex_num; i++)
	{
		if (c == graph->Vex[i].vertex)
			return i;
	}

	return -1;
}
// 创建邻接点表
void create_adj_node_list(struct ALG_Graph* graph, int i, int j)   // 比较复杂的函数  //如图
{
	struct AdjNode* s = (struct AdjNode*)malloc(sizeof(struct AdjNode));  // 创建邻接表
	s->index = j; // 填充的是邻接点的索引编号
	//节点表链接邻接点
	s->next = graph->Vex[i].first;  // 连接
	graph->Vex[i].first = s;        // 指向当前的位置  // first指向会移动
}

void Show_ALG_Graph(struct ALG_Graph* graph)
{
	int i;
	struct AdjNode* t; // 定义邻接点的指针

	printf("显示ALG Graph:\n");  // 显示邻接表

	for (i = 0; i < graph->vertex_num; i++)
	{
		printf("%c: ", graph->Vex[i].vertex); //显示节点信息
		t = graph->Vex[i].first; // 指向第一个邻接点
		while (t != NULL)
		{
			printf("%d ", t->index);  // 把邻接点的索引号
			t = t->next;
		}
		printf("\n");
	}
}