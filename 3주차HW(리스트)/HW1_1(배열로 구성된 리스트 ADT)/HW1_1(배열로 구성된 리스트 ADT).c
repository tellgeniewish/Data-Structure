//����ȭ�а� 20211689 ������
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h> 

#define MAX_LIST_SIZE 5 // ����Ʈ�� �ִ� ũ��
typedef int element; // �׸��� ����
typedef struct {
	element array[MAX_LIST_SIZE]; // �迭 ����
	int size; // ���� ����Ʈ�� ����� �׸���� ����
}ArrayListType;

void error(char* message) // ���� ó�� �Լ�
{
	fprintf(stderr, "%s\n", message);
	//exit(1);
}
void init(ArrayListType* L) // ����Ʈ �ʱ�ȭ �Լ�
{
	L->size = 0;
}
int is_empty(ArrayListType* L)
{
	return L->size == 0; // ����Ʈ�� ��� ������ 1�� ��ȯ / �׷��� ������ 0�� ��ȯ
}
int is_full(ArrayListType* L)
{
	return L->size == MAX_LIST_SIZE; // ����Ʈ�� ���� �� ������ 1�� ��ȯ / �׷��� ������ 0�� ��ȯ
}

void print_list(ArrayListType* L) // ����Ʈ ���
{
	for (int i = 0; i <= (L->size - 1); i++)
		printf("%d->", L->array[i]);
	printf("����Ʈ ��\n");
}

void insert(ArrayListType* L, int pos, element item)
{
	if (is_full(L)) {
		error("����Ʈ�� �����÷ο�");
		return;
	}

	if (!is_full(L) && (0 <= pos) && (pos <= L->size)) {
		for (int i = (L->size - 1); i >= pos; i--)
			L->array[i + 1] = L->array[i];
		L->array[pos] = item;
		L->size++;
	}
}
void insert_last(ArrayListType* L, element item)
{
	if (MAX_LIST_SIZE <= L->size) {
		error("����Ʈ�� �����÷ο�\n");
		return;
	}
	L->array[L->size++] = item;
}
element delete(ArrayListType* L, int pos)
{
	element item =  L->array[pos];

	if (pos < 0 || L->size <= pos) {
		error("��ġ ����");
		return;
	}

	for (int i = pos; i <= (L->size - 1); i++)
		L->array[i] = L->array[i + 1];
	L->size--;
	
	return item;
}
element get_entry(ArrayListType* L, int pos)
{
	if (pos < 0 || L->size <= pos) {
		error("��ġ ����");
		return;
	}
	return L->array[pos];
}

//���� �ۼ��ؾ� �� �Լ�
void clear(ArrayListType* L) // ����Ʈ�� ����
{
	L->size = 0;
}
void insert_first(ArrayListType* L, element item) // item �� ����Ʈ�� ù��° �׸� �߰��Ѵ�
{
	if (is_full(L)) {
		error("����Ʈ�� �����÷ο�");
		return;
	}
	else { // (!is_full(L)) {
		for (int i = (L->size - 1); i >= 0; i--)
			L->array[i + 1] = L->array[i];
		L->array[0] = item;
		L->size++;
	}
}
int get_length(ArrayListType* L) // ����Ʈ�� �׸���� ��ȯ�Ѵ�
{
	return L->size;
}
void replace(ArrayListType* L, int pos, element item) // pos ��° �׸��� item ���� �ٲ۴�
{
	L->array[pos] = item;
}
int is_in_list(ArrayListType* L, element item) // item �� ����Ʈ�� ������ 1 �� �ƴϸ� 0 �� ��ȯ
{
	for (int i = 0; i <= (L->size - 1); i++) {
		if (L->array[i] == item)
			return 1;
	}
	return 0;
}
void delete_by_key(ArrayListType* L, element key) // ����Ʈ���� key ���� �˻��Ͽ� �׸� �����Ѵ�.
{
	
	int i;
	for (i = 0; i < L->size; i++) {
		if (L->array[i] == key) {
			delete(L, i);
			break; // ���� ����key ���� �������� ù��° key ���� �����ϴ� ������ �Ѵ�. 
		}
	}

	if (i == L->size) // key ���� ���� ��� �����١��� ����Ѵ�.
		printf("�����Ϸ��� key�� %d�� ����Ʈ�� �����ϴ�\n", key);
	/**/
	
	/*for (int i = 0; i <= (L->size - 1); i++) {
		if (L->array[i] == key) {
			for (int j = i; j <= (L->size - 1); j++)
				L->array[j] = L->array[j + 1];
			L->size--;
			return; // ���� ����key ���� �������� ù��° key ���� �����ϴ� ������ �Ѵ�.
		}
	}
	printf("�����Ϸ��� key�� %d�� ����Ʈ�� �����ϴ�\n", key); // key ���� ���� ��� �����١��� ����Ѵ�.
	*/
}

int main(void)
{
	ArrayListType list1;

	init(&list1);
	insert(&list1, 0, 20);
	insert(&list1, 0, 10); print_list(&list1);
	clear(&list1); print_list(&list1);

	insert_last(&list1, 90); print_list(&list1);

	insert(&list1, 0, 30);
	insert(&list1, 0, 20);
	insert(&list1, 0, 10); print_list(&list1);

	delete(&list1, 2); print_list(&list1);
	//-----����
	
	//-----�߰�
	printf("\n-�� ���Ĵ� HW1_1���� �߰��� �Լ��� �׽�Ʈ-\n");
	insert_first(&list1, 9); print_list(&list1);
	insert_last(&list1, 99); print_list(&list1);

	// ���� ����Ʈ�� �� ��(ũ�� 5��) �����̹Ƿ� �� �׸��� �� �߰��ϸ� "����Ʈ �����÷ο�"�� ����Ѵ�. 
	insert_first(&list1, 1); print_list(&list1); 

	printf("���̴� %d\n", get_length(&list1));
	printf("3��° ����Ÿ�� %d\n", get_entry(&list1, 2));

	replace(&list1, 3, 40); print_list(&list1);
	printf("20�� ����Ʈ�� %s\n", is_in_list(&list1, 20) ? "�ֽ��ϴ�" : "�����ϴ�");
	printf("22�� ����Ʈ�� %s\n", is_in_list(&list1, 22) ? "�ֽ��ϴ�" : "�����ϴ�");

	delete_by_key(&list1, 20); print_list(&list1);
	delete_by_key(&list1, 22); print_list(&list1);
}