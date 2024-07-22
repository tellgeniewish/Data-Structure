
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>�� 
#include <malloc.h>�� 

typedef int element;
typedef struct StackNode {
	element item;
	struct StackNode* link;
} StackNode;

typedef struct {
	StackNode* top;
} LinkedStackType;

// �ʱ�ȭ �Լ�
void init(LinkedStackType* s) // �������� ����
{
	s->top = NULL;
}
// ���� ���� ���� �Լ�
int is_empty(LinkedStackType* s)// �������� ����
{
	return (s->top == NULL);
}
// ��ȭ ���� ���� �Լ�
int is_full(LinkedStackType* s)// �������� ����
{
	return 0;
}
// ���� �Լ�
void push(LinkedStackType* s, element item)// �������� ����
{
	StackNode* temp = (StackNode*)malloc(sizeof(StackNode));
	if (temp == NULL) {
		fprintf(stderr, "�޸� �Ҵ翡��\n");
		return;
	}
	else {
		temp->item = item;
		temp->link = s->top;
		s->top = temp;
	}
}
// ���� �Լ�
element pop(LinkedStackType* s)// �������� ����
{
	if (is_empty(s)) {
		fprintf(stderr, "������ �������\n");
		exit(1);
	}
	else {
		StackNode* temp = s->top;
		element item = temp->item;
		s->top = s->top->link;
		free(temp);
		return item;
	}
}
// ��ũ �Լ�
element peek(LinkedStackType* s)// �������� ����
{
	if (is_empty(s)) {
		fprintf(stderr, "������ �������\n");
		exit(1);
	}
	else {
		return s->top->item;
	}
}

void stack_print(LinkedStackType* s)// �������� ����
{
	StackNode* p = s->top;
	if (p) {
		while (p) {
			printf("%d ", p->item);
			p = p->link;
		}
	}
	else
		printf("(empty)\n");
}

// �� �Լ�
int main(void)
{
	LinkedStackType s;
	init(&s);
	element data, item;
	int sum = 0;
	int threshold;

	init(&s);

	scanf("%d", &data);
	while (data != -1) {
		push(&s, data);
		scanf("%d", &data);
	}

	scanf("%d", &threshold);

	// ���Ͽ� �ڵ� �߰�
	//sum += pop(&s);
	while (sum < threshold) {
		if (threshold < sum + peek(&s))
			break;
		sum += pop(&s);

		//printf("now %d\n", sum);
	}


	printf("%d\n", sum);
	stack_print(&s);

	return 0;
}