#include <stdio.h>
#include "linklist.h"
#include <stdlib.h>


int main(void)
{
	int n, k, m, num;
	int i;
	struct node* p, * q;

	printf("请输入人的个数:");  //请输入人的个数
	scanf("%d", &n);

	for (i = 1; i <= n; i++)
	{
		printf("请输入第%d个人密码:", i); // 请输入个人密码
		scanf("%d", &num);
		create_list(num); //创建的是循环链表
	}
	print_linklist(); //显示
	p = head;

	printf("请输入出列的喊的编号m初始值:");   //请输入出列的喊的编号
	scanf("%d", &m);
	if (1 == m)
	{
		for (i = 0; i < n; i++)
		{
			printf("%3d", p->elem);
			p = p->next;
		}
		printf("\n");
	}
	else
	{


		while (n--)  //(直到没有元素了)全部人数循环(1 到 n次)(只要n里面没人来)
		{

			//找前驱点(i = 0; i < m-2)
			for (i = 0; i < m - 2; i++)  //找前驱点   m为3-->循环1次   m为5-->3次 
				p = p->next;  //  p是前驱点

			//如下图 	
			q = p;  // q取代表前驱点 //p是用来接受要删除的节点的
			p = p->next; //找到下一个节点(要删除的节点)
			m = p->elem;
			printf("%d", p->elem);
			q->next = p->next;   //   删除节点
			free(p);
			p = p->next; //更新p的位置

		}
		printf("\n");
	}

	return 0;
}


