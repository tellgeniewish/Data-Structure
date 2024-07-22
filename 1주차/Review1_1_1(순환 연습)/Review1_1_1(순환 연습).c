//응용화학과 20211689 김현진
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h> 
#include <string.h> 
void reverse_string(char* str, int s, int e)
{
	char tmp;	
	if (s < e) { //0, 2
		tmp = str[s]; //1
		str[s] = str[e]; //5
		str[e] = tmp; //1

		reverse_string(str, s + 1 , e - 1); //52341, 1, 4
	}
}
int main()
{ 
	char str[100];
	
	printf("Enter any string:"); 
	scanf("%s", str); //12345
	
	reverse_string(str, 0, strlen(str) - 1); //12345, 0, 4
	printf("\nReversed String is: %s", str);
	return 0;
}