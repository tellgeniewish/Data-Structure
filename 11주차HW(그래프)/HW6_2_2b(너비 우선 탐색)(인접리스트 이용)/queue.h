#include <stdio.h>
#include <stdlib.h>
typedef int element; // ����� Ÿ��
typedef struct QueueNode { // ť�� ����� Ÿ��
    element data;
    struct QueueNode* link;
} QueueNode;
typedef struct { // ť ADT ����
    QueueNode* front, * rear;
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
    q->front = q->rear = NULL;
}
// ���� ���� ���� �Լ�
int is_empty(QueueType* q)
{
    return (q->front == NULL);
}
// ���� �Լ�
void enqueue(QueueType* q, element data)
{
    QueueNode* temp = (QueueNode*)malloc(sizeof(QueueNode));
    temp->data = data; // ������ ����
    temp->link = NULL; // ��ũ �ʵ带 NULL
    if (is_empty(q)) { // ť�� �����̸�
        q->front = temp;
        q->rear = temp;
    }
    else { // ť�� ������ �ƴϸ�
        q->rear->link = temp; // ������ �߿�
        q->rear = temp;
    }
}
// ���� �Լ�
element dequeue(QueueType* q)
{
    QueueNode* temp = q->front;
    element data;
    if (is_empty(q)) { // �������
        fprintf(stderr, "������ �������\n");
        exit(1);
    }
    else {
        data = temp->data; // �����͸� ������.
        q->front = q->front->link; // front�� �������
        if (q->front == NULL) // ���� ����
            q->rear = NULL;
        free(temp); // �����޸� ����
        return data; // ������ ��ȯ
    }
}
// ���� �Լ�
element peek(QueueType* q)
{
    if (is_empty(q)) { // �������
        fprintf(stderr, "������ �������\n");
        exit(1);
    }
    return q->front->data;
}

int get_count(QueueType* q)
{
    int count = 0;
    QueueNode* p = q->front;

    while (p != NULL) {
        count++;
        p = p->link;
    }

    return count;
}

void print_queue(QueueType* q)
{
    QueueNode* p = q->front;
    while (p != NULL) {
        printf("%d ", p->data);
        p = p->link;
    }
    printf("\n");
}