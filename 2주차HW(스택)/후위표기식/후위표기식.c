#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 100
// ���α׷� 4.3���� ���� �ڵ� �߰�
typedef char element; // ��ü!
typedef struct {
	element data[MAX_STACK_SIZE];
	int top;
} StackType;

void init_stack(StackType* s) // ���� �ʱ�ȭ �Լ� 
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
// ���α׷� 4.3���� ���� �ڵ� �߰� ��
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
// ���� ǥ�� ���� ��� �Լ�
int eval(char exp[])
{
	int op1, op2, value, i = 0;
	int len = strlen(exp);
	char ch;
	StackType s;

	init_stack(&s);
	for (i = 0; i < len; i++) {
		ch = exp[i];
		if (ch != '+' && ch != '-' && ch != '*' && ch != '/') {
			value = ch - '0'; // �Է��� �ǿ������̸�
			push(&s, value);
		}
		else { //�������̸� �ǿ����ڸ� ���ÿ��� ����
			op2 = pop(&s);
			op1 = pop(&s);
			switch (ch) { //������ �����ϰ� ���ÿ� ����
			case '+': push(&s, op1 + op2); break;
			case '-': push(&s, op1 - op2); break;
			case '*': push(&s, op1 * op2); break;
			case '/': push(&s, op1 / op2); break;
			}
		}
	}
	return pop(&s);
}
int main(void)
{
	int result;
	printf("����ǥ����� 82/3-32*+\n");
	result = eval("82/3-32*+");
	printf("������� %d\n", result);
	return 0;
}
/*
���� s�� �����ϰ� �ʱ�ȭ�Ѵ�.
for �׸� in ����ǥ���
do if (�׸��� �ǿ������̸�)
push(s, item)
if (�׸��� ������ op�̸�)
then second �� pop(s)
first �� pop(s)
result �� first op second // op �� + - * /���� �ϳ�
push(s, result)
final_result �� pop(s); 
*/