//����ȭ�а� 20211689 ������
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h> 
#include <stdlib.h> 
#include <memory.h> 

typedef struct TreeNode {
	int data;
	struct TreeNode* left, * right;
} TreeNode;
/*
#define SIZE 100
int top = -1;
TreeNode* stack[SIZE];
*/
typedef TreeNode* element;
typedef struct StackNode {
	element data;
	struct StackNode* link;
} StackNode;
typedef struct {
	StackNode* top;
} LinkedStackNode;
// 15
// 4 20
// 1 16 25
/*
TreeNode n1 = { 1, NULL, NULL };
TreeNode n2 = { 4, &n1, NULL };
TreeNode n3 = { 16, NULL, NULL };
TreeNode n4 = { 25, NULL, NULL };
TreeNode n5 = { 20, &n3, &n4 };
TreeNode n6 = { 15, &n2, &n5 };
TreeNode* root = &n6;
*/
void init(LinkedStackNode* s) // ���� �ʱ�ȭ �Լ� 
{
	s->top = NULL;
}
int is_empty(LinkedStackNode* s) // ���� ���� ���� �Լ� 
{
	return (s->top == NULL);
}
int is_full(LinkedStackNode* s) // ��ȭ ���� ���� �Լ� 
{
	return 0;
}
/*void push(LinkedStackNode* s) {
	if (top < SIZE - 1)
		stack[++top] = p;
}
TreeNode* pop()
{
	TreeNode* p = NULL;
	if (top >= 0)
		p = stack[top--];
	return p;
}*/

void push(LinkedStackNode* s, element item) // �����Լ� 
{
	StackNode* temp = (StackNode*)malloc(sizeof(StackNode));
	if (temp == NULL) {
		fprintf(stderr, "�޸� �Ҵ翡��\n");
		return;
	}
	else {
		temp->data = item;
		temp->link = s->top;
		s->top = temp;
	}
}
element pop(LinkedStackNode* s) // �����Լ� 
{
	if (is_empty(s)) {
		fprintf(stderr, "������ �������\n");
		exit(1);
	}
	else {
		StackNode* temp = s->top;
		element item = temp->data;
		s->top = s->top->link;
		free(temp);
		return item;
	}
}
void print_stack(LinkedStackNode* s) {
	if (is_empty(s)) {
		printf("<empty>\n--\n");
		return;
	}

	StackNode* p = s->top;
	for (p = s->top; p != NULL; p = p->link) {
		printf("%d", p->data);

		if (p == s->top)
			printf(" <- top");
		printf("\n");
	}
	printf("--\n");
}
/*void inorder_iter(TreeNode* root)
{
	while (1) {
		for (; root; root = root->left)
			push(root);
		root = pop();
		if (!root) break;
		printf("[%d] ", root->data);
		root = root->right;
	}
}*/
void inorder_iter(LinkedStackNode* s, TreeNode* root) {
	//init(&s);
	for (; root; root = root->left)
		push(s, root);
	while (!is_empty(s)) {
		root = pop(s);
		printf("[%d] ", root->data);
		root = root->right;

		for (; root; root = root->left)
			push(s, root);
	}
}
TreeNode* insert_node(TreeNode* root, int data) {
	if (root == NULL) {
		TreeNode* new_node = (TreeNode*)malloc(sizeof(TreeNode));
		if (new_node == NULL) {
			fprintf(stderr, "�޸� �Ҵ� ����\n");
			exit(1);
		}
		new_node->data = data;
		new_node->left = new_node->right = NULL;
		return new_node;
	}
	if (data < root->data)
		root->left = insert_node(root->left, data);
	else if (data > root->data)
		root->right = insert_node(root->right, data);
	return root;
}
int main(void)
{
	LinkedStackNode s;
	TreeNode* root;
	int n;

	// Ʈ���� ����� ���� �κ�: ���� �������� �ٷ����� ����
	root = NULL;
	scanf("%d", &n);
	while (n != -1) {
		root = insert_node(root, n);
		scanf("%d", &n);
	}
	init(&s);
	printf("���� ��ȸ=");
	inorder_iter(&s, root);
	printf("\n");
	return 0;
}