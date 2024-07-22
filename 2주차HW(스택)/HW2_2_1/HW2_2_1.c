//����ȭ�а� 20211689 ������
#include <malloc.h> 
#include <stdio.h> 

typedef int element; // ������ ���� Ÿ�� ���� 
typedef struct StackNode {
	element item;
	struct StackNode* link;
} StackNode;
typedef struct {
	StackNode* top;
} LinkedStackType;

void init(LinkedStackType* s) // ���� �ʱ�ȭ �Լ� 
{
	s->top = NULL;
}
int is_empty(LinkedStackType* s) // ���� ���� ���� �Լ� 
{
	return (s->top == NULL);
}
int is_full(LinkedStackType* s) // ��ȭ ���� ���� �Լ� 
{
	return 0;
}
void push(LinkedStackType* s, element item) // �����Լ� 
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
element pop(LinkedStackType* s) // �����Լ� 
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
element peek(LinkedStackType* s) // ��ũ�Լ� 
{
	if (is_empty(s)) {
		fprintf(stderr, "������ �������\n");
		exit(1);
	}
	else
		return s->top->item;
}
void stack_print(LinkedStackType* s) {

	if (is_empty(s)) {
		printf("<empty>\n--\n");
		return;
	}

	StackNode* p = s->top;
	for (p = s->top; p != NULL; p = p->link) {
		printf("%d ", p->item);

		if (p == s->top)
			printf(" <- top");
		printf("\n");
	}
	printf("--\n");
}
void main() // ���Լ�
{
	LinkedStackType s;

	init(&s);
	stack_print(&s);

	push(&s, 10);
	stack_print(&s);

	push(&s, 20);
	stack_print(&s);

	push(&s, 30);
	stack_print(&s);

	push(&s, 40);
	stack_print(&s);

	pop(&s);
	//printf("%d\n", pop(&s));
	stack_print(&s);

	push(&s, 50);
	stack_print(&s);

	pop(&s);
	//printf("%d\n", pop(&s));
	stack_print(&s);

	pop(&s);
	//printf("%d\n", pop(&s));
	stack_print(&s);

	pop(&s);
	//printf("%d\n", pop(&s));/**/
	stack_print(&s);

	pop(&s);
	//printf("%d\n", pop(&s));/**/
	stack_print(&s);

	//printf("is_empty %d\n", is_empty(&s));
	//printf("is_full %d\n", is_full(&s));
}
/*void main() // ���Լ�
{
	LinkedStackType s;

	init(&s);

	push(&s, 1);
	push(&s, 2);
	push(&s, 3);

	printf("%d\n", pop(&s));
	printf("%d\n", pop(&s));
	printf("%d\n", pop(&s));
	printf("%d\n", is_empty(&s));
}*/