#include <stdio.h>
#include <stdlib.h>
typedef int element; // 요소의 타입
typedef struct QueueNode { // 큐의 노드의 타입
    element data;
    struct QueueNode* link;
} QueueNode;
typedef struct { // 큐 ADT 구현
    QueueNode* front, * rear;
} QueueType;
//
void error(char* message)
{
    fprintf(stderr, "%s\n", message);
    exit(1);
}
// 초기화 함수
void init(QueueType* q)
{
    q->front = q->rear = NULL;
}
// 공백 상태 검출 함수
int is_empty(QueueType* q)
{
    return (q->front == NULL);
}
// 삽입 함수
void enqueue(QueueType* q, element data)
{
    QueueNode* temp = (QueueNode*)malloc(sizeof(QueueNode));
    temp->data = data; // 데이터 저장
    temp->link = NULL; // 링크 필드를 NULL
    if (is_empty(q)) { // 큐가 공백이면
        q->front = temp;
        q->rear = temp;
    }
    else { // 큐가 공백이 아니면
        q->rear->link = temp; // 순서가 중요
        q->rear = temp;
    }
}
// 삭제 함수
element dequeue(QueueType* q)
{
    QueueNode* temp = q->front;
    element data;
    if (is_empty(q)) { // 공백상태
        fprintf(stderr, "스택이 비어있음\n");
        exit(1);
    }
    else {
        data = temp->data; // 데이터를 꺼낸다.
        q->front = q->front->link; // front로 다음노드
        if (q->front == NULL) // 공백 상태
            q->rear = NULL;
        free(temp); // 동적메모리 해제
        return data; // 데이터 반환
    }
}
// 보기 함수
element peek(QueueType* q)
{
    if (is_empty(q)) { // 공백상태
        fprintf(stderr, "스택이 비어있음\n");
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