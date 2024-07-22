
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

// ===== ����ť �ڵ� ======
#define MAX_QUEUE_SIZE 4
typedef int element;
typedef struct { // ť Ÿ��
	element  queue[MAX_QUEUE_SIZE];
	int  front, rear;
} QueueType;

// ���� �Լ�
void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

// ���� ���� ���� �Լ�
void init_queue(QueueType* q)
{
	q->front = q->rear = 0;
}

// ���� ���� ���� �Լ�
int is_empty(QueueType* q)
{
	return (q->front == q->rear);
}

// ��ȭ ���� ���� �Լ�
int is_full(QueueType* q)
{
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

// ���� �Լ�
void enqueue(QueueType* q, element item)
{
	if (is_full(q))
		error("ť�� ��ȭ�����Դϴ�");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->queue[q->rear] = item;
}

// ���� �Լ�
element dequeue(QueueType* q)
{
	if (is_empty(q))
		error("ť�� ��������Դϴ�");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->queue[q->front];
}

// ���� �Լ�
element peek(QueueType* q)
{
	if (is_empty(q))
		error("ť�� ��������Դϴ�");
	return q->queue[(q->front + 1) % MAX_QUEUE_SIZE];
}

void nodeIncrease(QueueType* q) // �� �Լ��� �ۼ��Ѵ�
{
	// �ڵ带 �ۼ��Ѵ�
	//printf("COME %d %d\n", q->front, q->queue[q->front]);
	if (is_empty(q))
		return;
	int i = 0;
	while (i <= q->front) {
		q->queue[q->front] *= 10;
		//printf("%d %d\n", i, q->queue[q->front]);
		i++;
	}
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
}

void print_queue(QueueType* q) // �� �Լ��� �ۼ��Ѵ�
{
	// �ڵ带 �ۼ��Ѵ�
	int temp = (q->front + 1) % MAX_QUEUE_SIZE;

	while (temp != (q->rear + 1) % MAX_QUEUE_SIZE) {
		printf("%d\n", q->queue[temp]);
		temp = (temp + 1) % MAX_QUEUE_SIZE;
	}
	printf("end\n");
}

int main(void) // �������� ����
{
	QueueType q;
	char choice;
	element data;

	init_queue(&q);
	scanf("%c", &choice);
	while (choice != 'q') {
		switch (choice) {
		case 'e':
			scanf("%d", &data);
			enqueue(&q, data);
			break;
		case 'd':
			dequeue(&q);
		}
		while (getchar() != '\n');
		scanf("%c", &choice);
	}

	nodeIncrease(&q);
	print_queue(&q);

	return 0;
}