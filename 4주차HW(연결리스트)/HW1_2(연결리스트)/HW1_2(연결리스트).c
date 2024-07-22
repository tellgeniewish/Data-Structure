//응용화학과 20211689 김현진
// HW1_2(개정3판) 
#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h> 
#include <stdio.h> 

typedef int element; // 항목의 정의
typedef struct ListNode { // 노드 타입
	element data;
	struct ListNode* link;
}ListNode;
//istNode* head = NULL;

void error(char* message) // 오류 처리 함수
{
	fprintf(stderr, "%s\n", message);
	//exit(1);
}

ListNode* insert_first(ListNode* head, element value)
{
	ListNode* p = (ListNode*)malloc(sizeof(ListNode)); //(1) 
	p->data = value; // (2) 
	p->link = head; // 헤드 포인터의 값을 복사 //(3) 
	head = p; // 헤드 포인터 변경 //(4) 
	return head; // 변경된 헤드 포인터 반환
}
//ListNode* insert_next(ListNode* head, ListNode* pre, element value)
// 노드 pre 뒤에 새로운 노드 삽입
ListNode* insert(ListNode* head, ListNode* pre, element value)
{
	ListNode* p = (ListNode*)malloc(sizeof(ListNode)); //(1) 
	p->data = value; //(2) 
	p->link = pre->link; //(3) 
	pre->link = p; //(4) 
	return head; //(5) 
}

ListNode* insert_last(ListNode* head, element value)
{
	ListNode* temp = head;
	ListNode* p = (ListNode*)malloc(sizeof(ListNode)); //(1) 
	p->data = value;
	p->link = NULL;
	// (2)
	if (head == NULL) // 공백 리스트이면
		head = p;
	else {
		while (temp->link != NULL)
			temp = temp->link;
		temp->link = p;
	}
	return head; // 변경된 헤드 포인터 반환
}/**/

//ListNode* delete_next(ListNode* head, ListNode* pre)
// pre가 가리키는 노드의 다음 노드를 삭제한다.
ListNode* delete(ListNode* head, ListNode* pre)
{
	ListNode* removed;
	removed = pre->link;
	pre->link = removed->link; // (2) 
	free(removed); // (3) 
	return head; // (4) 
}
ListNode* delete_first(ListNode* head)
{
	ListNode* removed;
	if (head == NULL)
		error("삭제할 항목이 없음");
	removed = head; // (1) 
	head = removed->link; // (2) 
	free(removed); // (3) 
	return head; // (4) 
}
ListNode* delete_last(ListNode* head)
{
	ListNode* temp = head;
	ListNode* prevTemp = NULL;
	ListNode* removed;
	if (head == NULL)
		error("삭제할 항목이 없음");
	if (temp->link == NULL) { // 하나의 노드
		free(head);
		head = NULL;
	}
	else { // 둘 이상의 노드
		while (temp->link != NULL) {
			prevTemp = temp;
			temp = temp->link;
		}
		removed = temp;
		prevTemp->link = NULL;
		free(removed);
		return head; // 그대로
	}
}

ListNode* search(ListNode* head, element x)
{
	ListNode* p;
	p = head;
	while (p != NULL) {
		if (p->data == x)
			return p; // 탐색 성공
		p = p->link;
	}
	return NULL; // 탐색 실패일 경우 NULL 반환
}
ListNode* concat(ListNode* head1, ListNode* head2)
{
	ListNode* p;
	if (head1 == NULL)
		return head2;
	else if (head2 == NULL)
		return head1;
	else {
		p = head1;
		while (p->link != NULL)
			p = p->link;
		p->link = head2;
		return head1;
	}
}
ListNode* reverse(ListNode* head)
{
	ListNode* p, * q, * r; // 순회 포인터로 p, q, r을 사용
	p = head; // p는 역순으로 만들 리스트
	q = NULL; // q는 역순으로 만들 노드
	while (p != NULL) {
		r = q; // r은 역순으로 된 리스트. r은 q, q는 p를 차례로 따라간다. 
		q = p;
		p = p->link;
		q->link = r; // q의 링크 방향을 바꾼다. 
	}
	return q; // q는 역순으로 된 리스트의 헤드 포인터
}

// 아래의 함수들을 정의하여 위의 프로그램에 추가하여 테스트를 위한 코드를(A)에 추가하라.
int is_in_list(ListNode* head, element item) // item 이 리스트에 있으면 1 을 아니면 0 을 반환
{
	ListNode* p;
	for (p = head; p != NULL; p = p->link) {
		if (p->data == item)
			return 1;
	}
	return 0;
}
int get_length(ListNode* head) // 단순 연결 리스트에 존재하는 노드의 수를 반환
{
	ListNode* p;
	int length = 0;
	for (p = head; p != NULL; p = p->link)
		length++;
	return length;
}
int get_total(ListNode* head) // 단순연결리스트의 모든 데이터 값을 더한 합을 반환
{
	ListNode* p;
	int sum = 0;
	for (p = head; p != NULL; p = p->link) {
		sum += p->data;
	}
	return sum;
}
element get_entry(ListNode* head, int pos) // pos 위치(0 이 첫 번째 노드)에 있는 노드의 data 를 반환
{
	if (pos < 0 || get_length(head) <= pos) {
		error("pos error");
		return head;
	}

	ListNode* p = head;
	for (int i = 0; i < pos; i++) {
		p = p->link;
	}
	return p->data;
}
ListNode* delete_by_key(ListNode* head, int key)
{
	/*ListNode* p = head;
	ListNode* prev = NULL;
	while (p != NULL) {
		if (p->data == key) {
			if (p == head) {
				head = head->link;
				free(p);

				return head;
			}
			prev->link = p->link;
			free(p);

			return head;
		}

		prev = p;
		p = p->link;
	}*/
	if (head == NULL) {
		return head;
	}
	if (key == head->data) {
		head = head->link;
		//head = delete_first(head);
		return head;
	}
	ListNode* p = head, * prev = NULL;
	for (p = head; p != NULL; p = p->link) {
		if (p->data == key) {
			prev->link = p->link;
			return head;
		}
		prev = p;
	}/**/

	printf("삭제하려는 key값 %d은 리스트에 없습니다\n", key);
	return head;
}
ListNode* insert_pos(ListNode* head, int pos, element value) // pos 위치에 value 를 갖는 노드를 추가
{
	if (pos < 0 || get_length(head) < pos) {
		error("pos error");
		return head;
	}

	//printf("\npos ===> %d\n", pos);
	ListNode* p = head;
	ListNode* new_node = (ListNode*)malloc(sizeof(ListNode));
	new_node->data = value;
	if (pos == 0) {
		new_node->link = head;
		head = new_node;
		//head = insert_first(head, value);
		return head;
	}
	ListNode* prev = NULL;
	for (int i = 0; i < pos; i++) {
		prev = p;
		p = p->link;
	}
	/*if (pos == get_length(head)) {
		//printf("\npos ===> %d\n", pos);
		//p->data = new_node->data;
		insert_last(head, value);
		return head;
	}*/
	prev->link = new_node;
	new_node->link = p;
	return head;
}
ListNode* delete_pos(ListNode* head, int pos) // pos 위치의 노드를 삭제
{
	if (pos < 0 || get_length(head) <= pos) {
		error("pos error");
		return head;
	}

	ListNode* p = head, * prev = NULL, * removed = NULL;
	if (pos == 0) {
		//head  = delete_first(head);
		removed = p;
		p = p->link;
		head = p;
		free(removed);/**/
		return head;
	}

	for (int i = 0; i < pos; i++) {
		prev = p;
		p = p->link;
	}
	removed = p;
	prev->link = p->link;
	free(removed);
	return head;
}

void print_list(ListNode* head)
{
	ListNode* p;
	for (p = head; p != NULL; p = p->link)
		printf("%d->", p->data);
	printf("NULL \n");
}
int main(void)
{
	ListNode* list1 = NULL, * list2 = NULL, * list3;

	//list1 = 30->20->10->를 만든다. 이때 10, 20, 30의 순으로 노드를 삽입한다. 
	list1 = insert_first(list1, 10);
	list1 = insert_first(list1, 20);
	list1 = insert_first(list1, 30);
	// list1을 출력 
	printf("list1 = ");
	print_list(list1);

	//list1의 맨 앞 노드를 삭제한다 즉, list1 = 20->30-> 
	list1 = delete_first(list1);
	// list1을 출력 
	printf("list1 = ");
	print_list(list1);
	//list2 = 11->22->33->44->를 만든다. 이때 11, 22, 33, 44의 순으로 노드를 삽입한다. 
	list2 = insert_first(list2, 11);
	list2 = insert(list2, list2, 22);
	list2 = insert(list2, list2->link, 33);
	list2 = insert(list2, list2->link->link, 44);
	// list2를 출력 
	printf("list2 = ");
	print_list(list2);
	// list2의 맨 뒤 노드를 삭제한다. 즉, list2 = 11->22->33-> 
	list2 = delete_last(list2);
	// list2를 출력 
	printf("list2 = ");
	print_list(list2);
	//list2를 역순으로 바꾼 리스트를 list3가 가리키게 한다. list3 = 33->22->11->를 만든다. 
	list3 = reverse(list2);
	//list3를 출력한다. 
	printf("list3 = ");
	print_list(list3);
	// list1 = 20->30->33->22->11->를 만든다. 즉, list1과 list3를 합쳐서 list1이 가리키게 한다. 
	list1 = concat(list1, list3);
	//list1을 출력한다. 
	printf("concat한 list1 = ");
	print_list(list1);

	//(A) 주의: 여기서부터는 list1만 사용하여 함수들을 테스트하자
	if (is_in_list(list1, 33) == 1)
		printf("삭제하려는 key값 33은 리스트에 있습니다\n");
	else
		printf("삭제하려는 key값 33은 리스트에 없습니다\n");

	printf("list1에 있는 모든 데이터 값의 합 %d\n", get_total(list1));

	element entry = get_entry(list1, 1);
	printf("list1 1번째 노드의 데이터 값은 %d\n", entry);
	entry = get_entry(list1, 3);
	printf("list1 3번째 노드의 데이터 값은 %d\n", entry);
	entry = get_entry(list1, 5);

	printf("pos값 체크(음수 = - 1) ---> ");
	insert_pos(list1, -1, 33);
	printf("list1 1번째 추가 ---> ");
	list1 = insert_pos(list1, 1, 1);
	print_list(list1);

	printf("list1 노드의 수는 %d\n", get_length(list1));
	printf("pos값 == get_length(list1) ---> ");
	list1 = insert_pos(list1, get_length(list1), 33);
	print_list(list1);

	list1 = delete_by_key(list1, 33);
	printf("list1 key 값 33을 삭제하면 list1 = ");
	print_list(list1);
	list1 = delete_by_key(list1, 1);
	printf("list1 key 값 1을 삭제하면 list1 = ");
	print_list(list1);/**/

	list1 = insert_pos(list1, 3, 33);
	printf("list1 3번째 노드의 데이터 값 33을 추가하면 list1 = ");
	print_list(list1);

	list1 = delete_pos(list1, 0);
	printf("list1 0번째 노드의 데이터 값 20을 삭제하면 list1 = ");
	print_list(list1);/**/
	list1 = delete_pos(list1, 2);
	printf("list1 2번째 노드의 데이터 값 33을 삭제하면 list1 = ");
	print_list(list1);
}/**/
/*
int main(void)
{
	ListNode* head1 = NULL, * head2;
	int i;
	for (i = 0; i < 5; i++) {
		head1 = insert_last(head1, i * 10);
		print_list(head1);
	}
	head2 = reverse(head1);
	print_list(head2);
	head2 = insert_pos(head2, 1, 99);
	print_list(head2);

	head2 = delete_last(head2);
	print_list(head2);

	head1 = NULL;
	head1 = insert_first(head1, 100);
	head1 = insert_first(head1, 200);
	print_list(head1);
	head1 = concat(head1, head2);
	print_list(head1);
}*/