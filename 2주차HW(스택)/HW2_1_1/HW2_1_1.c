//����ȭ�а� 20211689 ������
#include <stdio.h> 
#define MAX_STACK_SIZE 3 // �迭�� �̿��� ������ �������� ������ �ִ� 

typedef int element; // ������ ���� Ÿ�� ���� 

typedef struct {
	element data[MAX_STACK_SIZE];
	int top;
} StackType;
void init(StackType* s) // ���� �ʱ�ȭ �Լ� 
{
	s->top = -1;
}
int is_empty(StackType* s) // ���� ���� ���� �Լ� 
{
	return (s->top == -1);
}
int is_full(StackType* s) // ��ȭ ���� ���� �Լ� 
{
	return (s->top == (MAX_STACK_SIZE - 1));
}
void push(StackType* s, element item) // �����Լ� 
{
	if (is_full(s)) {
		fprintf(stderr, "���� ��ȭ ����\n");
		return;
	}
	else
		s->data[++(s->top)] = item;
}
element pop(StackType* s) // �����Լ� 
{
	if (is_empty(s)) {
		fprintf(stderr, "���� ���� ����\n");
		exit(1);
	}
	else
		return s->data[(s->top)--];
}
element peek(StackType* s) // ��ũ�Լ� 
{
	if (is_empty(s)) {
		fprintf(stderr, "���� ���� ����\n");
		exit(1);
	}
	else
		return s->data[s->top];
}
void stack_print(StackType* s)
{
	if (s->top == -1) {
		printf("<empty>\n--\n");
		return;
	}

	for (int i = s->top; i >= 0; i--) {
		//if (s->top == 0)
			//return;

		printf("%d", s->data[i]);

		if (i == s->top)//s->top == (MAX_STACK_SIZE - 1) //is_full(s)
			printf(" <- top");
		printf("\n");
	}
	printf("--\n");
}
void main() // ���Լ�
{
	StackType s;

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
	
	//printf("is_empty %d\n", is_empty(&s));
	//printf("is_full %d\n", is_full(&s));
}