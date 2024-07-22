//����ȭ�а� 20211689 ������
#include <stdio.h>
#include <stdlib.h>
typedef int element;
typedef struct DListNode { // ���߿��� ��� Ÿ��
	element data;
	struct DListNode* llink;
	struct DListNode* rlink;
} DListNode;

void init(DListNode* phead) // ���� ���� ����Ʈ�� �ʱ�ȭ
{
	phead->llink = phead;
	phead->rlink = phead;
}
 
void dinsert(DListNode *before, element data) // ���ο� �����͸� ��� before�� �����ʿ� �����Ѵ�.
{
	DListNode* newnode = (DListNode*)malloc(sizeof(DListNode));
	newnode->data = data;
	
	newnode->llink = before; // 1
	newnode->rlink = before->rlink; // 4
	before->rlink->llink = newnode; // 3
	before->rlink = newnode; // 2
}
void ddelete(DListNode* head, DListNode* removed) // ��� removed�� �����Ѵ�.
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

void print_dlist(DListNode* phead) // ���� ���� ����Ʈ�� ��带 ���
{
	DListNode* p;
	for (p = phead->rlink; p != phead; p = p->rlink) {
		printf("<-| |%d| |-> ", p->data);
	}
	printf("\n");
}
int main(void) // ���� ���� ����Ʈ �׽�Ʈ ���α׷�
{
	DListNode* head = (DListNode*)malloc(sizeof(DListNode));
	init(head);
	printf("�߰� �ܰ�\n");

	// �� �տ� ��带 ����
	dinsert(head, 10);
	print_dlist(head);
	dinsert(head, 20);
	print_dlist(head);
	dinsert(head, 30);
	print_dlist(head);

	// �� �ڿ� ��带 �����Ϸ���?
	dinsert(head->llink, 5);
	print_dlist(head);
		
	/*printf("\n���� �ܰ�\n");
	// �� ���� ��带 ����
	ddelete(head, head->rlink);
	print_dlist(head);
	// �� ���� ��带 �����Ϸ���?
	ddelete(head, head->llink);
	print_dlist(head);*/

	if (search(head, 20) == NULL)
		printf("20 data�� ���� ���� ����.\n");
	else
		printf("20 data�� ���� ���� %p\n", search(head, 20));
	if (search(head, 50) == NULL)
		printf("50 data�� ���� ���� ����.\n");
	else
		printf("50 data�� ���� ���� %p\n", search(head, 50));

	print_reverse_dlist(head);

	free(head);
	return 0;
}