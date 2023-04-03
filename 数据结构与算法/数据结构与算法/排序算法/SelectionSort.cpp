#include <iostream>
#include<cstring>

using namespace std;

void swap(int* n1, int* n2);
void print(const int arr[], int len);
void bubbleSort(int arr[], int len);  // 冒泡排序
void selectionSort(int arr[], int len);  // 选择排序
void insertionSort(int arr[], int len);  // 插入排序
void shellSort(int arr[], int len);      // 希尔排序
void radixSort(int arr[], int len, int max);  // 基数排序
void binSort(int arr[], int len, int area);   // 箱排序
void mergeToSort(int arr[], int l, int m, int r);   // 合并排序
void mergeSort(int arr[], int l, int r);            // 归并排序
void quickSort(int arr[], int len);
void quickSort2(int arr[], int len);

void showTestResult(const char* str, void (*pf)(int*, int) = NULL)
{
	int arr[10] = {7, 44, 3, 5, 0, 99, 46, 12, 6, 1};
	cout << "-----------------------------------\n";
	cout << " " << str << ":  ";
	if (pf)
		pf(arr, sizeof(arr) / sizeof(arr[0]));
	print(arr, 10);
}

int main(void)
{
	// 未排序:
	showTestResult("未排序  ");
	// 冒泡排序:
	showTestResult("冒泡排序", bubbleSort);
	// 选择排序:
	showTestResult("选择排序", selectionSort);
	// 插入排序:
	showTestResult("插入排序", insertionSort);
	// 希尔排序:
	showTestResult("希尔排序", shellSort);
	// 基数排序:
	int arr1[10] = {7, 44, 3, 5, 0, 99, 46, 12, 6, 1};
	cout << "-----------------------------------\n";
	cout << " " << "基数排序" << ":  ";
	radixSort(arr1, 10, 99);
	print(arr1, 10);

	//箱排序:
	int arr2[10] = {27, 306, 486, 563, 48, 99, 711, 667, 418, 43};
	cout << "\n-----------------------------------------------\n";
	cout << " " << "未排序  " << ":  ";
	print(arr2, 10);
	cout << "-----------------------------------------------\n";
	cout << " " << "箱排序  " << ":  ";
	binSort(arr2, 10, 1000);
	print(arr2, 10);

	//合并排序:
	int arr3[15] = {5, 80, 3, 0, 0, 1, 6, 9, 11, 18, 2, 3, 4, 77, 99};
	cout << "\n-----------------------------------------------\n";
	cout << " " << "未排序  " << ":  ";
	print(arr3, 15);
	cout << "-----------------------------------------------\n";
	cout << " " << "合并排序" << ":  ";
	mergeToSort(arr3, 5, 9, 14);
	print(arr3, 15);
	//归并排序:
	cout << "-----------------------------------------------\n";
	cout << " " << "归并排序" << ":  ";
	mergeSort(arr3, 5, 14);
	print(arr3, 15);

	//快速排序:
	int arr4[15] = {5, 80, 3, 0, 0, 1, 6, 9, 11, 18, 2, 3, 4, 77, 99};
	cout << "\n-----------------------------------------------\n";
	cout << " " << "未排序  " << ":  ";
	print(arr4, 15);
	//cout << "-----------------------------------------------\n";
	//cout << " " << "快速排序1" << ":  ";
	//quickSort(arr3, 15);
	//print(arr3, 15);
	cout << "-----------------------------------------------\n";
	cout << " " << "快速排序2" << ":  ";
	quickSort2(arr4, 15);
	print(arr4, 15);
	return 0;
}

void swap(int* n1, int* n2)
{
	int temp = *n1;
	*n1 = *n2;
	*n2 = temp;
}

void print(const int arr[], int len)
{
	for (int i = 0; i < len; i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl;
}

// 冒泡排序
void bubbleSort(int arr[], int len)
{
	bool isok;
	for (int i = len - 1; i > 0; i--)
	{
		isok = false;
		for (int j = 0; j < i; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				swap(arr[j], arr[j + 1]);
				isok = true;
			}
		}
		if (!isok)
			break;
	}
}

// 选择排序
void selectionSort(int arr[], int len)
{
	int min_idx = 0;
	//从待排序列中挑选最小的放到第一个位置  (所以挑到最后一个元素就不用挑了)
	for (int i = 0; i < len - 1; i++)
	{
		min_idx = i;
		// 待排序列的范围  [i, len - 1]
		for (int j = i; j < len; j++)  //[i, len - 1]范围内找到最小的下标
		{
			min_idx = (arr[min_idx] < arr[j]) ? min_idx : j;
		}
		// 和 a[i] 交换
		if (min_idx != i)    // 如果最小的位置不是起始位置就交换值,始终使当前位置是最小值
			swap(&arr[i], &arr[min_idx]);
	}
}

// 插入排序
void insertionSort(int arr[], int len)
{
	int temp;
	int j;
	//把待排序的数组分成已排序和未排序两部分，初始时把第一个元素认为是已排好序的。
	//直到最后一个元素被插入有序子数组中。所以挑到最后一个元素就还是要挑的(因为除了第一个元素,每个元素都要拿来插入)
	for (int i = 1; i < len; i++) //初始时把第一个元素认为是已排好序的。
	{
		// 1. 临时存储当前数据
		temp = arr[i];

		//(从第二个元素开始)去已排好序的子数组中, 定位插入点
		// 2. 定位到插入点,插入点之后的需要往后移,因为他们不能变
		// 条件1:从i-1 到 0 条件2:比temp大  ---> 往后覆盖
		j = i - 1;
		while (j >= 0 && arr[j] > temp)
		{
			arr[j + 1] = arr[j];  // 往后覆盖(往后挪)
			j--;
		}
		// 3. 插入
		arr[j + 1] = temp;
	}
}

// 希尔排序
void shellSort(int arr[], int len)
{
	int step = len >> 1;   // 初始步长为元素的一半(len / 2)
	int temp;
	int j;
	while (step)
	{
		// 组内做"插入排序"  i = step
		for (int i = step; i < len; i++)
		{
			// 1. 临时存储当前数据,
			temp = arr[i];

			// 2. 定位到插入点,插入点之后的需要往后移 // 条件1:从i-1 到 0 条件2:比temp大  ---> 往后覆盖
			j = i - step;
			while (j >= 0 && arr[j] > temp)
			{
				arr[j + step] = arr[j];  // 往后覆盖
				j -= step;
			}
			// 3. 插入
			arr[j + step] = temp;
		}

		step >>= 1;  // 步长每次折半
	}
}

// 基数排序
void radixSort(int arr[], int len, int max) //数组首地址   数组元素个数  最大元素值
{
	int* pTemp = new int[max + 1];
	int k = 0;
	for (int i = 0; i < max + 1; i++)
	{
		pTemp[i] = -1;
	}

	for (int i = 0; i < len; i++)
	{
		pTemp[arr[i]] = arr[i];  // 核心
	}

	// 放回去
	for (int i = 0; i < max + 1; i++)
	{
		if (-1 != pTemp[i])  // 如果存在
		{
			arr[k] = pTemp[i];
			k++;
		}
	}
}

// 箱排序
void binSort(int arr[], int len, int area)  // int area 位数次
{
	int idx;
	// i = 1      10            100
	// num/1%10   num/10%10     num/100%10
	for (int i = 1; i < area; i *= 10)  // 10进制位数
	{
		// 1. 创建10个箱子, 并且初始化为-1
		int* pTemp = new int[len * 10];  // 一维数组表示二维数组
		for (int j = 0; j < 10 * len; j++)
		{
			pTemp[j] = -1;
		}
		// 2. 把待排数组中的数据，按照规律放到箱子里去
		for (int j = 0; j < len; j++)
		{
			idx = arr[j] / i % 10;   // 一个数上的某个位上的数
			//pTemp[idx][j];
			*(pTemp + (idx * 10) + j) = arr[j];
		}
		// 3. 按照先后次序把箱子里的数据放到待排数组中 , 放回去
		int k = 0;
		for (int j = 0; j < 10 * len; j++)
		{
			if (-1 != pTemp[j])
			{
				arr[k++] = pTemp[j];
			}
		}

		// 4. 释放内存
		delete[]pTemp;
	}
}

// 合并排序
void mergeToSort(int arr[], int l, int m, int r) //1,m,r: 是元素下标
{ // l -- m  // m+1 -- r
	int left = l;
	int right = m + 1;
	int k = 0;
	// 1. 开辟临时内存
	int len = r - l + 1;  // r + 1 是在常规情况的
	int* pTemp = new int[len];

	// 2. 放完左边或者右边
	while (left <= m && right <= r)
	{
		if (arr[left] < arr[right])
			pTemp[k++] = arr[left++];
		else
			pTemp[k++] = arr[right++];
	}
	// 3. 把剩下的也放到临时数组中
	if (left <= m)
	{
		memcpy(pTemp + k, arr + left, sizeof(int) * (m - left + 1));
	}
	else
	{
		memcpy(pTemp + k, arr + right, sizeof(int) * (r - right + 1));
	}

	// 4. 临时数组覆盖原数组，释放临时数组内存
	memcpy(arr + l, pTemp, sizeof(int) * len);

	// 5. 释放内存
	delete[]pTemp;
}

// 归并排序
void mergeSort(int arr[], int l, int r)
{
	// 1拆到只有一个元素为止(只有一个元素的数组必然有序)
	if (l >= r)
		return;
	// 0先拆
	int m = l + (r - l) / 2;
	mergeSort(arr, l, m);
	mergeSort(arr, m + 1, r);

	// 2再合并
	mergeToSort(arr, l, m, r);
}

#if 0

// 快速排序
int partition(int arr[], int low, int high)
{
	int pivot = arr[low];     //基准
	while (low < high)
	{
		while (low < high && arr[high] >= pivot) --high;
		arr[low] = arr[high];            //交换比基准大的记录到左端
		while (low < high && arr[low] <= pivot) ++low;
		arr[high] = arr[low];           //交换比基准小的记录到右端
	}
	//扫描完成，基准到位
	arr[low] = pivot;
	//返回的是基准的位置
	return low;
}

void qsort(int arr[], int low, int high)
{
	if (low >= high)
		return;
	int pivot = partition(arr, low, high);        //将数组分为两部分
	qsort(arr, low, pivot - 1);                   //递归排序左子数组
	qsort(arr, pivot + 1, high);                  //递归排序右子数组
}

void quickSort(int arr[], int len)
{
	qsort(arr, 0, len - 1);
}
#endif // 0

//  快速排序
/*
思路:
	1. pivot ----> 永远是左边第一个
	2. i,j ----> pivot后一个
	3. 移动两个指针: 1. i左边的数 < pivot
				   2. 让[i, j]之间 > pivot
		3.1. 如果 num[j] > pivot  --> j++
			 如果 num[j] < pivot  --> 1. 交换i,j  2. i++, j++

	4. j到最后了, 交换pivot 和 num[i-1]

	5. 分治

*/

void mySwap(int arr[], int n1, int n2)
{
	arr[n1] ^= arr[n2];
	arr[n2] ^= arr[n1];
	arr[n1] ^= arr[n2];
}

void subSort(int arr[], int low, int high)
{
	if (low >= high) return;
	//1. pivot ----> 永远是左边第一个
	int pivot = arr[low];

	//2. i, j---- > pivot后一个
	int i = low + 1;
	int j = low + 1;

	while (j <= high)   // 终止条件  // 4. j到最后了
	{
		// 3. 如果 num[j] < pivot--> 1. 交换i, j  2. i++, j++
		if (arr[j] < pivot)
		{
			mySwap(arr, i, j);
			i++;
		}
		j++;
	}

	//4. j到最后了, 交换pivot 和 num[i-1]
	mySwap(arr, low, i - 1);  // 也可以i-2

	// 分治
	subSort(arr, low, i - 1);
	subSort(arr, i, high);
}

void quickSort2(int arr[], int len)
{
	subSort(arr, 0, len - 1);
}