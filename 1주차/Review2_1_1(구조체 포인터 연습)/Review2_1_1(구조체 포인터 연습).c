//응용화학과 20211689 김현진
#include <stdio.h> 
#include <stdlib.h> 
typedef struct Score { // 1) typedef으로 구조체 타입 Score 정의
	int midterm;
	int final;
} Score;
void printScore(Score* p) //2) 
{
	printf("중간고사 성적은 %d\n", p->midterm);
	printf("학기말고사 성적은 %d\n", p->final);
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
int main(void) {
	Score* p1, * p2, * p3;
	//1)p1, p2에 Score를 저장하기위한
	// 메모리를 할당하고
	p1 = (Score*)malloc(sizeof(Score));
	p2 = (Score*)malloc(sizeof(Score));
	// 값을 대입한다. 각각(50, 100), (70, 70)
	p1->midterm = 50;
	p1->final = 100;

	p2->midterm = 70;
	p2->final = 70;
	
	printScore(p1);
	printScore(p2);

	printf("-----------------------------\n");
	printf("둘중 성적이 좋은 점수:\n");
	printScore(biggerScore(p1, p2));

	printf("-----------------------------\n");
	printf("두 성적의 총 합:\n");
	printScore(totalScore(p1, p2));

	printf("-----------------------------\n");
	p3 = createScore(100, 100);
	printScore(p3);
}