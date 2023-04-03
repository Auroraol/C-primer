#include <stdio.h>
#include "linklist.h"

int main(void)
{
	int n;

	create_list(1);
	create_list(2);
	create_list(3);
	create_list(4);
	create_list(5);
	create_list(6);
	create_list(7);
	create_list(8);
	create_list(9);
	create_list(10);
	print_linklist(head);

	printf("Please enter the last one you want to show:");
	scanf("%d", &n);

	printf("the last n :%d\n", find_last_nth(head, n));

	return 0;
}
