#include <stdio.h>
#include "linklist.h"

int main(void)
{
	create_list(1);
	create_list(2);
	create_list(8);
	create_list(2);
	create_list(3);
	create_list(9);
	create_list(4);
	create_list(6);
	create_list(4);
	create_list(8);
	create_list(7);
	create_list(5);
	create_list(2);
	create_list(9);
	create_list(6);
	print_linklist(head);

	delete_repeat(head);
	print_linklist(head);

	return 0;
}
