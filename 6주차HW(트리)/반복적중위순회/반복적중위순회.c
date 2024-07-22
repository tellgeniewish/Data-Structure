//응용화학과 20211689 김현진
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
void init(LinkedStackNode* s) // 스택 초기화 함수 
{
	s->top = NULL;
}
int is_empty(LinkedStackNode* s) // 공백 상태 검출 함수 
{
	return (s->top == NULL);
}
int is_full(LinkedStackNode* s) // 포화 상태 검출 함수 
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

void push(LinkedStackNode* s, element item) // 삽입함수 
{
	StackNode* temp = (StackNode*)malloc(sizeof(StackNode));
	if (temp == NULL) {
		fprintf(stderr, "메모리 할당에러\n");
		return;
	}
	else {
		temp->data = item;
		temp->link = s->top;
		s->top = temp;
	}
}
element pop(LinkedStackNode* s) // 삭제함수 
{
	if (is_empty(s)) {
		fprintf(stderr, "스택이 비어있음\n");
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
			fprintf(stderr, "메모리 할당 에러\n");
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

	// 트리를 만들기 위한 부분: 아직 수업에서 다루지는 않음
	root = NULL;
	scanf("%d", &n);
	while (n != -1) {
		root = insert_node(root, n);
		scanf("%d", &n);
	}
	init(&s);
	printf("중위 순회=");
	inorder_iter(&s, root);
	printf("\n");
	return 0;
}