#include <iostream>
#include "AVLTree.h"

int main(void)
{
	AVLTree<int> tree;
	tree.insert(10);
	tree.insert(88);
	tree.insert(4);
	tree.insert(33);
	tree.insert(666);
	tree.insert(999);
	printf("\n\nÏÈĞò±éÀú: ");
	tree.pre_order(tree.getTree());

	while (1);
	return 0;
}