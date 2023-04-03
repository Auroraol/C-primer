#include "binary_tree.h"

int main(void)
{
	struct BinTree_node *mytree;

	mytree = create_bintree();

	level_traverse(mytree);
	printf("\n");

	printf("depth = %d\n", depth(mytree));
	printf("leaf number = %d\n", leaf_num(mytree));
	printf("node number = %d\n", node_num(mytree));

	return 0;
}
