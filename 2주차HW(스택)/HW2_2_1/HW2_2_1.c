//응용화학과 20211689 김현진
#include <malloc.h> 
#include <stdio.h> 

typedef int element; // 스택을 위한 타입 정의 
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
		printf("%d ", p->item);

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
/*void main() // 주함수
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