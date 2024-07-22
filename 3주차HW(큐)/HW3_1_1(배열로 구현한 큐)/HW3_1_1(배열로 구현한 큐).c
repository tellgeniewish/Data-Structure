//����ȭ�а� 20211689 ������
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

void init(QueueType* q) // �ʱ�ȭ �Լ� 
{
	q->front = q->rear = 0;
}

int is_empty(QueueType* q) // ���� ���� ���� �Լ� 
{
	return (q->front == q->rear);
}
int is_full(QueueType* q) // ��ȭ ���� ���� �Լ� 
{
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

void enqueue(QueueType* q, element item) // ���� �Լ� 
{
	if (is_full(q)) {
		error("����ڰ� ��á���� ���ȸ�� �̿�");
		return;
	}
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	strcpy(q->queue[q->rear].name, item.name);	//q->queue[q->rear] = item.name;
	q->queue[q->rear].sex = item.sex; // ���� �ϳ��� strcpy ����ϸ� ����
}
element dequeue(QueueType* q) // ���� �Լ� 
{
	if (is_empty(q))
		error("ť�� ��������Դϴ�");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->queue[q->front];
}/**/
element peek(QueueType* q) // ������ �Լ�
{
	if (is_empty(q))
		error("ť�� ��������Դϴ�");
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
int main(void) // 2)�� �׽�Ʈ�ϱ����� �ӽ� main �Լ� # test driver
{
	QueueType manQ, womanQ;
	element newPerson;

	printf("���� �ּ� ���α׷��Դϴ�.\n");
	init(&manQ);
	init(&womanQ);

	char answer;
	printf("i<nsert, ���Է�>, c<heck, ����� üũ>, q<uit>: ");
	scanf("%c", &answer);
	while (answer != 'q') {
		switch (answer)
		{
		case 'i':
			printf("�̸��� �Է�:");
			scanf("%s", newPerson.name);
			while (getchar() != '\n');
			printf("������ �Է�<m or f>:");
			scanf("%c", &newPerson.sex);
			while (getchar() != '\n');

			if (newPerson.sex == 'm')
				enqueue(&manQ, newPerson);
			else
				enqueue(&womanQ, newPerson);
			break;
		case 'c':
			printf("���� ����� %d��: ", get_count(&manQ));
			print_queue(&manQ);
			printf("���� ����� %d��: ", get_count(&womanQ));
			print_queue(&womanQ);
			break;
		default:
			break;
		}
		if (1 <= get_count(&manQ) && 1 <= get_count(&womanQ)) {
			printf("Ŀ���� ź���߽��ϴ�! %s�� %s\n", dequeue(&manQ), dequeue(&womanQ));
		}
		//(A)�κ��� �� �� �ݺ� 
		printf("i<nsert, ���Է�>, c<heck, ����� üũ>, q<uit>: ");
		scanf("%c", &answer);
		while (getchar() != '\n');
	}
}
/*
void main() // �� �Լ� 
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