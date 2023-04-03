#pragma once
#include <cstring>

template <class T>
class MyTwoThreeTree
{
	// 内部类
	struct Node
	{
		int    count;          // 标记当前是2节点(1)还是3节点(2)还是4节点(3)
		T      data[3];        // 数据  // 2节点, 3节点 , 4节点
		Node* pArray[4];       // 节点指针

		Node()
		{
			count = 0;
			memset(data, 0, sizeof(T) * 3);
			memset(pArray, 0, sizeof(Node*) * 4);
		}
	};

	Node* pRoot;  // 指向根节点的指针变量
public:
	//// 防止内存泄露
	//static int newTimes;
	//static int deleteTimes; 

public:
	// 构造器
	MyTwoThreeTree()
	{
		pRoot = NULL;
	}
	// 析构
	~MyTwoThreeTree()
	{
		_clear();
	}

	void insertNode(const T& data);  // 插入

private:
	void _clear();
	void _clear(Node* pDel);
	void _insertNode(Node* node, Node* pParent, const T& data);
};

template<class T>
inline void MyTwoThreeTree<T>::insertNode(const T& data)
{
	if (pRoot)  // pRoot不为空
	{
		_insertNode(pRoot, NULL, data);
	}
	else
	{ // 第一个节点是不一样的
		pRoot = new Node;
		pRoot->count = 1;
		pRoot->data[0] = data;
	}
}

template<class T>
inline void MyTwoThreeTree<T>::_insertNode(Node* node, Node* pParent, const T& data)
{
	if (0 == node->count)  // 当前节点为空
	{
		node->data[0] = data;
		node->count++;
		return;
	}
	if (1 == node->count)  // 2节点
	{
		if (data > node->data[0])  //往右边添加
		{
			if (node->pArray[0]) // 有孩子
			{
				_insertNode(node->pArray[1], node, data);
			}
			else  // 没有孩子
			{     // 往当前孩子添加
				node->data[1] = data;
				node->count++;

			}
		}
		else    //往左边添加
		{
			if (node->pArray[0]) // 有孩子
			{
				_insertNode(node->pArray[0], node, data);

			}
			else // 没有孩子
			{
				node->data[1] = node->data[0];   // 本来左边的放到右边
				node->data[0] = data;
				node->count++;
			}
		}
	}
	else // 3节点
	{

		if (data < node->data[0])  //往最左边插入
		{
			if (node->pArray[0]) // 有孩子
			{
				_insertNode(node->pArray[0], node, data);

			}
			else // 没有孩子
			{
				node->data[2] = node->data[1];   // 本来中间的放到右边
				node->data[1] = node->data[0];   // 本来左边的放到中间
				node->data[0] = data;
				node->count++;
			}
		}
		else if (data < node->data[1]) // 往中间插入
		{
			if (node->pArray[1]) // 有孩子
			{
				_insertNode(node->pArray[1], node, data);

			}
			else // 没有孩子
			{
				node->data[2] = node->data[1];   // 本来中间的放到右边
				node->data[1] = data;
				node->count++;
			}
		}
		else // 往右边插入
		{
			if (node->pArray[2]) // 有孩子
			{
				_insertNode(node->pArray[2], node, data);

			}
			else // 没有孩子
			{
				node->data[2] = data;
				node->count++;
			}

		}

	}

	// 4节点
	if (3 == node->count)
	{

		//1. 创建两个新节点
		Node* node1 = new Node;
		Node* node2 = new Node;
		// node1是当前节点的左边那个
		node1->data[0] = node->data[0];
		node1->count = 1;  // 标记为2节
		node1->pArray[0] = node->pArray[0];
		node1->pArray[1] = node->pArray[1];

		// node2是当前节点的右边那个
		node2->data[0] = node->data[2];
		node2->count = 1;
		node2->pArray[0] = node->pArray[2];
		node2->pArray[1] = node->pArray[3];

		//  临时的储存当前节点的中间值
		T temp = node->data[1];

		if (pParent)  //有父节点
		{
			//找位置
			if (temp < pParent->data[0])  // 左边
			{
				if (pParent->pArray[2])  // 最右边有孩子
				{
					pParent->data[2] = pParent->data[1];
					pParent->data[1] = pParent->data[0];
					pParent->data[0] = temp;

					pParent->pArray[3] = pParent->pArray[2];
					pParent->pArray[2] = pParent->pArray[1];
					pParent->pArray[1] = node2;
					pParent->pArray[0] = node1;
				}
				else if (pParent->pArray[1]) // 中间有孩子
				{
					pParent->data[1] = pParent->data[0];
					pParent->data[0] = temp;

					pParent->pArray[2] = pParent->pArray[1];
					pParent->pArray[1] = node2;
					pParent->pArray[0] = node1;
				}
			}
			else if (pParent->count == 1
				|| (pParent->count > 1) && (temp < pParent->data[1]))  // 中间
			{
				if (pParent->pArray[2])  // 最右边有孩子
				{
					pParent->data[2] = pParent->data[1];
					pParent->data[1] = temp;

					pParent->pArray[3] = pParent->pArray[2];
					pParent->pArray[2] = node2;
					pParent->pArray[1] = node1;
				}
				else if (pParent->pArray[1]) // 中间有孩子
				{
					pParent->data[1] = temp;

					pParent->pArray[2] = node2;
					pParent->pArray[1] = node1;
				}

			}
			else if (pParent->count == 2
				|| (pParent->count > 2) && (temp < pParent->data[2]))  // 右边
			{
				if (pParent->pArray[2])  // 最右边有孩子
				{
					pParent->data[2] = temp;

					pParent->pArray[3] = node2;
					pParent->pArray[2] = node1;
				}

			}

			pParent->count++;
			delete node; //必须释放当前节点，因为已经插入到父节点之内

		}
		else  // 没有父节点
		{
			//2. 当前节点数据改变count变成1 
			memset(node->data, 0, sizeof(T) * 3);  // 清空
			node->data[0] = temp;
			node->count = 1;
			//3. pArray[o]和pArray[1]赋值l  
			memset(node->pArray, 0, sizeof(Node*) * 4);  // 清空
			node->pArray[0] = node1;
			node->pArray[1] = node2;
		}
	}

}

template<class T>
inline void MyTwoThreeTree<T>::_clear()
{
	// 调用带参的_clear从叶子到根删除整颗树
}

template<class T>
inline void MyTwoThreeTree<T>::_clear(Node* pDel)
{
	if (pDel)
		delete pDel;
}





