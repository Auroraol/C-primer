#include <stdio.h>
#include "linkedlist.h"

int main(void)
{
	create_list('A');
	create_list('B');
	create_list('C');
	create_list('D');
	print_linklist();

	delete_node(0);
	print_linklist();

	insert_node(0, 'F');
	insert_node(2, 'Z');
	print_linklist();

	if(search('C'))
		printf("the elem is found in the linklist\n");
	else
		printf("Can not find it\n");

	return 0;
}
