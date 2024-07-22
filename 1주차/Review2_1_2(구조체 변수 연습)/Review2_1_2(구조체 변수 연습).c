//����ȭ�а� 20211689 ������
#include <stdio.h> 
#include <stdlib.h> 
typedef struct Score { // 1) typedef���� ����ü Ÿ�� Score ����
	int midterm;
	int final;
} Score;
void printScore(Score* p) //2) 
{
	printf("�߰���� ������ %d\n", p->midterm);
	printf("�б⸻��� ������ %d\n", p->final);
}
Score* biggerScore(Score* p1, Score* p2) //3) 
{
	Score* big = (Score*)malloc(sizeof(Score));

	if (p1->midterm > p2->midterm)
		big->midterm = p1->midterm;
	else
		big->midterm = p2->midterm;

	if (p1->final > p2->final)
		big->final = p1->final;
	else
		big->final = p2->final;

	return big;
}
Score* totalScore(Score* p1, Score* p2) //4) 
{
	Score* total = (Score*)malloc(sizeof(Score));

	total->midterm = p1->midterm + p2->midterm;

	total->final = p1->final + p2->final;

	return total;
}
Score* createScore(int m, int f) //5) 
{
	Score* newScore = (Score*)malloc(sizeof(Score));

	newScore->midterm = m;

	newScore->final = f;

	return newScore;
}
//���� ���α׷����� main�Լ��� ������ ���� �����Ͽ�
//���� �������� ������ �϶�.
int main(void) {
	Score s1, s2; // ������ p1, p2��ſ� ����ü���� s1,s2
	Score* p3;
	
	s1.midterm = 50;
	s1.final = 100;

	s2.midterm = 70;
	s2.final = 70;

	printScore(&s1);
	printScore(&s2);
	
	printf("-----------------------------\n");
	printf("���� ������ ���� ����:\n");
	printScore(biggerScore(&s1, &s2));
	
	printf("-----------------------------\n");
	printf("�� ������ �� ��:\n");
	printScore(totalScore(&s1, &s2));
	
	printf("-----------------------------\n");
	p3 = createScore(100, 100);
	printScore(p3);
}