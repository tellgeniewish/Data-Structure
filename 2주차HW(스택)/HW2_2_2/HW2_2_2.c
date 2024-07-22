//응용화학과 20211689 김현진
#include <malloc.h>
//#include <string.h> 
#include <stdio.h> 

#define MAX_STRING_SIZE 10

typedef struct {
	int num;
	char name[MAX_STRING_SIZE];
} element;
typedef struct StackNode {
	element item;
	struct StackNode* link;
} StackNode;
typedef struct {
	StackNode* top;
} LinkedStackType;

void init(LinkedStackType* s) // 스택 초기화 함수 
{
	s->top = NULL;
}
int is_empty(LinkedStackType* s) // 공백 상태 검출 함수 
{
	return (s->top == NULL);
}
int is_full(LinkedStackType* s) // 포화 상태 검출 함수 
{
	return 0;
}
void push(LinkedStackType* s, element item) // 삽입함수 
{
	StackNode* temp = (StackNode*)malloc(sizeof(StackNode));
	if (temp == NULL) {
		fprintf(stderr, "메모리 할당에러\n");
		return;
	}
	else {
		temp->item = item;
		temp->link = s->top;
		s->top = temp;
	}
}
element pop(LinkedStackType* s) // 삭제함수 
{
	if (is_empty(s)) {
		fprintf(stderr, "스택이 비어있음\n");
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
element peek(LinkedStackType* s) // 피크함수 
{
	if (is_empty(s)) {
		fprintf(stderr, "스택이 비어있음\n");
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
		printf("[%d, %s]", p->item.num, p->item.name);

		if (p == s->top)
			printf(" <- top");
		printf("\n");
	}
	printf("--\n");
}
void main() // 주함수
{
	LinkedStackType s;
	init(&s);
	stack_print(&s);

	element e = { 10, "ten" };
	push(&s, e); // (10, “ten”) 삽입
	stack_print(&s);

	e.num = 20;
	strcpy(e.name, "twenty");
	push(&s, e); // (20, “twenty”) 삽입
	stack_print(&s);

	e.num = 30;
	strcpy(e.name, "thirty");
	push(&s, e); // (30, “thirty”) 삽입
	stack_print(&s);

	e.num = 40;
	strcpy(e.name, "forty");
	push(&s, e); // (40, “forty”) 삽입
	stack_print(&s);

	pop(&s); // 삭제
	stack_print(&s);

	e.num = 50;
	strcpy(e.name, "fifty");
	push(&s, e); // (50, “fifty”) 삽입
	stack_print(&s);

	pop(&s); // 삭제
	stack_print(&s);
	pop(&s); // 삭제
	stack_print(&s);
	pop(&s); // 삭제
	stack_print(&s);

	pop(&s); // 삭제
	stack_print(&s);
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