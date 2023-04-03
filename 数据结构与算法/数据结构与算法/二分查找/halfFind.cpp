#include <iostream>
#include <vector>
#include <string>

using namespace std;

int searchE(vector<int>& nums, int target);     // 等于 
int searchBE(vector<int>& nums, int target);    // 大于等于
int searchB(vector<int>& nums, int target);     // 大于 
int searchLD(vector<int>& nums, int target);    // 小于等于
int searchL(vector<int>& nums, int target);     // 小于


void showTestResult(string str, int (*pf)(vector<int>&, int))
{
	vector<int> arr = {1, 2, 3, 4, 8, 14, 32, 43, 223, 344, 362, 555, 1134 ,2312};
	cout << "\n  数组 [ ";
	for (int v : arr)
	{
		cout << v << " ";
	}
	cout << "]";
	int anw = 43;
	cout << "\n  要查找" << str << anw << "的数据" << endl;
	cout << "  查找结果: 索引";
	int reslut = pf(arr, anw);
	if (reslut != -1)
		cout << reslut << endl;
	else
		cout << "数组中不存在要查找的数据" << endl;
}



int main(void)
{
	// 等于
	showTestResult("等于", searchE);
	// 大于等于
	showTestResult("大于等于", searchBE);
	// 大于
	showTestResult("大于", searchB);
	// 小于等于
	showTestResult("小于等于", searchLD);
	// 小于
	showTestResult("小于", searchL);

	return 0;
}

// 等于
int searchE(vector<int>& nums, int target)
{
	int len = nums.size();
	int left = 0, right = len - 1;
	while (left <= right)
	{
		int mid = left + (right - left) / 2;
		if (nums[mid] < target)
			left = mid + 1;
		else
			right = mid - 1;
	}
	return (left == len || nums[left] != target) ? -1 : left;
}

//大于等于
int searchBE(vector<int>& nums, int target)
{
	int len = nums.size();
	int left = 0, right = len - 1;
	while (left <= right)
	{
		int mid = left + (right - left) / 2;
		if (nums[mid] >= target)  // 
			right = mid - 1;
		else
			left = mid + 1;
	}
	return left == len ? -1 : left;
}

//大于
int searchB(vector<int>& nums, int target)
{
	int len = nums.size();
	int left = 0, right = len - 1;
	while (left <= right)
	{
		int mid = left + (right - left) / 2;
		if (nums[mid] > target)  // 
			right = mid - 1;
		else
			left = mid + 1;
	}
	return left == len ? -1 : left;
}

//小于等于
int searchLD(vector<int>& nums, int target)
{
	int len = nums.size();
	int left = 0, right = len - 1;
	while (left <= right)
	{
		int mid = left + (right - left) / 2;
		if (nums[mid] <= target)
			left = mid + 1;
		else
			right = mid - 1;
	}
	return right;
}

//小于
int searchL(vector<int>& nums, int target)
{
	int len = nums.size();
	int left = 0, right = len - 1;
	while (left <= right)
	{
		int mid = left + (right - left) / 2;
		if (nums[mid] < target)
			left = mid + 1;
		else
			right = mid - 1;
	}
	return right;
}