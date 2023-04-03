#pragma once
#include <cstring>

// vector 动态数组
template <class T>
class MyStack
{
public:
	MyStack()
	{
		pBuff = NULL;
		len = 0;
		maxLen = 0;
	}
	~MyStack()
	{
		if (pBuff)
			delete[] pBuff;
		pBuff = NULL;
	}
	void push(const T& data);
	void pop()
	{
		len--;
	}
	T getTop()
	{
		return pBuff[len - 1];
	}
	bool isEmpty()
	{
		return len == 0;
	}
private:
	T* pBuff;
	size_t len;
	size_t 	maxLen;

};

template<class T>
inline void MyStack<T>::push(const T& data)
{
	/*
	//1. 每次开内存  //节约空间当时浪费时间
	maxLen = len + 1;
	T* pTemp = new T[maxLen];
	//2. 如果原来的内存段中有数据
	if (pBuff)
	{
		memcpy(pTemp，pBuff，sizeof(T) * len);
		delete[] pBuff;
	}

	//3 新数据进来
	pBuff = pTemp;
	pBuff[len++] = data;
	*/
	// 改进:
	// 1. 判断是否需要开内存 
	if (len >= maxLen)
	{
		//1.1 每次开内存  
		// 1.1.1 计算新开的内存大小
		// 新的内存段大小是原来的1倍加原来的1/2 或者 1
		maxLen = maxLen + (((maxLen >> 1) > 1) ? (maxLen >> 1) : 1);
		// 1.1.2 开内存
		T* pTemp = new T[maxLen];
		//2. 如果原来的内存段中有数据
		if (pBuff)
		{
			std::memcpy(pTemp, pBuff, sizeof(T) * len);
			delete[] pBuff;
		}
		pBuff = pTemp;
	}
	//3 新数据进来
	pBuff[len++] = data;
}
