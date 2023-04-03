#include "binary_tree.h"

int main(void)
{
	struct BinTree_node *mytree;

	mytree = create_bintree();

	level_traverse(mytree);
	printf("\n");

	printf("depth = %d\n", depth(mytree));  //打印深度值
	printf("leaf number = %d\n", leaf_num(mytree)); // 显示叶子个数
	printf("node number = %d\n", node_num(mytree));  //显示节点个数

	return 0;
}
