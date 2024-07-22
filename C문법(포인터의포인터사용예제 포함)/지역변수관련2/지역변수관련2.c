/*

(코드 전체를 제출하는 문제이다)

  일련의 이름을 대기자에 넣으면서
  process란 단어가 입력되면
  가장 *나중에* 대기열에 오른 사람의 이름을 출력하려한다. 
  이때 대기열이 비어있으면 "empty"라고 출력한다.
  이를 quit가 나올때까지 계속한다.

예를 들어서
aa bb cc process dd ee process process quit

라는 입력이 한줄로 들어오면 출력은

cc
ee
dd

이다. 다음과 같이 실행할 수도 있다.

aa :입력
bb :입력 
cc  :입력
process  :입력
cc :출력
dd :입력
ee :입력
process  :입력
ee :출력
process :입력
dd :출력
quit

실행예:
xx process process yy zz process quit :입력
xx : 출력
empty
zz
*/

#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct {
	char name[20];
} element;
typedef struct StackNode {
	element data;
	struct StackNode *link;
} StackNode;

typedef struct {
	StackNode *top;
} LinkedStackType;
// 초기화 함수
void init(LinkedStackType *s)
{
	s->top = NULL;
}
// 공백 상태 검출 함수
int is_empty(LinkedStackType *s)
{
	return (s->top == NULL);
}

// 삽입 함수
void push(LinkedStackType *s, element item)
{
	StackNode *temp = (StackNode *)malloc(sizeof(StackNode));
	temp->data = item;
	temp->link = s->top;
	s->top = temp;
}

// 삭제 함수
element pop(LinkedStackType *s)
{
	if (is_empty(s)) {
		fprintf(stdout, "empty\n");
	}
	else {
		StackNode *temp = s->top;
		element data = temp->data;
		s->top = s->top->link;
		free(temp);
		return data;
	}
}
int main(void)
{
	LinkedStackType s;
	element ele;
	init(&s);

	scanf("%s", ele.name);
	while (strcmp(ele.name, "quit") != 0) {
        if (strcmp(ele.name, "process") == 0)
			if (is_empty(&s))
				printf("empty\n");
			else 
				printf("%s\n", pop(&s).name);			
		else
			push(&s, ele);
		scanf("%s", ele.name);
	}
}