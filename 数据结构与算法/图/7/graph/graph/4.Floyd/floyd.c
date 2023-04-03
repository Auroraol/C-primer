#include <stdio.h>
#include <stdlib.h>
#include <math.h>  // 数学的头文件

#define MAX 100

struct AMG_Graph  // 邻接矩阵
{
	int vex_num, edge_num;

	char Vex[MAX];
	int Edge[MAX][MAX];
};

struct AMG_Graph *Create_AMG_Graph(void);
void Show_AMG_Graph_dist_p(struct AMG_Graph *graph);
int search_vex(struct AMG_Graph *graph, char c);
void Floyd(struct AMG_Graph *graph);

double dist[MAX][MAX];   // 最短距离的数组   用double的原因是溢出
int p[MAX][MAX];        // 前驱点的数组

int main(void)
{
	struct AMG_Graph *d_graph;
	char start, end;
	int s, e;

	d_graph = Create_AMG_Graph();
	Show_AMG_Graph_dist_p(d_graph);

	Floyd(d_graph);  // 调用floyd函数
	printf("\n\nNow show the shortest distance matrix:\n");
	Show_AMG_Graph_dist_p(d_graph);

	printf("Please enter the start and end point:\n");  // 输入起末位置
	scanf("%c %c", &start, &end);
	s = search_vex(d_graph, start);  // 得到所在的编号
	e = search_vex(d_graph, end);
	printf("The shortest distance between %c and %c is %.1f.\n", start, end, dist[s][e]);   // 显示距离  //dist[s][e]现在存储的就是最短距离

	return 0;
}

// 创建
struct AMG_Graph *Create_AMG_Graph(void)
{
	int i, j;
	char u, v;
	double l;

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
		{
			graph->Edge[i][j] = 0;

			if(i == j)  // a到a,b到b 就设置0
				dist[i][j] = 0;   
			else
				dist[i][j] = INFINITY;	//无穷大

			p[i][j] = -1; // 前驱点的数组
		}	
	}

	while(graph->edge_num--)
	{
		printf("Please enter the vex that connect each other by edge:\n");
		u = getchar();
		while(getchar() != '\n');
		v = getchar();
		while(getchar() != '\n');

		printf("Please enter the distance between the two vex:\n");    // 提示输入 两个顶点的距离
		scanf("%lf", &l);
		while(getchar() != '\n');

		i = search_vex(graph, u);   // 得到所在的编号
		j = search_vex(graph, v);

		if(i != -1 && j != -1)  // 有效的
		{
			graph->Edge[i][j] = 1;
			dist[i][j] = l;    // 距离就是输入的l
			p[i][j] = i;       // 前驱点就是i的值
		}
		else
		{
			printf("You have entered wrong vex, please enter again.\n");
			graph->edge_num++;
		}

	}

	return graph;
}

//显示内容
void Show_AMG_Graph_dist_p(struct AMG_Graph *graph)
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

	printf("Show the distance matrices:\n");   // 显示距离的矩阵
	for(i = 0; i< graph->vex_num; i++)
	{
		for(j = 0; j < graph->vex_num; j++)
			printf("%.1f\t", dist[i][j]);
		printf("\n");
	}

	printf("Show the pre point matrices:\n");  // 显示前驱点的矩阵
	for(i = 0; i< graph->vex_num; i++)
	{
		for(j = 0; j < graph->vex_num; j++)
			printf("%d\t", p[i][j]);
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

// 差点法
void Floyd(struct AMG_Graph *graph)    
{
	int k, i, j;

	for(k = 0; k < graph->vex_num; k++)  // 外层依次去选择插入点
	{
		for(i = 0; i < graph->vex_num; i++)  // 依次遍历数组所有点
		{
			for(j = 0; j < graph->vex_num; j++)  // 依次遍历数组所有点
			{
				if(dist[i][j] > dist[i][k] + dist[k][j])  // 判断距离大小 . k是插入点
				{
					dist[i][j] = dist[i][k] + dist[k][j];  // 更新一下距离
					p[i][j] = p[k][j];  //   更新前驱点
				}
			}
		}
	}
}


