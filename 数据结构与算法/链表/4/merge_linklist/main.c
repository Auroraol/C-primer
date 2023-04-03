#include <stdio.h>
#include "linkedlist.h"

int main(void)
{
    create_list(1);
	create_list(2);
	create_list(8);
	create_list(2);
	create_list(3);
    create_list(1);
	create_list(2);
	create_list(8);
	create_list(2);
    print_linklist(head);
    printf("mid = %d", find_mid(head));
    return 0;
}
