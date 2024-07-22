/*

(�ڵ� ��ü�� �����ϴ� �����̴�)

  �Ϸ��� �̸��� ����ڿ� �����鼭
  process�� �ܾ �ԷµǸ�
  ���� *���߿�* ��⿭�� ���� ����� �̸��� ����Ϸ��Ѵ�. 
  �̶� ��⿭�� ��������� "empty"��� ����Ѵ�.
  �̸� quit�� ���ö����� ����Ѵ�.

���� ��
aa bb cc process dd ee process process quit

��� �Է��� ���ٷ� ������ �����

cc
ee
dd

�̴�. ������ ���� ������ ���� �ִ�.

aa :�Է�
bb :�Է� 
cc  :�Է�
process  :�Է�
cc :���
dd :�Է�
ee :�Է�
process  :�Է�
ee :���
process :�Է�
dd :���
quit

���࿹:
xx process process yy zz process quit :�Է�
xx : ���
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
// �ʱ�ȭ �Լ�
void init(LinkedStackType *s)
{
	s->top = NULL;
}
// ���� ���� ���� �Լ�
int is_empty(LinkedStackType *s)
{
	return (s->top == NULL);
}

// ���� �Լ�
void push(LinkedStackType *s, element item)
{
	StackNode *temp = (StackNode *)malloc(sizeof(StackNode));
	temp->data = item;
	temp->link = s->top;
	s->top = temp;
}

// ���� �Լ�
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