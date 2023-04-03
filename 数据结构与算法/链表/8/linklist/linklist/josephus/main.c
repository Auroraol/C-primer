#include <stdio.h>
#include "linklist.h"
#include <stdlib.h>

int main(void)
{
	int n, k, m;   //
	int i;
	struct node *p, *q;

	printf("Please enter the number of person:");  //请输入人的个数
	scanf("%d", &n); //scanf（“%d”，&n ) 头文件stdio.h  用户输入整数，并将这个整数存在变量n   . gets()输入字符串时用

	for(i = 1; i <= n; i++)
		create_list(i);
	print_linklist(); //显示
	p = head;

	printf("Please enter the start num:"); //请输入起始的编号
	scanf("%d", &k);

	while(--k) //可以循环 k-1次
		p = p->next;
	printf("p->elem = %d\n", p->elem);  //显示一下找到的是不是目标节点

	printf("Please enter the m:");   //请输入出列的喊的编号
	scanf("%d", &m);
	
	if(1 == m)
	{
		for(i = 0; i < n; i++)
		{
			printf("%3d", p->elem);
			p = p->next;
		}
		printf("\n");
	}
	else
	{
		while(n--)  //全部人数循环
		{
			//找前驱点
			for(i = 1; i < m - 1; i++)  //找前驱点     找本身 m为3-->循环1次   m为5-->3次 
				p = p->next;  //p是前驱点

			//如下图 	
			q = p;  // q取代表前驱点
			p = p->next; //找到下一个节点
			printf("%3d", p->elem);
			q->next = p->next;
			free(p);
			p = p->next;
		}
		printf("\n");
	}
	return 0;
}
