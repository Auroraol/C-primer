#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void test03(void)
{
    FILE *fp = NULL;
    fp = fopen("05.txt", "w");
    if (!fp)
    {
        printf("文件打开失败");
        return;
    }

    fclose(fp);
}

int main(void)
{
    // // test03();
    // char *p1 = "hello world";
    // // p1 = NULL;
    // // p1 = "dgaj";

    // strcpy(p1, "sdf");
    // printf("%s", *p1);

    for (int i = 0; i < 20; i++)
    {
    }

    return 0;
}