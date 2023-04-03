#include <iostream>
#include "23tree.h"

using namespace std;
int main(void)
{
	MyTwoThreeTree<int> tree;
	int a[] = {7, 239, 78, 99, 34, 33, 10, 2, 13, 48};
	for (int i = 0; i < sizeof(a) / sizeof(a[0]); i++)
	{
		tree.insertNode(a[i]);
	}

	while (1);
	return 0;
}