//����ȭ�а� 20211689 ������
#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct ListNode { // ��� Ÿ��
	element data;
	struct ListNode* link;
} ListNode;

ListNode* insert_first(ListNode* head, element data)
{
	ListNode* node = (ListNode*)malloc(sizeof(ListNode));
	node->data = data;
	if (head == NULL) {
		head = node;
		node->link = head;
	}
	else {
		node->link = head->link; // (1) 
		head->link = node; // (2) 
	}
	return head; // ����� ��� �����͸� ��ȯ�Ѵ�. 
} 
ListNode* insert_last(ListNode* head, element data)
{
	ListNode* node = (ListNode*)malloc(sizeof(ListNode));
	node->data = data;
	if (head == NULL) {
		head = node;
		node->link = head;
	}
	else {
		node->link = head->link; // (1) 
		head->link = node; // (2) 
		head = node; // (3) 
	}
	return head; // ����� ��� �����͸� ��ȯ�Ѵ�.
}

ListNode* delete_first(ListNode* head)
{
	ListNode* temp;
	if (head == NULL) {
		printf("����Ʈ�� ��� ������ ����\n");
		return NULL;
	}
	else if (head == head->link) { // �� �ϳ��� ��尡 ��������
			temp = head;
		head = NULL;
		free(temp);
	}
	else {
		temp = head->link;
		head->link = temp->link;
		free(temp);
	}
	return head;
}
ListNode* delete_last(ListNode* head)
{
	ListNode* temp;
	if (head == NULL) {
		printf("����Ʈ�� ��� ������ ����\n");
		return NULL;
	}
	else if (head == head->link) { // �� �ϳ��� ��尡 ��������
		temp = head;
		head = NULL;
	}
	else {
		ListNode* pre = NULL;
		/**/temp = head->link;
		while (temp != head) {
			pre = temp;
			temp = temp->link;
		}
		/*for (temp = head->link; temp != head; temp = temp->link) {
			preP = temp;
		}*/
		pre->link = head->link;
		head = pre;
	}
	free(temp);
	return head;
}

ListNode* search(ListNode* head, element data)
{
	ListNode* p;
	for (p = head->link; p != head; p = p->link) {
		if (p->data == data)
			return p;
	}
	return NULL;
}
int get_size(ListNode* head)
{
	if (head == NULL)
		return 0;
	ListNode* p = head->link;
	int size;
	for (size = 1; p != head; size++)
		p = p->link;

	return size;
}
void print_list(ListNode* head) // Ʋ��: �����غ��ô�
{
	ListNode* p;
	if (head == NULL) return;
	
	p = head->link;
	if (p == head) {
		printf("%d->\n", p->data);
		return;
	}
	do {
		printf("%d->", p->data);
		p = p->link;
	} while (p != head);
	printf("%d->", p->data); // ������ ��� ���
	printf("\n");
}
int main(void) // ���� ���� ����Ʈ �׽�Ʈ ���α׷�
{
	ListNode* head = NULL;
	//printf("size = %d\n", get_size(head));
	// list = 10->20->30->40
	head = insert_last(head, 20);
	print_list(head);

	head = insert_last(head, 30);
	print_list(head);
	head = insert_last(head, 40);
	print_list(head);
	head = insert_first(head, 10);
	print_list(head);

	head = delete_first(head);
	print_list(head);
	
	/**/
	head = delete_last(head);
	printf("AFTER delete_last : ");
	print_list(head);

	printf("size = %d\n", get_size(head));
	if (search(head, 20) == NULL)
		printf("20 data�� ���� ���� ����.\n");
	else
		printf("20 data�� ���� ���� %p\n", search(head, 20));
	if (search(head, 50) == NULL)
		printf("50 data�� ���� ���� ����.\n");
	else
		printf("50 data�� ���� ���� %p\n", search(head, 50));
	return 0;
}