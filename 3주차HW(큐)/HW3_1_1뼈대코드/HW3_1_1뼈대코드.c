//����ȭ�а� 20211689 ������
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 3 //3���� ����
#define MAX_STRING 100 // �߰�

typedef struct { //����
    char name[MAX_STRING];
} element;

typedef struct {
    element  queue[MAX_QUEUE_SIZE];
    int  front, rear;
} QueueType;
//
void error(char* message)
{
    fprintf(stderr, "%s\n", message);
    exit(1);
}
// �ʱ�ȭ �Լ�
void init(QueueType* q)
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

int get_count(QueueType* q)
{
    // �ڵ� �߰�
    return (q->rear - q->front + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
}

void print_queue(QueueType* q) // �߰�, 20141016 ����
{
    // �ڵ� �߰�
    /*for (int i = q->front + 1; i <= q->rear; i++) {
        printf("%s ", q->queue[i]);
    }
    printf("\n");*/
    int temp = (q->front + 1) % MAX_QUEUE_SIZE;
    while (temp != (q->rear + 1) % MAX_QUEUE_SIZE) {
        printf("%s ", q->queue[temp].name);
        temp = (temp + 1) % MAX_QUEUE_SIZE;
    }
    printf("\n");

}

void try_match(char* name, QueueType* partnerQ, QueueType* myQ) //�߰� �κ�: �� ���� �Լ� �̸�??
{
    // �ڵ� �߰�
    element inputName;
    strcpy(inputName.name, name);
    enqueue(myQ, inputName);

    if (1 <= get_count(myQ) && 1 <= get_count(partnerQ)) {
        printf("Ŀ���� ź���߽��ϴ�! %s�� %s\n", dequeue(myQ), dequeue(partnerQ));
    }
}

// 2)�� �׽�Ʈ�ϱ� ���� �ӽ� main �Լ�
/*
int main(void)
{
    QueueType manQ;
    element newPerson;
    char name[MAX_STRING];

    init(&manQ);

    printf("�̸��� �Է�:");
    scanf("%s", newPerson.name);
    enqueue(&manQ, newPerson);
    printf("%d��: ", get_count(&manQ));
    print_queue(&manQ);

    printf("�̸��� �Է�:");
    scanf("%s", newPerson.name);
    enqueue(&manQ, newPerson);
    printf("%d��: ", get_count(&manQ));
    print_queue(&manQ);

    printf("�̸��� �Է�:");
    scanf("%s", newPerson.name);
    enqueue(&manQ, newPerson); // ����ť�� ����� 3�̹Ƿ� 3��° ��Ҹ� �������ϸ� ��ȭ ������ ����
    printf("%d��: ", get_count(&manQ));
    print_queue(&manQ);
}
*/
int main(void)
{
     QueueType manQ, womanQ;
     char choice;
     char name[MAX_STRING];
     char gender;

     init(&manQ);
     init(&womanQ);

     printf("���� �ּ� ���α׷��Դϴ�.\n");

     printf("i(nsert, ���Է�), c(heck, ����� üũ), q(uit):");
     scanf("%c", &choice);

     while (choice != 'q') {
          switch(choice) {
          case 'i':
               printf("�̸��� �Է�:");
               scanf("%s", name);
               while (getchar() != '\n'); // ���� ����
               printf("������ �Է�(m or f):");
               scanf("%c", &gender);
               if (gender == 'm')
                    try_match(name, &womanQ, &manQ);
               else
                    try_match(name, &manQ, &womanQ);
               break;
          case 'c':
               printf("���� ����� %d��: ", get_count(&manQ));
               print_queue(&manQ);
               printf("���� ����� %d��: ", get_count(&womanQ));
               print_queue(&womanQ);
          }
          while (getchar() != '\n'); // ���� ����
          printf("i(nsert, ���Է�), c(heck, ����� üũ), q(uit):");
          scanf("%c", &choice);
     }
}