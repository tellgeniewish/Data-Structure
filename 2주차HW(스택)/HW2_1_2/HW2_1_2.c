//응용화학과 20211689 김현진
#define _CRT_SECURE_NO_WARNINGS
#include <string.h> 
#include <stdio.h> 
#define MAX_STACK_SIZE 3 // 배열을 이용한 스택은 사이즈의 제한이 있다 
#define MAX_STRING_SIZE 10

//typedef char element; // 스택을 위한 타입 정의 
typedef struct {
	int num;
	char name[MAX_STRING_SIZE];
} element;
element stack[MAX_STACK_SIZE];
int top = -1;

int is_empty() // 공백 상태 검출 함수 
{
	return (top == -1);
}
int is_full() // 포화 상태 검출 함수 
{
	return (top == (MAX_STACK_SIZE - 1));
}
void push(element item) // 삽입함수 
{
	if (is_full()) {
		fprintf(stderr, "스택 포화 에러\n");
		return;
	}
	else
		stack[++(top)] = item;
}
element pop() // 삭제함수 
{
	if (is_empty()) {
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else
		return stack[(top)--];
}
element peek() // 피크함수 
{
	if (is_empty()) {
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else
		return stack[top];
}
void stack_print()
{
	if (top == -1) {
		printf("<empty>\n--\n");
		return;
	}

	for (int i = top; i >= 0; i--) {
		//if (s->top == 0)
			//return;

		printf("[%d, %s]", stack[i].num, stack[i].name);

		if (i == top)//s->top == (MAX_STACK_SIZE - 1) //is_full(s)
			printf(" <- top");
		printf("\n");
	}
	printf("--\n");
}
void main() // 주함수
{
	stack_print();

	element e = {10, "ten"};
	push(e); // (10, “ten”) 삽입
	stack_print();

	e.num = 20;
	strcpy(e.name, "twenty");
	push(e); // (20, “twenty”) 삽입
	stack_print();

	e.num = 30;
	strcpy(e.name, "thirty");
	push(e); // (30, “thirty”) 삽입
	stack_print();

	e.num = 40;
	strcpy(e.name, "forty");
	push(e); // (40, “forty”) 삽입
	stack_print();

	pop(); // 삭제
	stack_print();

	e.num = 50;
	strcpy(e.name, "fifty");
	push(e); // (50, “fifty”) 삽입
	stack_print();

	pop(); // 삭제
	stack_print();
	pop(); // 삭제
	stack_print();
	pop(); // 삭제
	stack_print();
}
/*#include<stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 3

typedef int element;
typedef struct {

	element data[MAX_STACK_SIZE];
	int top;

}StackType;

void init_stack(StackType* s) {
	s->top = -1;
}

int is_empty(StackType* s) {
	return (s->top == -1);
}
int is_full(StackType* s) {
	return (s->top == (MAX_STACK_SIZE - 1));
}
void push(StackType* s, element item) {

	if (is_full(s)) {
		fprintf(stderr, "스택 포화 에러\n");
		return;
	}
	else
		s->top = s->top + 1;
	s->data[s->top] = item;
}

element pop(StackType* s) {

	if (is_empty(s)) {
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else return s->data[(s->top)--];
}
element peek(StackType* s) {

	if (is_empty(s)) {
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else
		return s->data[s->top];
}

void stack_print(StackType* s) {

	int i = 0;
	if (is_empty(s)) {
		printf("<empty>\n");
	}
	else {
		printf("%d <- top\n", s->data[s->top]);

		for (i = 1; i <= s->top; i++) {
			printf("%d \n", s->data[s->top - i]);
			printf("\n");
		}
	}
	printf("--\n");
}


int main() {
	StackType s;

	init_stack(&s);
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
	stack_print(&s);

	push(&s, 50);
	stack_print(&s);

	pop(&s);
	stack_print(&s);

	pop(&s);
	stack_print(&s);

	pop(&s);
	stack_print(&s);
}*/