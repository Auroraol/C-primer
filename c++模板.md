# 1 . C++ Template

## 1.1 Template 的声明和定义

模板是一种忽略数据一种泛型编程。把数据当做未知量，当使用的传入类型一种编程方式。

```c++
template <typename T1, typename T2, typename T3>    // 模板函数
template <class T1,class T2,class T3>               // 模板类
template <int V>                                    // 整型模板参数
```

注意:  用typename或者class 都行

## 1.2 函数模板的调用

**函数模板的调用格式是：**

``` C++
函数模板名 < 模板参数列表 > ( 参数 )
```

模板参数的顺序是有限制的：**先写需要指定的模板参数，再把能推导出来的模板参数放在后面**。

```c++
template <typename DstT, typename SrcT> 
DstT c_style_cast(SrcT v)	// 模板参数 DstT 需要人为指定，放前面。
{
    return (DstT)(v);
}

int v = 0;
float i = c_style_cast<float>(v);  // 形象地说，DstT会先把你指定的参数吃掉，剩下的就交给编译器从函数参数列表中推导啦。
```

## 1.3 模板类的调用

**模板类的调用格式(实例化)的语法是：**

```c++
模板名 < 模板实参1 [，模板实参2，...] >  类对象名
```

## 1.4 函数模板使用

+ 函数模板调用

  + 函数模板隐式调用, 可以自动推断:  函数名(函数参数)
  + 显式调用  : 函数名<未知类型>(函数参数)

+ 函数模板本质就是函数传参

  + 函数模板也是可以缺省

+ 整型模板参数

  + 这里的**整型数比较宽泛，包括布尔型，不同位数、有无符号的整型，甚至包括指针。**

  + 整型模板参数最基本的用途: 定义一个常数。

  + ==用了整型模板参数就必须显示调用==
  + 变量传参只能传入常量

+ 当函数模板和普通函数相遇

  + 优先调用类型一致的普通函数
  + 显式调用一定是调用模板

+ 函数模板重载

  + 优先调用传参数目少的函数模板

```c++
  #include <iostream>
  #include <string>
  using namespace std;
  template <class Type>
  Type  Max(Type a, Type b) 
  {
  	return a > b ? a : b;
  }
  template <class _Ty1,class _Ty2,class _Ty3>
  void print(_Ty1 one, _Ty2 two, _Ty3 three) 
  {
  	cout << "1:" << one << endl;
  	cout << "2:" << two << endl;
  	cout << "3:" << three << endl;
  }
  
  //函数模板的缺省
  template <class _Ty1, class _Ty2=string, class _Ty3=int>
  void printData(_Ty1 one, _Ty2 two, _Ty3 three) 
  {
  	cout << "1:" << one << endl;
  	cout << "2:" << two << endl;
  	cout << "3:" << three << endl;
  }
  
  //整型模板参数
  template <class _Ty,int size>
  _Ty* createArray() 
  {
  	_Ty* parray = new _Ty[size];
  	//_Ty =int  size=5
  	//int* parray=new int[5];
  	//_Ty=string size=5
  	//string* parray=new string[5];
  	return parray;
  }
  template <class _Ty, int size>
  void printArray(_Ty array[])
  {
  	for (int i = 0; i < size; i++) 
  	{
  		cout << array[i] << "\t";
  	}
  	cout << endl;
  }
  
  
  template <class _Ty, int size=3>
  void printArray2(_Ty array[])
  {
  	for (int i = 0; i < size; i++)
  	{
  		cout << array[i] << "\t";
  	}
  	cout << endl;
  }
  
  void test() 
  {
  	//No.4 函数模板存在变量
  	int* pInt = createArray<int, 5>();			//_Ty =int  size=5
  	string* pStr = createArray<string, 5>();
  	double* pDouble = createArray<double, 5>();
  	//整数模板参数,必须要显式调用
  	int array[3] = { 1,2,3 };
  	printArray<int,3>(array);
  	double dNum[3] = { 1.11,2.33,4.44 };
  	printArray<double,3>(dNum);
  	//变量做了缺省，可以隐式调用
  	printArray2(array);
  	printArray2(dNum);
  	//int length = 5;
  	//int* pNum = createArray<int, length>();  //只能传入常量
  	//常属性变量ok
  	//const int length = 5;
  	//int* pNum = createArray<int, length>();
  	 
  	//错误的
  	//int length = 5;
  	//int* pNum = createArray<int, static_cast<const int>(length)>();
  
  	//int length = 5;
  	//int* pNum = createArray<int,move(length)>();
  }
  
  void Func1(int a, string b, double c) 
  {
  	cout << "普通函数" << endl;
  }
  //函数模板允许重载
  template <class _Ty1,class _Ty2,class _Ty3>
  void Func1(_Ty1 a, _Ty2 b, _Ty3 c) 
  {
  	cout << "三个类型模板" << endl;
  }
  template <class _Ty1, class _Ty2>
  void Func1(_Ty1 a, _Ty2 b, _Ty2 c)
  {
  	cout << "两个类型模板" << endl;
  }
  template <class _Ty1>
  void Func1(_Ty1 a, _Ty1 b, _Ty1 c)
  {
  	cout << "一个类型模板" << endl;
  }
  
  void test2() 
  {
  	Func1<int, string, double>(1, "sd", 1.11);
  	Func1(1, string("sd"), 1.11);  // 优先推断成char *
  	Func1(1, 1, 1);			//一个参数的模板
  	Func1("string", 1, 1 );
  	Func1("string", 1, "sfsd");
  }
  int main() 
  {
  	//No.1 隐式调用法
  	cout << Max(string("abc"), string("dbc")) << endl;  //Type=string
  	cout << Max(1, 2) << endl;							//Type=int
  	cout << Max(1.11, 2.33) << endl;					//Type=double
  	//No.2 显示调用
  	cout << Max<string>(string("abc"), string("dbc")) << endl;  //Type=string
  	cout << Max<int>(1, 2) << endl;							//Type=int
  	cout << Max<double>(1.11, 2.33) << endl;					//Type=double
  	print<int, string, double>(1, "ILoveyou", 1.11);
  	print<string, string, string>("abc", "ILoveyou", "模板");
  
  	//No.3 缺省
  	printData<string>("str1","str2",1);		//_Ty1=string _Ty2=string _Ty3=int
  	printData<string, double>("str1", 1.11, 1);
  	printData<string, double,string>("str1", 1.11, "str3");
  	test();
  	test2();
  
  
  	return 0;
  }
```



### 1.4.1 函数模板操作自定义类型

操作自定义类型的关键点就是函数重载

```c++
#include <iostream>
#include <string>
using namespace std;

template <class _Ty>
void printArray(_Ty array[], int arrayNum) 
{
	for (int i = 0; i < arrayNum; i++)   //_Ty=MM
	{
		cout << array[i];		//array[i] 对象是不能直接打印
	}
	cout << endl;
}

template <class _Ty>
void Sort(_Ty array[], int arrayNum) 
{
	for (int i = 0; i < arrayNum; i++) 
	{
		for (int j = 0; j < arrayNum - i - 1; j++) 
		{
			if (array[j] > array[j + 1])   //_Ty =MM  array[j] 对象与对象比
			{
				_Ty temp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = temp;
			}
		}
	}
}

// 操作自定义类型
class MM 
{
public:
	MM(string name = "", int age = 0) :name(name), age(age) {}
    // 重载让cout打印
	friend ostream& operator<<(ostream& out, const MM& object) 
	{
		out << object.name << "\t" << object.age << endl;
		return out;
	}
	bool operator>(const MM& object) 
	{
		return this->name > object.name;
	}
	string getName()const { return name; }
	int getAge()const { return age; }
protected:
	string name;
	int age;
};

// 写的比较准则
bool compareByName(const MM& one, const MM& two)
{
	return one.getName() > two.getName();
}
bool compareByAge(const MM& one, const MM& two)
{
	return one.getAge() > two.getAge();
}

template <class _Ty>
void Sort2(_Ty array[], int arrayNum, bool(*compare)(const _Ty& one,const _Ty& two))
{// 参数3是比较准则
	for (int i = 0; i < arrayNum; i++)
	{
		for (int j = 0; j < arrayNum - i - 1; j++)
		{
			if (compare(array[j],array[j+1]))   //_Ty =MM  array[j] 对象与对象比
			{
				_Ty temp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = temp;
			}
		}
	}
}

int main() 
{
	int num[3] = { 1,2,3 };
	printArray(num, 3);
	double dNum[3] = { 1.2,1.1,1.0 };
	Sort(dNum,3);
	printArray(dNum, 3);
    
    // 操作自定义类型
	MM mm[3];
	mm[0] = { "abc",1 };
	mm[1] = { "fc",18 };
	mm[2] = { "de",29 };
	Sort(mm, 3);
	printArray(mm, 3);

	Sort2(mm, 3, compareByName);
	printArray(mm, 3);
	Sort2(mm, 3, compareByAge);
	printArray(mm, 3);
	return 0;
}
```

## 1.5  类模板使用

+  template修饰的类就是模板类
+  模板类必须显式实例化，简单来说必须要传参
+  模板类不是一个真正的类型
   + 声明和实现必须写在一起及同一个文件中, 成员函数直接写成内联函数
   + ==所有用到类型的地方必须要用:    类名<未知类型> 的用法==
+  类模板特化(特殊情况特殊处理, 理解成类的重载)
   + 局部特化： 特殊化处理，例如两个未知变成一个未知类型 template <class T1, class T2> 变成template < class T> 
   + 完全特化： 具体化类型  template <>

```c++
#include <iostream>
#include <string>
using namespace std;

template <class _Ty1,class _Ty2>
class Data 
{
public:
	void print();
protected:
public:
	static int count;  // 静态变量
};

// 静态变量
template <class _Ty1,class _Ty2>
int Data<_Ty1, _Ty2>::count = 0;


template <class _Ty1,class _Ty2>
void Data<_Ty1, _Ty2>::print() 
{
	cout << "类模板中函数" << endl;
}

// -----------
// 所有用到类型的地方必须要用:    类名<未知类型> 的用法
template <class _Ty1,class _Ty2>
class Son : public Data<_Ty1,_Ty2> 
{
public:

protected:

};

struct MMInfo 
{
	string name;
	int age;
	int num;
};
ostream& operator<<(ostream& out, const MMInfo& object) 
{
	out << object.name << "\t" << object.age << "\t" << object.num;
	return out;
}


struct Score 
{
	int math;
	int english;
	int py;
};

ostream& operator<<(ostream& out, const Score& object)
{
	out << object.math << "\t" << object.english << "\t" << object.py;
	return out;
}


//-----------
template <class _Ty1, class _Ty2>
class MM
{
public:
	MM(_Ty1 one, _Ty2 two) :one(one), two(two)
	{

	}
	void print() 
	{
		cout << one <<"\t" << two << endl;
	}
protected:
	_Ty1  one;
	_Ty2  two;
};
void testMM() 
{
	MM<string, int> mm("月亮", 18);
	mm.print();
	MM<int, int> complex(1, 2);
	complex.print();
	MMInfo  info = { "美女",18,1001 }; 
	Score score = { 88, 99, 100 };
	MM<MMInfo, Score> mmObject(info, score);
	mmObject.print();
}

//----------------------
//类模板特化
template <class _Ty1,class _Ty2,class _Ty3>
class A 
{
public:
	A(_Ty1 one, _Ty2 two, _Ty3 three) :one(one), two(two), three() 
	{
		cout << "三个类型" << endl;
	}
protected:
	_Ty1 one;
	_Ty2 two;
	_Ty3 three;
};

//局部特化
template <class _Ty1, class _Ty2>
class A<_Ty1,_Ty2,_Ty1>
{
public:
	A(_Ty1 one, _Ty2 two, _Ty1 three) :one(one), two(two), three()
	{
		cout << "局部特化" << endl;
	}
protected:
	_Ty1 one;
	_Ty1 two;
	_Ty1 three;
};

//完全特化
template <>
class A<int, int, int>
{
public:
	A(int one, int two, int three) :one(one), two(two), three()
	{
		cout << "完全特化" << endl;
	}
protected:
	int one;
	int two;
	int three;
};
void testA() 
{
	A<int, int, int>  object1(1, 1, 1);
	A<double, double, double>  object2(1.1, 1.1, 1.1);
	A<double, string, double>  object3(1.1, string("模板"), 1.1);
}


int main() 
{
	Data<int, string>  object;
	Data<int, string>* pObject = new Data<int, string>;
	object.print();
	pObject->print();
    
    // 静态变量的访问
	cout << Data<int, int>::count << endl;
	cout << Data<string, int>::count << endl;
    
    
	testMM();
	testA();
	return 0;
}
```

### 1.5.1 类模板嵌套

```c++
#include <iostream>
#include <string>
using namespace std;
template <class _Ty1, class _Ty2>
class MM
{
public:
	MM(_Ty1 one, _Ty2 two) :one(one), two(two)
	{

	}
	void print()
	{
		cout << one << "\t" << two << endl;
	}
	template <class _Ty1, class _Ty2>
	friend ostream& operator<<(ostream& out, const MM<_Ty1,_Ty2>& object);
protected:
	_Ty1  one;
	_Ty2  two;
};
template <class _Ty1, class _Ty2> ostream& operator<<(ostream& out, const MM<_Ty1, _Ty2>& object) 
{
	out << object.one << "\t" << object.two;
	return out;
}

template <class _Ty1, class _Ty2>
class Data
{
public:
	Data(_Ty1 one, _Ty2 two) :one(one), two(two)
	{

	}
	void print()
	{
		cout << one << "\t" << two << endl;
	}
protected:
	_Ty1  one;
	_Ty2  two;
};

int main() 
{
	MM<string, int> info("月亮", 18);		//姓名 年龄
	MM<int, int> pos(100, 100);				//位置
	Data<MM<string, int>, MM<int, int>> test(info, pos);
	test.print();
	Data<MM<string, int>, Data<MM<string, int>, MM<int, int>>> test2(info,test);

	using DataType1 = Data<MM<string, int>, MM<int, int>>;
	using DataType2 = MM<string, int>;
	Data<DataType2, DataType1> test3(info, test);

	return 0;
}
```

# 2. 折叠参数

折叠参数就是一个参数包, 代表是多个未知,   tuple元组就是一个折叠参数的使用

折叠参数类型:

+ typename  ...Args  ,   Args参数包的包名 ,  本质是声明一个Args折叠参数类型
+ Args ...arg ,   折叠参数包类型的变量
+ ... , 多个意思

## 2.1 函数模板中使用折叠参数

+ 递归方式展开
+ 列表数据展开(推荐)
+ 完美转发的方式展开

```c++
#include <iostream>
#include <string>
#include <functional>
#include <initializer_list>
using namespace std;

//递归的方式剥离参数展开
template <typename _Ty>
void print(_Ty  data)
{
	cout << data << endl;
}
template <typename _Ty, typename ...Args>
void print(_Ty head, Args ...args)		//{1, 2, "string", "sdg", 1.3}
{
	cout << head << "\t";	//head=1  args...={2, "string", "sdg", 1.3} ....  {1.3}
	print(args...);
}

//列表的方式展开 例子1
template <typename _Ty>
void printData(_Ty  data)
{
	cout << data << "\t";
}

template <typename ...Args>
void printArgs(Args ...args)
{
	//int array[] = { (printData(args),0)... };
	initializer_list<int>{ (printData(args), 0)...};  // 展开参数包
	cout << endl;
}

// 列表的方式展开 例子2
template <typename T>
void addData(int& ans, T  data)
{
	ans += data;
}
template <typename ...Args>
void add(Args ...args)
{
	int ans = 0;
	initializer_list<int> {(addData(ans, args), 0)...};  // 展开参数包
	cout << ans << endl;
}

class Test
{
public:

	void testFunc()
	{
		if (func)
		{
			func();		//统一调用接口
		}
	}
	template <typename Func, typename ...Args>
	void connect(Func&& f, Args&& ...args)
	{
		func = bind(forward<Func>(f), forward<Args>(args)...);
	}
protected:
	function<void()> func;  //
};

void sum(int a, int b)
{
	cout << a + b << endl;
}
void printTest()
{
	cout << "提示信息" << endl;
}

int main()
{
	add(2, 2, 2);
	print(1, 2, "string", "sdg", 1.3);
	print(1, 2, "string", "sdg", 1.3, 1, 2, "string", "sdg", 1.3, 1, 2, "string", "sdg", 1.3);
	printArgs(1, 2, "string", "sdg", 1.3);
	printArgs(1, 2, "string", "sdg", 1.3, 1, 2, "string", "sdg", 1.3, 1, 2, "string", "sdg", 1.3);

	Test test;
	test.connect(sum, 1, 2);
	test.testFunc();

	test.connect(printTest);
	test.testFunc();

	test.connect([](int a, int b) { cout << a + b << endl; }, 3, 4);
	test.testFunc();
	return 0;
}
```

## 2.2 类模板中使用折叠参数

展开方式:

+ ==继承 +模板特化的方式展开(推荐)==
+ 递归的方式展开

```c++
#include <iostream>
#include <string>
#include <tuple>
using namespace std;

template <typename ...Args>
class Test;

// 特化
template <>
class Test<> {};

template <class _Ty,class ...Args>
class Test<_Ty, Args...> :public Test<Args...> 
{
public:
	Test() {}
	Test(_Ty data, Args ...args) :data(data), Test<Args...>(args...) {}
	Test<Args...>& getObject() 
	{
		return *this;
	}
	_Ty& getData() 
	{
		return data;
	}
protected:
	_Ty data;
};
void testFirst() 
{
	Test<string, int, double>  test("str", 1, 1.1);
	cout << test.getData() << "\t" << test.getObject().getData() << "\t" << test.getObject().getObject().getData() << endl;
    
	Test<string, string>  test1("str1", "str2");
	cout << test1.getData() << "\t" << test1.getObject().getData() << endl;
}


// 第二种方案 
template <class ...Args>
class my_tuple;

template <>
class my_tuple<> {};

template <typename _Ty, typename ...Args>
class my_tuple<_Ty, Args...> 
{
public:
	my_tuple() {}
	my_tuple(_Ty data, Args ...args) :data(data), args(args...) {}

	_Ty& getData() { return data; }
	my_tuple<Args...>& getObject() { return args; }
protected:
	_Ty data;
	my_tuple<Args...> args;  //自身
};

void testSecond() 
{
	my_tuple<string, int, double>  test("str", 1, 1.1);
	cout << test.getData() << "\t" << test.getObject().getData() << "\t" << test.getObject().getObject().getData() << endl;
    
	my_tuple<string, string>  test1("str1", "str2");
	cout << test1.getData() << "\t" << test1.getObject().getData() << endl;
}

int main() 
{
	testFirst();
	testSecond();
	tuple<string, int> tup;

	return 0;
}
```

