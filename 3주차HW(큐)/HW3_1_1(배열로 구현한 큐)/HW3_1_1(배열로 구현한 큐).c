//응용화학과 20211689 김현진
#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdio.h>
#define MAX_QUEUE_SIZE 3
#define MAX_NAME_SIZE 10
//typedef char element;
typedef struct {
	char name[MAX_NAME_SIZE];
	char sex;
} element;
typedef struct {
	element queue[MAX_QUEUE_SIZE];
	int front, rear;
} QueueType;

void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	//exit(1);
}

void init(QueueType* q) // 초기화 함수 
{
	q->front = q->rear = 0;
}

int is_empty(QueueType* q) // 공백 상태 검출 함수 
{
	return (q->front == q->rear);
}
int is_full(QueueType* q) // 포화 상태 검출 함수 
{
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

void enqueue(QueueType* q, element item) // 삽입 함수 
{
	if (is_full(q)) {
		error("대기자가 꽉찼으니 담기회를 이용");
		return;
	}
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	strcpy(q->queue[q->rear].name, item.name);	//q->queue[q->rear] = item.name;
	q->queue[q->rear].sex = item.sex; // 문자 하나라서 strcpy 사용하면 오류
}
element dequeue(QueueType* q) // 삭제 함수 
{
	if (is_empty(q))
		error("큐가 공백상태입니다");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->queue[q->front];
}/**/
element peek(QueueType* q) // 엿보기 함수
{
	if (is_empty(q))
		error("큐가 공백상태입니다");
	return q->queue[(q->front + 1) % MAX_QUEUE_SIZE];
}

int get_count(QueueType* q)
{
	return q->rear - q->front;
}
void print_queue(QueueType* q)
{
	for (int i = q->front + 1; i <= q->rear; i++) {
		printf("%s ", q->queue[i]);
	}
	printf("\n");
}
int main(void) // 2)를 테스트하기위한 임시 main 함수 # test driver
{
	QueueType manQ, womanQ;
	element newPerson;

	printf("미팅 주선 프로그램입니다.\n");
	init(&manQ);
	init(&womanQ);

	char answer;
	printf("i<nsert, 고객입력>, c<heck, 대기자 체크>, q<uit>: ");
	scanf("%c", &answer);
	while (answer != 'q') {
		switch (answer)
		{
		case 'i':
			printf("이름을 입력:");
			scanf("%s", newPerson.name);
			while (getchar() != '\n');
			printf("성별을 입력<m or f>:");
			scanf("%c", &newPerson.sex);
			while (getchar() != '\n');

			if (newPerson.sex == 'm')
				enqueue(&manQ, newPerson);
			else
				enqueue(&womanQ, newPerson);
			break;
		case 'c':
			printf("남성 대기자 %d명: ", get_count(&manQ));
			print_queue(&manQ);
			printf("여성 대기자 %d명: ", get_count(&womanQ));
			print_queue(&womanQ);
			break;
		default:
			break;
		}
		if (1 <= get_count(&manQ) && 1 <= get_count(&womanQ)) {
			printf("커플이 탄생했습니다! %s과 %s\n", dequeue(&manQ), dequeue(&womanQ));
		}
		//(A)부분을 몇 번 반복 
		printf("i<nsert, 고객입력>, c<heck, 대기자 체크>, q<uit>: ");
		scanf("%c", &answer);
		while (getchar() != '\n');
	}
}
/*
void main() // 주 함수 
{
	QueueType q;

	init(&q);
	printf("front=%d rear=%d\n", q.front, q.rear);
	enqueue(&q, 1);
	enqueue(&q, 2);
	enqueue(&q, 3);
	printf("dequeue()=%d\n", dequeue(&q));
	printf("dequeue()=%d\n", dequeue(&q));
	printf("dequeue()=%d\n", dequeue(&q));
	printf("front=%d rear=%d\n", q.front, q.rear);
}*/