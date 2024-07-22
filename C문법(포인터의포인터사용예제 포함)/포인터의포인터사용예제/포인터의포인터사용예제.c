// 예제 1

#include <stdio.h>
int globalData[3] = {10, 20, 30};

void changePointing(int *ptr)
{	
	int i;
	ptr = globalData;
}

int main(void)
{
	int i;
	int data[3] = {11, 22, 33};
	int *p = data;
	
	printf("함수호출후:\n");
	for (i = 0; i < 3; i++)
		printf("%d ", p[i]);
	printf("\n");

	changePointing(p);
	
	printf("함수호출후:\n");
	for (i = 0; i < 3; i++)
		printf("%d ", p[i]);
	printf("\n");
}