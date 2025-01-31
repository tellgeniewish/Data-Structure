#define _CRT_SECURE_NO_WARNINGS
#define MAX_STACK_SIZE 3
#define MAX_STRING_SIZE 100
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//�迭�� ���ڿ��� �ƴ� ���ڿ��� �ٲٰ� ���� �� element�� ������ typedef�� Ÿ�Ը� �ٲٸ� �ǰ�, �ڵ� ��ü�� �ٲ� �ʿ䰡 ����
//typedef int element;

typedef struct {
	char string[MAX_STRING_SIZE];
	int num;
}element;

typedef struct {
	element data[MAX_STACK_SIZE];
	int top;
}stack;

void init(stack* s) {
	s->top = -1;
}

int is_empty(stack* s) {
	return (s->top == -1);
}

int is_full(stack* s) {
	return (s->top == MAX_STACK_SIZE - 1);
}

void push(stack* s, element e) {
	if (is_full(s)) {
		fprintf(stderr, "���� ��ȭ ����\n");
		return;
	}

	s->data[++(s->top)] = e;
}

element pop(stack* s) {
	if (is_empty(s)) {
		fprintf(stderr, "���� ���� ����\n");
		exit(1);
	}

	return s->data[(s->top)--];
}

element peek(stack* s) {
	if (is_empty(s)) {
		fprintf(stderr, "���� ���� ����\n");
		exit(1);
	}

	return s->data[s->top];
}

void stack_print(stack* s) {
	if (s->top == -1) {
		printf("<empty>\n--\n");
		return;
	}

	printf("[%d, %s] <- top\n", s->data[s->top].num, s->data[s->top].string);

	for (int i = s->top - 1; i >= 0; i--)
		printf("[%d, %s]\n", s->data[i].num, s->data[i].string);
	printf("--\n");

	return;
}

int main(void) {
	stack* s = (stack*)malloc(sizeof(stack));
	element el;

	//������ s�� top�� -1�� �����ؼ� ����ִ� ������ ����
	init(s);

	stack_print(s);
	el.num = 10;
	strcpy(el.string, "ten");
	push(s, el);
	stack_print(s);

	el.num = 20;
	strcpy(el.string, "twenty");
	push(s, el);
	stack_print(s);

	el.num = 30;
	strcpy(el.string, "thirty");
	push(s, el);
	stack_print(s);

	el.num = 40;
	strcpy(el.string, "forty");
	push(s, el);
	stack_print(s);

	pop(s);
	stack_print(s);
	el.num = 50;
	strcpy(el.string, "fifty");
	push(s, el);
	stack_print(s);
	pop(s);
	stack_print(s);
	pop(s);
	stack_print(s);
	pop(s);
	stack_print(s);

	free(s);
}