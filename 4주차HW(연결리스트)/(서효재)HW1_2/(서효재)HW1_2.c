#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct ListNode {
	element data;
	struct ListNode* link;
} ListNode;

void error(char* message) {
	fprintf(stderr, "%s\n", message);
	exit(1);
}

//��� pre �ڿ� ���ο� ��� ����
ListNode* insert_next(ListNode* head, ListNode* pre, element value) {
	ListNode* new = (ListNode*)malloc(sizeof(ListNode));
	new->data = value;
	new->link = pre->link;
	pre->link = new;

	return head;
}

//��� ó���� ���ο� ��� ����
ListNode* insert_first(ListNode* head, int value) {
	ListNode* new = (ListNode*)malloc(sizeof(ListNode));
	new->data = value;
	new->link = head;
	head = new;

	return head;
}

//��� �������� ���ο� ��� ����
ListNode* insert_last(ListNode* head, int value) {
	ListNode* temp = head;
	ListNode* new = (ListNode*)malloc(sizeof(ListNode));
	new->data = value;
	new->link = NULL;

	if (head == NULL) {
		head = new;
		return head;
	}

	while (temp->link != NULL)
		temp = temp->link;
	temp->link = new;

	return head;
}

//pre�� ����Ű�� ����� ���� ��带 ����
ListNode* delete_next(ListNode* head, ListNode* pre) {
	ListNode* removed;
	removed = pre->link;
	pre->link = removed->link;
	free(removed);

	return head;
}

//ó�� ��� ����
ListNode* delete_first(ListNode* head) {
	if (head == NULL)
		error("������ �׸��� ����\n");

	ListNode* removed;
	removed = head;
	head = removed->link;
	free(removed);

	return head;
}

//������ ��� ����
ListNode* delete_last(ListNode* head) {
	ListNode* temp = head;
	ListNode* preTemp = NULL;
	ListNode* removed;

	if (head == NULL)
		error("������ �׸��� ����\n");
	else if (head->link == NULL) {
		free(head);
		head = NULL;
	}
	else {
		while (temp->link != NULL) {
			preTemp = temp;
			temp = temp->link;
		}

		removed = temp;
		preTemp->link = NULL;
		free(removed);
	}

	return head;
}

void print_list(ListNode* head) {
	ListNode* temp = head;
	while (temp != NULL) {
		printf("%d->", temp->data);
		temp = temp->link;
	}
	printf("\n");
}

//��ũ����Ʈ���� int x ã��
ListNode* search(ListNode* head, int x) {
	ListNode* p;
	p = head;

	while (p != NULL) {
		if (p->data == x)
			return p;
		p = p->link;
	}

	return NULL;
}

//��ũ����Ʈ �ΰ��� �����ϱ�
ListNode* concat(ListNode* head1, ListNode* head2) {
	ListNode* p = NULL;

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

//������
ListNode* reverse(ListNode* head) {
	ListNode* p, * q = NULL, * r = NULL;
	p = head;

	while (p != NULL) {
		r = q;
		q = p;
		p = p->link;
		q->link = r;
	}

	return q;
}

int is_in_list(ListNode* head, element item) {
	if (search(head, item) == NULL)
		return 0;
	return 1;
}

int get_length(ListNode* head) {
	int i; ListNode* p = head;
	for (i = 0; p != NULL; i++)
		p = p->link;

	return i;
}

int get_total(ListNode* head) {
	int add = 0; ListNode* p = head;

	while (p != NULL) {
		add += p->data;
		p = p->link;
	}

	return add;
}

element get_entry(ListNode* head, int pos) {
	ListNode* p = head;
	for (int i = 0; i < pos; i++) {
		p = p->link;

		if (p == NULL) {
			printf("pos���� �� ����Ʈ�������� Ů�ϴ�.\n");
			return 0;
		}
	}

	return p->data;
}

ListNode* delete_by_key(ListNode* head, int key) {
	ListNode* removed = head;
	ListNode* pre = NULL;
	while (removed != NULL) {
		if (removed->data == key) {
			if (removed == head) {
				head = head->link;
				free(removed);

				return head;
			}
			pre->link = removed->link;
			free(removed);

			return head;
		}

		pre = removed;
		removed = removed->link;
	}

	printf("�ش��ϴ� key���� ����Ʈ�� �������� �ʽ��ϴ�.\n");
	return head;
}

ListNode* insert_pos(ListNode* head, int pos, element value) {
	if (pos < 0) {
		printf("pos���� �����Դϴ�.\n");
		return head;
	}

	ListNode* new = (ListNode*)malloc(sizeof(ListNode));
	new->data = value;

	if (pos == 0) {
		new->link = head;
		head = new;

		return head;
	}

	ListNode* temp = head;
	ListNode* pre = NULL;

	for (int i = 0; i < pos; i++) {
		if (temp == NULL) {
			printf("pos���� �� ����Ʈ�������� Ů�ϴ�.\n");
			return head;
		}

		pre = temp;
		temp = temp->link;
	}

	pre->link = new;
	new->link = temp;

	return head;
}

ListNode* delete_pos(ListNode* head, int pos) {
	if (pos < 0) {
		printf("pos���� �����Դϴ�.\n");
		return head;
	}

	ListNode* temp = head;
	ListNode* pre = NULL;

	if (pos == 0) {
		pre = temp;
		temp = temp->link;

		head = temp;
		free(pre);

		return head;
	}

	for (int i = 0; i < pos; i++) {
		pre = temp;
		temp = temp->link;

		if (temp == NULL) {
			printf("pos���� �� ����Ʈ�������� Ů�ϴ�.\n");
			return head;
		}
	}

	pre->link = temp->link;
	free(temp);

	return head;
}


int main(void) {
	ListNode* list1 = NULL, * list2 = NULL, * list3;

	//10, 20, 30�� ������� list1 �� ó���� ����
	list1 = insert_first(list1, 10);
	list1 = insert_first(list1, 20);
	list1 = insert_first(list1, 30);
	//���
	printf("list1 = ");
	print_list(list1);

	//�� �� ��� ����
	list1 = delete_first(list1);
	//���
	printf("list1 = ");
	print_list(list1);

	//11, 22, 33, 44�� ������� list2 �������� ����
	list2 = insert_last(list2, 11);
	list2 = insert_last(list2, 22);
	list2 = insert_last(list2, 33);
	list2 = insert_last(list2, 44);
	//���
	printf("list2 = ");
	print_list(list2);

	//�� �� ��� ����
	list2 = delete_last(list2);
	//���
	printf("list2 = ");
	print_list(list2);

	//list2�� ������ list3
	list3 = reverse(list2);
	//���
	printf("list3 = ");
	print_list(list3);

	//list1�� list3�� ����
	list1 = concat(list1, list3);
	//���
	printf("list1 = ");
	print_list(list1);

	//list1�� ������ üũ (A)
	//is_in_list
	element item;
	printf("ã�� ���� �����Ͱ�: ");
	scanf("%d", &item);

	if (is_in_list(list1, item))
		printf("%d�� list1 �ȿ� �ֽ��ϴ�\n", item);
	else
		printf("%d��(��) list1 �ȿ� �����ϴ�\n", item);

	//get_length
	printf("list1�� �� �����ͼ��� %d\n", get_length(list1));

	//get_total
	printf("list1�� �����Ͱ��� ���� %d\n", get_total(list1));

	//get_entry 
	int index;
	element findData;
	printf("ã�� ���� �������� �ε�����: ");
	scanf("%d", &index);

	findData = get_entry(list1, index);
	if (findData != 0)
		printf("%d�� �����Ͱ��� %d\n", index, get_entry(list1, index));

	//delte_by_key
	int data_key;
	printf("�����ϰ� ���� �����Ͱ�: ");
	scanf("%d", &data_key);
	list1 = delete_by_key(list1, data_key);
	printf("������(key)���� %d�� ��带 ������ �� list1 = ", data_key);
	print_list(list1);

	//insert_pos
	int inPos, inData;
	printf("�����ϰ� ���� ��ġ(pos��)�� �����Ͱ�: ");
	scanf("%d %d", &inPos, &inData);
	list1 = insert_pos(list1, inPos, inData);
	printf("pos���� %d�� �� %d�� ������ �� list1 = ", inPos, inData);
	print_list(list1);

	//delete_pos
	int delPos;
	printf("�����ϰ� ���� �����Ͱ��� ��ġ(pos��): ");
	scanf("%d", &delPos);
	list1 = delete_pos(list1, delPos);
	printf("pos���� %d�� ��带 ������ �� list1 = ", delPos);
	print_list(list1);

	return 0;
}
/*
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct ListNode {
	element data;
	struct ListNode* link;
} ListNode;

void error(char* message) {
	fprintf(stderr, "%s\n", message);
	exit(1);
}

//��� pre �ڿ� ���ο� ��� ����
ListNode* insert_next(ListNode* head, ListNode* pre, element value) {
	ListNode* new = (ListNode*)malloc(sizeof(ListNode));
	new->data = value;
	new->link = pre->link;
	pre->link = new;

	return head;
}

//��� ó���� ���ο� ��� ����
ListNode* insert_first(ListNode* head, int value) {
	ListNode* new = (ListNode*)malloc(sizeof(ListNode));
	new->data = value;
	new->link = head;
	head = new;

	return head;
}

//��� �������� ���ο� ��� ����
ListNode* insert_last(ListNode* head, int value) {
	ListNode* temp = head;
	ListNode* new = (ListNode*)malloc(sizeof(ListNode));
	new->data = value;
	new->link = NULL;

	if (head == NULL) {
		head = new;
		return head;
	}

	while (temp->link != NULL)
		temp = temp->link;
	temp->link = new;

	return head;
}

//pre�� ����Ű�� ����� ���� ��带 ����
ListNode* delete_next(ListNode* head, ListNode* pre) {
	ListNode* removed;
	removed = pre->link;
	pre->link = removed->link;
	free(removed);

	return head;
}

//ó�� ��� ����
ListNode* delete_first(ListNode* head) {
	if (head == NULL)
		error("������ �׸��� ����\n");

	ListNode* removed;
	removed = head;
	head = removed->link;
	free(removed);

	return head;
}

//������ ��� ����
ListNode* delete_last(ListNode* head) {
	ListNode* temp = head;
	ListNode* preTemp = NULL;
	ListNode* removed;

	if (head == NULL)
		error("������ �׸��� ����\n");
	else if (head->link == NULL) {
		free(head);
		head = NULL;
	}
	else {
		while (temp->link != NULL) {
			preTemp = temp;
			temp = temp->link;
		}

		removed = temp;
		preTemp->link = NULL;
		free(removed);
	}

	return head;
}

void print_list(ListNode* head) {
	ListNode* temp = head;
	while (temp != NULL) {
		printf("%d->", temp->data);
		temp = temp->link;
	}
	printf("\n");
}

//��ũ����Ʈ���� int x ã��
ListNode* search(ListNode* head, int x) {
	ListNode* p;
	p = head;

	while (p != NULL) {
		if (p->data == x)
			return p;
		p = p->link;
	}

	return NULL;
}

//��ũ����Ʈ �ΰ��� �����ϱ�
ListNode* concat(ListNode* head1, ListNode* head2) {
	ListNode* p = NULL;

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

//������
ListNode* reverse(ListNode* head) {
	ListNode* p, * q = NULL, * r = NULL;
	p = head;

	while (p != NULL) {
		r = q;
		q = p;
		p = p->link;
		q->link = r;
	}

	return q;
}

int is_in_list(ListNode* head, element item) {
	if (search(head, item) == NULL)
		return 0;
	return 1;
}

int get_length(ListNode* head) {
	int i; ListNode* p = head;
	for (i = 0; p != NULL; i++)
		p = p->link;

	return i;
}

int get_total(ListNode* head) {
	int add = 0; ListNode* p = head;

	while (p != NULL) {
		add += p->data;
		p = p->link;
	}

	return add;
}

element get_entry(ListNode* head, int pos) {
	ListNode* p = head;
	for (int i = 0; i < pos; i++) {
		if (p == NULL) {
			printf("pos���� �� ����Ʈ�������� Ů�ϴ�.\n");
			return 0;
		}
		p = p->link;
	}

	return p->data;
}

ListNode* delete_by_key(ListNode* head, int key) {
	ListNode* removed = head;
	ListNode* pre = NULL;
	while (removed != NULL) {
		if (removed->data == key) {
			pre->link = removed->link;
			free(removed);

			return head;
		}

		pre = removed;
		removed = removed->link;
	}

	printf("�ش��ϴ� key���� ����Ʈ�� �������� �ʽ��ϴ�.\n");
	return head;
}

ListNode* insert_pos(ListNode* head, int pos, element value) {
	if (pos < 0) {
		printf("pos���� �����Դϴ�.\n");
		return head;
	}

	ListNode* new = (ListNode*)malloc(sizeof(ListNode));
	new->data = value;

	ListNode* temp = head;
	ListNode* pre = NULL;
	for (int i = 0; i < pos; i++) {
		if (temp == NULL) {
			printf("pos���� �� ����Ʈ�������� Ů�ϴ�.\n");
			return head;
		}

		pre = temp;
		temp = temp->link;
	}

	pre->link = new;
	new->link = temp;

	return head;
}

ListNode* delete_pos(ListNode* head, int pos) {
	if (pos < 0) {
		printf("pos���� �����Դϴ�.\n");
		return head;
	}

	ListNode* temp = head;
	ListNode* pre = NULL;
	for (int i = 0; i < pos; i++) {
		if (temp == NULL) {
			printf("pos���� �� ����Ʈ�������� Ů�ϴ�.\n");
			return head;
		}

		pre = temp;
		temp = temp->link;
	}

	pre->link = temp->link;
	free(temp);

	return head;
}

int main(void) {
	ListNode* list1 = NULL, * list2 = NULL, * list3;

	//10, 20, 30�� ������� list1 �� ó���� ����
	list1 = insert_first(list1, 10);
	list1 = insert_first(list1, 20);
	list1 = insert_first(list1, 30);
	//���
	printf("list1 = ");
	print_list(list1);

	//�� �� ��� ����
	list1 = delete_first(list1);
	//���
	printf("list1 = ");
	print_list(list1);

	//11, 22, 33, 44�� ������� list2 �������� ����
	list2 = insert_last(list2, 11);
	list2 = insert_last(list2, 22);
	list2 = insert_last(list2, 33);
	list2 = insert_last(list2, 44);
	//���
	printf("list2 = ");
	print_list(list2);

	//�� �� ��� ����
	list2 = delete_last(list2);
	//���
	printf("list2 = ");
	print_list(list2);

	//list2�� ������ list3
	list3 = reverse(list2);
	//���
	printf("list3 = ");
	print_list(list3);

	//list1�� list3�� ����
	list1 = concat(list1, list3);
	//���
	printf("list1 = ");
	print_list(list1);

	//list1�� ������ üũ (A)
	//is_in_list
	element item;
	printf("ã�� ���� �����Ͱ�: ");
	scanf("%d", &item);

	if (is_in_list(list1, item))
		printf("%d�� list1 �ȿ� �ֽ��ϴ�\n", item);
	else
		printf("%d��(��) list1 �ȿ� �����ϴ�\n", item);

	//get_length
	printf("list1�� �� �����ͼ��� %d\n", get_length(list1));

	//get_total
	printf("list1�� �����Ͱ��� ���� %d\n", get_total(list1));

	//get_entry
	int index;
	element findData;
	printf("ã�� ���� �������� �ε�����: ");
	scanf("%d", &index);

	findData = get_entry(list1, index);
	if (findData != 0)
		printf("%d�� �����Ͱ��� %d\n", index, get_entry(list1, index));

	//delte_by_key
	int data_key;
	printf("�����ϰ� ���� �����Ͱ�: ");
	scanf("%d", &data_key);
	list1 = delete_by_key(list1, data_key);
	printf("������(key)���� %d�� ��带 ������ �� list1 = ", data_key);
	print_list(list1);

	//insert_pos
	int inPos, inData;
	printf("�����ϰ� ���� ��ġ(pos��)�� �����Ͱ�: ");
	scanf("%d %d", &inPos, &inData);
	list1 = insert_pos(list1, inPos, inData);
	printf("pos���� %d�� �� %d�� ������ �� list1 = ", inPos, inData);
	print_list(list1);

	//delete_pos
	int delPos;
	printf("�����ϰ� ���� �����Ͱ��� ��ġ(pos��): ");
	scanf("%d", &delPos);
	list1 = delete_pos(list1, delPos);
	printf("pos���� %d�� ��带 ������ �� list1 = ", delPos);
	print_list(list1);

	return 0;
}
*/