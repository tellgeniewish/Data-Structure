//����ȭ�а� 20211689 ������
#define _CRT_SECURE_NO_WARNINGS
#include <string.h> 
#include <stdio.h> 
#define MAX_STACK_SIZE 10 // �迭�� �̿��� ������ �������� ������ �ִ� 
#define MAX_STRING 10
typedef char element; // ������ ���� Ÿ�� ���� 
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

int palindrome(char str[])
{
	StackType s; // �迭�� ����� ���, ���Ḯ��Ʈ�� ����ϸ� LinkedStackType s; 
	
	// �ʿ��� ������ ����
	int i, tmp;
	int len = strlen(str);
	
	// ������ �ʱ�ȭ�϶�
	init(&s);
	//printf("s.top -> %d\n", s.top);
	
	//str �� ���ڵ��� ���ÿ� �ִ´�
	for (i = 0; i < len; i++) {
		//printf("i => %d\n", i);
		push(&s, str[i]);
		//printf("s.top -> %d\n", s.top);
	}
	//printf("s.data -> %s\n\n", s.data);
	
	//���ÿ��� �ϳ��� ���鼭 str �� ���ڵ�� ���ʷ� �� 
	for (i = 0; i < len / 2; i++) {
		//printf("i ---> %d\n", i);
		//char in = peek(&s);
		//printf("peek -> %c\n", in);
		if (str[i] != peek(&s)) {
			return 0;
		}
		pop(&s);

		//len--;
	}
	return 1;
}
int main(void)
{
	char word[MAX_STRING];

	printf("Enter a word to check palindrome: ");
	scanf("%s", word);

	if (palindrome(word))
		printf("palindrome �Դϴ�.\n");
	else
		printf("palindrome �� �ƴմϴ�.\n");
}