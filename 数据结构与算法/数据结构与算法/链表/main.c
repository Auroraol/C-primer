#include <stdio.h>
#include "LinkList.h"


int main(void)
{
	linkNode* list = createList();
	pushfront(list, 1);
	pushfront(list, 3);
	pushfront(list, 2);
	pushfront(list, 3);
	pushfront(list, 3);

	insert_pos(list, 3, 2);
	//insert_pos(list, 3, 999);

	//linkNode* item = find(list, 3);
	//if (item)
	//{
	//	insert_item(list, item, 444);
	//}

	//pop_front(list);
	//pop_back(list);
	//	removeOne(list, 2);
	removeA1l(list, 2);
	show_list(list);
	while (1);
	return 0;
}