//응용화학과 20211689 김현진
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h> 
int fact(int n)
{
	if (n == 0 || n == 1)
		return 1;
	else
		return n * fact(n - 1);
}
int main(void)
{
	int n;
	printf("Enter a number:");
	scanf("%d", &n);

	printf("%d! = ", n);
	printf("%d\n", fact(n));
}