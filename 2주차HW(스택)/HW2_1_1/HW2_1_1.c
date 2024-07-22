//응용화학과 20211689 김현진
#include <stdio.h> 
#define MAX_STACK_SIZE 3 // 배열을 이용한 스택은 사이즈의 제한이 있다 

typedef int element; // 스택을 위한 타입 정의 

typedef struct {
	element data[MAX_STACK_SIZE];
	int top;
} StackType;
void init(StackType* s) // 스택 초기화 함수 
{
	s->top = -1;
}
int is_empty(StackType* s) // 공백 상태 검출 함수 
{
	return (s->top == -1);
}
int is_full(StackType* s) // 포화 상태 검출 함수 
{
	return (s->top == (MAX_STACK_SIZE - 1));
}
void push(StackType* s, element item) // 삽입함수 
{
	if (is_full(s)) {
		fprintf(stderr, "스택 포화 에러\n");
		return;
	}
	else
		s->data[++(s->top)] = item;
}
element pop(StackType* s) // 삭제함수 
{
	if (is_empty(s)) {
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else
		return s->data[(s->top)--];
}
element peek(StackType* s) // 피크함수 
{
	if (is_empty(s)) {
		fprintf(stderr, "스택 공백 에러\n");
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
void main() // 주함수
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