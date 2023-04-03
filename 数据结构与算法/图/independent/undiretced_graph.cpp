#include <stdio.h>
#include <stdlib.h>
#define MAX 100

struct AMG_Graph
{
    int vex_num, edge_num;
    char VEX[MAX];
    int Edge[MAX][MAX];
};

struct AMG_Graph *Create_Amg_Graph(void);
int sreach_index(const struct AMG_Graph *graph,char c);
void show_undriction(const struct AMG_Graph *graph);

int main(void)
{
    struct AMG_Graph *ud_graph;
    ud_graph = Create_Amg_Graph();
    show_undriction(ud_graph);
    return 0;
}

struct AMG_Graph *Create_Amg_Graph(void)
{
    AMG_Graph *graph;
    graph = (AMG_Graph *)malloc(sizeof(struct AMG_Graph));
    printf("Please vex_num: \n");
    scanf("%d", &graph->vex_num);
    printf("Please edge_num: \n");
    scanf("%d", &graph->edge_num);
    while (getchar() != '\n');

    printf("Please enter vertex: \n");
    for (int i = 0; i < graph->vex_num; i++)
    {
        // scanf("%c", graph->VEX[i]);
        graph->VEX[i] = getchar();
        while (getchar() != '\n');
    }

    printf("Please enter vertex relation\n");
    for (int i = 0; i < graph->vex_num; i++)
    {
        for (int j = 0; j < graph->vex_num; j++)
        {
            graph->Edge[i][j] = 0;   //最开始是不知道关系的,同过输入有关系的顶点得到的
        }
    }

    while (graph->vex_num--) // 单纯带表循环次数所以不去减一
    {
        char a, b;
        int i, j;
        scanf("%c", a);
        scanf("%c", b);

        i = sreach_index(graph, a);
        j = sreach_index(graph, b);
        if (i != -1&& j != -1)
            graph->Edge[i][j] = graph->Edge[j][i] = 1;
        else
        {
            printf("Input erorr, no ration!");
            graph->vex_num++; 
        }
    }
    return graph;
}

int sreach_index(const struct AMG_Graph *graph,char c)
{
    for (int i = 0; i < graph->vex_num; i++)
    {
        if (c == graph->VEX[i])
            return i;
    }
    return -1;
}

void show_undriction(const struct AMG_Graph *graph)
{
    int i;
    printf("show undrited graph: \n");
    printf("display vex \n");
    for (i = 0; i < graph->vex_num; i++)
    {
        printf("%d", graph->VEX[i]);
    }
    printf("disply vex ralation: \n");
    for (i = 0; i < graph->vex_num; i++)
    {
        for (int j = 0; j < graph->vex_num; j++)
        {
            printf("%d \n", graph->Edge[i][j]);
        }
    }
}
