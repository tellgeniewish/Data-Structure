//응용화학과 20211689 김현진
#define _CRT_SECURE_NO_WARNINGS
#include <string.h> 
#include <stdio.h> 
#define MAX_STACK_SIZE 10 // 배열을 이용한 스택은 사이즈의 제한이 있다 
#define MAX_STRING 10
typedef char element; // 스택을 위한 타입 정의 
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

int palindrome(char str[])
{
	StackType s; // 배열을 사용할 경우, 연결리스트를 사용하면 LinkedStackType s; 
	
	// 필요한 변수들 선언
	int i, tmp;
	int len = strlen(str);
	
	// 스택을 초기화하라
	init(&s);
	//printf("s.top -> %d\n", s.top);
	
	//str 의 문자들을 스택에 넣는다
	for (i = 0; i < len; i++) {
		//printf("i => %d\n", i);
		push(&s, str[i]);
		//printf("s.top -> %d\n", s.top);
	}
	//printf("s.data -> %s\n\n", s.data);
	
	//스택에서 하나씩 빼면서 str 의 문자들과 차례로 비교 
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
		printf("palindrome 입니다.\n");
	else
		printf("palindrome 이 아닙니다.\n");
}