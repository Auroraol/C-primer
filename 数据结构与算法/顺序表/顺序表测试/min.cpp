#include "sequence_list.h"
#include <stdio.h>



int main(void)
{
	/*Seqlist list;
	seqlist_init(&list);
	seqlist_print(&list);*/

	Seqlist* list = seqList_create();

	seqList_pushback(list, (Data)3);
	seqList_pushback(list, (Data)4);
	seqList_pushback(list, (Data)4);
	seqList_pushfront(list, (Data)9);
	//seqList_popback(list);
	seqList_popfront(list);
	seqList_removePos(list, 2);
	for (int i = 0; i < 100; i++)
	{
		seqList_pushback(list, (Data)(i + 1));
	}

	seqlist_print(list);
	return 0;
}