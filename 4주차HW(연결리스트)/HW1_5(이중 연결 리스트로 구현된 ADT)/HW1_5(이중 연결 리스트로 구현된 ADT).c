//응용화학과 20211689 김현진
#include <stdio.h>
#include <stdlib.h>
typedef int element;
typedef struct DListNode { // 이중연결 노드 타입
	element data;
	struct DListNode* llink;
	struct DListNode* rlink;
} DListNode;

void init(DListNode* phead) // 이중 연결 리스트를 초기화
{
	phead->llink = phead;
	phead->rlink = phead;
}
 
void dinsert(DListNode *before, element data) // 새로운 데이터를 노드 before의 오른쪽에 삽입한다.
{
	DListNode* newnode = (DListNode*)malloc(sizeof(DListNode));
	newnode->data = data;
	
	newnode->llink = before; // 1
	newnode->rlink = before->rlink; // 4
	before->rlink->llink = newnode; // 3
	before->rlink = newnode; // 2
}
void ddelete(DListNode* head, DListNode* removed) // 노드 removed를 삭제한다.
{
	if (removed == head) return;

	removed->rlink->llink = removed->llink;
	removed->llink->rlink = removed->rlink;
	free(removed);
}
void print_reverse_dlist(DListNode* head)
{
	DListNode* p = head->llink;
	while (p != head) {
		printf("<-| |%d| |-> ", p->data);
		p = p->llink;
	}
	/*
	DListNode* reverse = (DListNode*)malloc(sizeof(DListNode));
	init(reverse);
	DListNode* p = head->rlink;
	while (p != head) {
		dinsert(reverse, p->data);
		p = p->rlink;
	}
	*/
}
DListNode* search(DListNode* head, element data)
{
	DListNode* p;
	for (p = head->rlink; p != head; p = p->rlink) {
		if (p->data == data)
			return p;
	}
	return NULL;
}

void print_dlist(DListNode* phead) // 이중 연결 리스트의 노드를 출력
{
	DListNode* p;
	for (p = phead->rlink; p != phead; p = p->rlink) {
		printf("<-| |%d| |-> ", p->data);
	}
	printf("\n");
}
int main(void) // 이중 연결 리스트 테스트 프로그램
{
	DListNode* head = (DListNode*)malloc(sizeof(DListNode));
	init(head);
	printf("추가 단계\n");

	// 맨 앞에 노드를 삽입
	dinsert(head, 10);
	print_dlist(head);
	dinsert(head, 20);
	print_dlist(head);
	dinsert(head, 30);
	print_dlist(head);

	// 맨 뒤에 노드를 삽입하려면?
	dinsert(head->llink, 5);
	print_dlist(head);
		
	/*printf("\n삭제 단계\n");
	// 맨 앞의 노드를 삭제
	ddelete(head, head->rlink);
	print_dlist(head);
	// 맨 뒤의 노드를 삭제하려면?
	ddelete(head, head->llink);
	print_dlist(head);*/

	if (search(head, 20) == NULL)
		printf("20 data를 가진 노드는 없다.\n");
	else
		printf("20 data를 가진 노드는 %p\n", search(head, 20));
	if (search(head, 50) == NULL)
		printf("50 data를 가진 노드는 없다.\n");
	else
		printf("50 data를 가진 노드는 %p\n", search(head, 50));

	print_reverse_dlist(head);

	free(head);
	return 0;
}