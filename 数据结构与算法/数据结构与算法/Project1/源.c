#include <stdio.h>

#define PI 3.14

int main(void)
{
	float r, s;
	printf("请输入圆的半径(cm)");
	scanf("%f", &r);
	s = PI * r * r;
	printf("圆的面积%f", &s);

}

