//����ȭ�а� 20211689 ������
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
	Student* sp = &aStudent; //4) sp�� aStudent�� ����Ű���Ѵ�
	
	printf("Enter student name: ");
	scanf("%s", sp->name); //5) 
	printf("Enter midterm and final score: ");
	scanf("%d %d", &sp->midterm, &sp->final); //6) 
	
	printf("\n�̸�\t�߰�\t�б⸻\n");
	printf("%s\t%d\t%d\n", sp->name, sp->midterm, sp->final); //7) 
}