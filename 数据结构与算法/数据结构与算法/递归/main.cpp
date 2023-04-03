#include <stdio.h>
void rec(int N);

int main()
{
	rec(11);
	return 0;
}

void rec(int N)
{
	if (N > 0)
	{
		rec(N - 10); //rec1
		rec(N - 1);  //rec2
	}
	printf("%d\n", N);    //此时的打印就相当于出栈 
	printf("*******\n");
	return;
}
