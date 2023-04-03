#include <stdio.h>
#include <stdlib.h>
#define MAX 100

struct AMG_Graph
{
    int vex_num, edge_num;   // 顶点的个数和边的的个数
    char Vex[MAX];           //一维数组(顶点信息)
    int Edge[MAX][MAX];     // 二维数组(顶点之间的关系)
};

struct AMG_Graph *Create_AMG_Graph(void);
void show_AMG_Graph(struct AMG_Graph *graph);
int search_vex(struct AMG_Graph *graph, char c);

int main(void)
{
    
    struct AMG_Graph *ud_graph;
    ud_graph = Create_AMG_Graph(); //调用创建图的函数
    show_AMG_Graph(ud_graph);
    return 0;
}

// 创建图
struct AMG_Graph *Create_AMG_Graph(void)
{
    int i , j;
    char u, v; //定义的两个有关系的顶点

    struct AMG_Graph *graph;
    graph = (struct AMG_Graph *)malloc(sizeof(struct AMG_Graph));
     
    printf("Please  enter the number of vex: ");
    scanf("%d", &graph->vex_num);
    printf("Pease enter ten number of edge: ");
    scanf("%d", &graph->edge_num);
    getchar();
    /*
    while (getchar() != '\n');
    */

    printf("Please enter vertex: \n"); // 请输入一个顶点的信息(存入到一维数组里)
    for (i = 0; i < graph->vex_num; i++)
        scanf(" %c", &graph->Vex[i]);
    /*{
        graph->Vex[i] = getchar();
        while(getchar() != '\n');
    }*/   
    for (i = 0; i < graph->vex_num; i++)
    {
        for (j = 0; j < graph->vex_num; j++)
            graph->Edge[i][j] = 0;  //初始时全是零
    }

    while (graph->edge_num--) //录入顶点之间的关系
    {
        printf("Please enter the that const each other by edge:\n"); //请输入连接彼此的顶点关系
        scanf(" %c", &u); 
        scanf(" %c", &v);
            
        /*
        u = getchar();
		while(getchar() != '\n');
		v = getchar();
		while(getchar() != '\n');
        */

        // v和u是关联的就要把对应的标志位进1
        // 并且要找到对应的索引编号
        i = search_vex(graph, u);
		j = search_vex(graph, v);
        printf("%d", i);
        printf("  %d\n", j);

		if(i != -1 && j != -1)
            graph->Edge[i][j] = graph->Edge[j][i] = 1;  // 设为1
        else
        {
            printf("You have enter wrong vex, Please enter again.\n"); // 有找不到,输入的顶底信息有错误
            graph->edge_num++;  //输错了不算数要加回来
        }
    }
    return graph;
}

void show_AMG_Graph(struct AMG_Graph *graph)
{
    int i, j;
    printf("Show the vex: \n");
    for (i = 0; i < graph->vex_num; i++)
        printf("%c", graph->Vex[i]);
    printf("\n");

    printf("Show the adjacency matrices: \n");
    for(i = 0; i < graph->vex_num; i++)
    {
        for (j = 0; j < graph->vex_num; j++)
            printf("%d\t", graph->Edge[i][j]);
        printf("\n");
    }

}

int search_vex(struct AMG_Graph *graph, char c)
{
    int i;

    for (i = 0; i < graph->vex_num; i++)
    {  //找到对应的索引编号
        if (c == graph->Vex[i])
            return i;
    }
    return -1; //般用在子函数结尾。表示该函数失败.
}