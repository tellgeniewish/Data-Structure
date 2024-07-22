#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
typedef struct TreeNode {
	int data;
	struct TreeNode* left, * right;
} TreeNode;

typedef TreeNode* element;
typedef struct StackNode {
	element data;
	struct StackNode* link;
} StackNode;

typedef struct {
	StackNode* top;
} LinkedStackType;

void init(LinkedStackType* s)// �������� ����.
{
	s->top = NULL;
}

int is_empty(LinkedStackType* s)// �������� ����.
{
	return (s->top == NULL);
}

// ��ȭ ���� ���� �Լ�
int is_full(LinkedStackType* s)// �������� ����.
{
	return 0;
}
// ���� �Լ�
void push(LinkedStackType* s, element item)// �������� ����.
{
	StackNode* temp = (StackNode*)malloc(sizeof(StackNode));
	temp->data = item;
	temp->link = s->top;
	s->top = temp;
}
// ���� �Լ�
element pop(LinkedStackType* s) // �������� ����.
{
	if (is_empty(s)) {
		fprintf(stderr, "������ �������\n");
		exit(1);
	}
	else {
		StackNode* temp = s->top;
		element data = temp->data;
		s->top = s->top->link;
		free(temp);
		return data;
	}
}

TreeNode* insert_node(TreeNode* root, int data)  // �������� ����. 
												 // ���� ����� �ʾ����� � ��Ģ���� Ʈ���� ��带 �����Ѵ�.
{
	TreeNode* p, * t; // p�� �θ���, t�� ������ 
	TreeNode* n;	    // n�� ���ο� ���

	t = root;
	p = NULL;

	// Ž���� ���� ����, �ݺ��� �̿��ؼ� search(���� search�Լ� ����)
	while (t != NULL) { // �����尡 NULL�� �ɶ�����
		if (data == t->data) return root;
		p = t; // �����带 �θ���� �ϰ�
			// �����带 ����
		if (data < t->data)
			t = t->left;
		else
			t = t->right;
	}
	// data�� Ʈ�� �ȿ� �����Ƿ� ���� ����
	n = (TreeNode*)malloc(sizeof(TreeNode));
	// ������ ����
	n->data = data;
	n->left = n->right = NULL;

	// �θ� ���� ��ũ ����
	if (p != NULL)
		if (data < p->data)
			p->left = n;
		else
			p->right = n;
	else // ���ʿ� Ʈ���� ����־�����
		root = n;
	return root;
}

void preorder_iter(LinkedStackType* s, TreeNode* root)
{
	// �ڵ� �ۼ�
	for (; root; root = root->left)
		push(s, root);
	for (; root; root = root->right)
		push(s, root);
	while (!is_empty(s)) {

		root = pop(s);
		printf("%d ", root->data);
		root = root->left;

		//for (; root; root = root->right)
		//	push(s, root);
	}
	while (!is_empty(s)) {

		root = pop(s);
		printf("%d ", root->data);
		root = root->right;
	}
}

int main(void)// �������� ����.
{
	LinkedStackType s;
	TreeNode* root;
	int n;

	// �Ʒ��� 6���� Ʈ���� ����� �κ����� �����ð��� �ٷ��� �ʾ����Ƿ� �Ű澲�� �ʾƵ� �ȴ�.
	root = NULL;
	scanf("%d", &n);
	while (n != -1) {
		root = insert_node(root, n);
		scanf("%d", &n);
	}

	init(&s);
	//printf("���� ��ȸ=");
	preorder_iter(&s, root);
	printf("\n");
	return 0;
}
