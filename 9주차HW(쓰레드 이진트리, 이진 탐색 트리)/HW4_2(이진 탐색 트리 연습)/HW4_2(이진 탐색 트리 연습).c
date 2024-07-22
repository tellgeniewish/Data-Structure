// ����ȭ�а� 20211689 ������
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <memory.h> 

// ����� ����
typedef struct {
	int key;
	struct TreeNode* left, * right;
} TreeNode;

void inorder(TreeNode* root) { // ���� ��ȸ //Ž��(��ȯ) & Ž��(�ݺ�)
	if (root) {
		inorder(root->left);// ���ʼ���Ʈ�� ��ȸ
		printf("[%d] ", root->key); // ��� �湮
		inorder(root->right);// �����ʼ���Ʈ�� ��ȸ
	}
}
TreeNode* new_node(int item)  //Ž��(��ȯ) & Ž��(�ݺ�)
{
	TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));
	temp->key = item;
	temp->left = temp->right = NULL;
	return temp;
}
TreeNode* insert_node(TreeNode* root, int key) //Ž��(��ȯ)
{
	// Ʈ���� �����̸� ���ο� ��带 ��ȯ�Ѵ�. 
	if (root == NULL) return new_node(key);
	// �׷��� ������ ��ȯ������ Ʈ���� ��������. 
	if (key < root->key)
		root->left = insert_node(root->left, key);
	else if (key > root->key)
		root->right = insert_node(root->right, key);
	// ����� ��Ʈ �����͸� ��ȯ�Ѵ�. 
	return root;
}

TreeNode* min_value_node(TreeNode* node) //Ž��(��ȯ)
{
	TreeNode* current = node;
	while (current->left != NULL) // �� ���� �ܸ� ��带 ã���� ������ 
		current = current->left;
	return current;
}
TreeNode* delete_node(TreeNode* root, int key) // ���� �Լ� //Ž��(��ȯ)
{
	TreeNode* temp;
	if (root == NULL) return root;
	// ���� Ű�� ��Ʈ���� ������ ���� ���� Ʈ���� �ִ� ����
	if (key < root->key)
		root->left = delete_node(root->left, key);
	// ���� Ű�� ��Ʈ���� ũ�� ������ ���� Ʈ���� �ִ� ����
	else if (key > root->key)
		root->right = delete_node(root->right, key);
	// Ű�� ��Ʈ�� ������ �� ��带 �����ϸ� ��
	else {
		// ù ��°�� �� ��° ���
		if (root->left == NULL) {
			TreeNode* temp = root->right;
			free(root);
			return temp;
		}
		else if (root->right == NULL) {
			TreeNode* temp = root->left;
			free(root);
			return temp;
		}
		// �� ��° ���
		temp = min_value_node(root->right);
		// �߿� ��ȸ�� �İ� ��带 �����Ѵ�. 
		root->key = temp->key;
		// �߿� ��ȸ�� �İ� ��带 �����Ѵ�. 
		root->right = delete_node(root->right, temp->key);
	}
	return root;
}

void search(TreeNode* node, int key) {
	if (node == NULL) {
		printf("����\n");
		return;
	}

	if (key == node->key) 
		printf("����\n");
	else if (key < node->key)
		return search(node->left, key);
	else
		return search(node->right, key);
}

int get_height(TreeNode* root) {
	int height = 0;
	if (root != NULL)
		height = 1 + max(get_height(root->left), get_height(root->right));
	return height;
}
int get_node_count(TreeNode* node)
{
	int count = 0;
	if (node != NULL)
		count = 1 + get_node_count(node->left) + get_node_count(node->right);
	return count;
}

int get_maximum(TreeNode* root) {
	TreeNode* p = root;
	while (p->right != NULL)
		p = p->right;
	return p->key;
}
int get_minimum(TreeNode* root) {
	TreeNode* p = root;
	while (p->left != NULL)
		p = p->left;
	return p->key;
}
void preorder(TreeNode* root) { // ���� Ž�� Ʈ�� ��� �Լ�
	if (root != NULL) {
		printf("%d ", root->key);
		preorder(root->left);
		preorder(root->right);
	}
}
void help()
{
	printf("Enter i<nsert>, d<elete>, s<earch>, p<rint>, h<eight>, c<ount>, m<ax>, n<min>, q<uit>:");
}
int main(void)
{
	char answer;
	int key;
	TreeNode* root = NULL;

	do
	{
		help();
		scanf("%c", &answer);
		while (getchar() != '\n');

		switch (answer) {
		case 'i':
			printf("������ key�� �Է� : ");
			scanf("%d", &key);
			root = insert_node(root, key);
			while (getchar() != '\n');
			break;
		case 'd':
			printf("������ key�� �Է� : ");
			scanf("%d", &key);
			root = delete_node(root, key);
			while (getchar() != '\n');
			break;
		case 's':
			printf("Ž���� key�� �Է� : ");
			scanf("%d", &key);
			search(root, key);
			while (getchar() != '\n');
			break;
		case 'p':
			preorder(root);
			printf("\n");
			break;
		case 'h':
			printf("Ʈ���� ���̴� %d\n", get_height(root));
			break;
		case 'c':
			printf("����� ������ %d\n", get_node_count(root));
			break;
		case 'm':
			printf("���� ū ���� %d\n", get_maximum(root));
			break;
		case 'n':
			printf("���� ���� ���� %d\n", get_minimum(root));
			break;
		}
	} while (answer != 'q');

	return 0;
}
/*int main(void)
{
	TreeNode* root = NULL;
	TreeNode* tmp = NULL;

	root = insert_node(root, 30);
	root = insert_node(root, 20);
	root = insert_node(root, 10);
	root = insert_node(root, 40);
	root = insert_node(root, 50);
	root = insert_node(root, 60);

	printf("���� Ž�� Ʈ�� ���� ��ȸ ���\n");
	inorder(root);
	printf("\n\n");

	if (search(root, 30) != NULL)
		printf("���� Ž�� Ʈ������ 30�� �߰���\n");
	else
		printf("���� Ž�� Ʈ������ 30�� �߰߸���\n");

	return 0;
}*/