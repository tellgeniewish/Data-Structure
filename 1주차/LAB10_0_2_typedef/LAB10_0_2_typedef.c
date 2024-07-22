//응용화학과 20211689 김현진
#define _CRT_SECURE_NO_WARNINGS
typedef struct student {
	char name[20];
	int midterm;
	int final;
} Student;
#include <stdio.h> 
int main(void)
{
	Student aStudent;
	Student* sp = &aStudent; //4) sp가 aStudent를 가르키게한다
	
	printf("Enter student name: ");
	scanf("%s", sp->name); //5) 
	printf("Enter midterm and final score: ");
	scanf("%d %d", &sp->midterm, &sp->final); //6) 
	
	printf("\n이름\t중간\t학기말\n");
	printf("%s\t%d\t%d\n", sp->name, sp->midterm, sp->final); //7) 
}