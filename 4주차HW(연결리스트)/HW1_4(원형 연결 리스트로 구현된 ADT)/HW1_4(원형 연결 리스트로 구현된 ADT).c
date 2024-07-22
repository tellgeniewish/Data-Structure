//응용화학과 20211689 김현진
#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct ListNode { // 노드 타입
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
	return head; // 변경된 헤드 포인터를 반환한다. 
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
	return head; // 변경된 헤드 포인터를 반환한다.
}

ListNode* delete_first(ListNode* head)
{
	ListNode* temp;
	if (head == NULL) {
		printf("리스트가 비어 삭제를 못함\n");
		return NULL;
	}
	else if (head == head->link) { // 즉 하나의 노드가 남았을때
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
		printf("리스트가 비어 삭제를 못함\n");
		return NULL;
	}
	else if (head == head->link) { // 즉 하나의 노드가 남았을때
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
void print_list(ListNode* head) // 틀림: 수정해봅시다
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
	printf("%d->", p->data); // 마지막 노드 출력
	printf("\n");
}
int main(void) // 원형 연결 리스트 테스트 프로그램
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
		printf("20 data를 가진 노드는 없다.\n");
	else
		printf("20 data를 가진 노드는 %p\n", search(head, 20));
	if (search(head, 50) == NULL)
		printf("50 data를 가진 노드는 없다.\n");
	else
		printf("50 data를 가진 노드는 %p\n", search(head, 50));
	return 0;
}