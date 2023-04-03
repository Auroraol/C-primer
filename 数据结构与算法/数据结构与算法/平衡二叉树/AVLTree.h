#pragma once
#include <stdio.h>

template <class T>
struct TreeNode
{
	T        data;    // 数据
	TreeNode* pLeft;   // 左孩子
	TreeNode* pRight;  // 右孩子
	int      height;  // 高度

	TreeNode(const T& data) : data(data)  // 为了方便使用构造器
	{
		pLeft = pRight = NULL;
		height = 0;
	}
};


template <class T>
class AVLTree
{
private:
	TreeNode<T>* pRoot;  // 指向根节点的指针
	void _insertNodeToTree(TreeNode<T>*& root, const T& data);  // & root目的是为了修改它 // 私有的函前面用_标记是私有的
	int _getHeight(TreeNode<T>* pRoot);

	//右旋对应1 
	TreeNode<T>* RR(TreeNode<T>* root);
	//左旋对应2 
	TreeNode<T>* LL(TreeNode<T>* root);
	//左右旋对应3
	TreeNode<T>* LR(TreeNode<T>* root);
	//右左旋对应4
	TreeNode<T>* RL(TreeNode<T>* root);

public:
	AVLTree() { pRoot = NULL; }   // 创建一个空树
	~AVLTree() {}

	void insert(const T& data);
	void pre_order(TreeNode<T>* root);
	TreeNode<T>* getTree();
};


template <class T>
void AVLTree<T>::insert(const T& data)
{
	_insertNodeToTree(pRoot, data);  // 看似对此一举是为了安全
}

template <class T>
void AVLTree<T>::_insertNodeToTree(TreeNode<T>*& root, const T& data)
{
	//作为一颗平衡二叉树，先是一颗有序二叉树
	// 1. 以有序二叉树方式插入
	if (root == NULL)
	{
		root = new TreeNode<T>(data);    // 这里的本质用新的节点替换NULL  // 插入
	}


	// 递归:  (本质就是把复杂的问题变简单,抓住函数的作用,比如这里的_insertNodeToTree:就是往一颗树里面插入一个节点,莫去想其他的)
	else if (data > root->data)
	{
		_insertNodeToTree(root->pRight, data);   // 递归调用,传进去的是root->PRight, 所以pRoot是永远指向最出的根节点

		// 2. 检查是否需要旋转，需要就旋转(是根据之前的左右子树高度判断的)
		if (_getHeight(root->pRight) - _getHeight(root->pLeft) > 1)
		{ // 2.1 右边比左边高
			// 2.2 判断是那种不平衡   2或4
			if (data > root->pRight->data)  // 看不平衡的图
			{// 2
				printf("左旋\n");
				root = LL(root);  // 以root为轴左旋
			}
			else
			{// 4
				printf("右左旋\n");
				root = RL(root);
			}
		};
	}
	else
	{
		_insertNodeToTree(root->pLeft, data);

		// 2. 检查是否需要旋转，需要就旋转(是根据之前的左右子树高度判断的)
		if (_getHeight(root->pLeft) - _getHeight(root->pRight) > 1)
		{// 2.1 左边比右边高
			// 2.2 判断是那种不平衡 1和3
			if (data < root->pLeft->data)
			{// 1
				printf("右旋\n");
				root = RR(root);   // 以root为轴右旋 然后 返回值赋值给root修改根节点
			}
			else
			{// 3
				printf("左右旋\n");
				root = LR(root);
			}
		}
	}

	// 3. 每插入一个节点,设置高度9(这里根结点第1，所以层数=深度=高度)
	int lH = _getHeight(root->pLeft);
	int RH = _getHeight(root->pRight);
	root->height = lH > RH ? (lH + 1) : (RH + 1);
	printf("当前节点的高度%d", root->height);
}

// 得到高度
template<class T>
inline int AVLTree<T>::_getHeight(TreeNode<T>* pRoot)
{
	if (pRoot)
		return pRoot->height;
	return 0;
}

//右旋
template<class T>
inline TreeNode<T>* AVLTree<T>::RR(TreeNode<T>* root)
{
	//1. pTemp记录root的左孩子
	TreeNode<T>* pTemp = root->pLeft;

	//2. pTemp的右孩子成为root的左孩子
	root->pLeft = pTemp->pRight;

	//3. root成为pTemp的右孩子
	pTemp->pRight = root;

	//4. 重新设置高度
	int lH = _getHeight(root->pLeft);
	int RH = _getHeight(root->pRight);
	root->height = lH > RH ? (lH + 1) : (RH + 1);

	//5. pTemp返回回去
	return pTemp;
}

// 左旋
template<class T>
inline TreeNode<T>* AVLTree<T>::LL(TreeNode<T>* root)
{
	//1. pTemp记录root的右孩子
	TreeNode<T>* pTemp = root->pRight;

	//2. pTemp的左孩子成为root的右孩子
	root->pRight = pTemp->pLeft;

	//3. root成为pTemp的左孩子
	pTemp->pLeft = root;

	//4. 重新设置高度
	int lH = _getHeight(root->pLeft);
	int RH = _getHeight(root->pRight);
	root->height = lH > RH ? (lH + 1) : (RH + 1);

	//5. pTemp返回回去
	return pTemp;
}

//左右旋
template<class T>
inline TreeNode<T>* AVLTree<T>::LR(TreeNode<T>* root)
{
	root->pLeft = LL(root->pLeft);  // 先以root的左孩子为轴左旋
	return RR(root); // 再以root为轴右旋
}

//右左旋
template<class T>
inline TreeNode<T>* AVLTree<T>::RL(TreeNode<T>* root)
{
	root->pLeft = RR(root->pLeft);  // 先以root的右孩子为轴右旋
	return LL(root); // 再以root为轴左旋
}


template<class T>
inline void AVLTree<T>::pre_order(TreeNode<T>* root)
{
	if (root)
	{
		printf("%d  ", root->data);
		pre_order(root->pLeft);
		pre_order(root->pRight);
	}
}

template<class T>
inline TreeNode<T>* AVLTree<T>::getTree()
{
	return pRoot;
}