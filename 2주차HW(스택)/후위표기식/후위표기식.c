#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 100
// 프로그램 4.3에서 스택 코드 추가
typedef char element; // 교체!
typedef struct {
	element data[MAX_STACK_SIZE];
	int top;
} StackType;

void init_stack(StackType* s) // 스택 초기화 함수 
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
// 프로그램 4.3에서 스택 코드 추가 끝
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
// 후위 표기 수식 계산 함수
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
			value = ch - '0'; // 입력이 피연산자이면
			push(&s, value);
		}
		else { //연산자이면 피연산자를 스택에서 제거
			op2 = pop(&s);
			op1 = pop(&s);
			switch (ch) { //연산을 수행하고 스택에 저장
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
	printf("후위표기식은 82/3-32*+\n");
	result = eval("82/3-32*+");
	printf("결과값은 %d\n", result);
	return 0;
}
/*
스택 s를 생성하고 초기화한다.
for 항목 in 후위표기식
do if (항목이 피연산자이면)
push(s, item)
if (항목이 연산자 op이면)
then second ← pop(s)
first ← pop(s)
result ← first op second // op 는 + - * /중의 하나
push(s, result)
final_result ← pop(s); 
*/