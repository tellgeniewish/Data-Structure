// ����ȭ�а� 20211689 ������
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <memory.h> 

/*#define MAX_WORD_SIZE 100
#define MAX_MEANING_SIZE 200
// ������ ����
typedef struct {
	char word[MAX_WORD_SIZE]; // Ű�ʵ�
	char meaning[MAX_MEANING_SIZE];
} element;
// ����� ����
typedef struct {
	element key, name, phoneNumber, major;
	struct TreeNode* left, * right;
} TreeNode;*/
#define MAX_STRING 100 
typedef struct {
	int id;
	char name[MAX_STRING];
	char tel[MAX_STRING];
	char dept[MAX_STRING];
} element;
typedef struct TreeNode {
	element data;
	struct TreeNode* left, * right;
} TreeNode;

void inorder(TreeNode* root) { // ���� ��ȸ //Ž��(��ȯ) & Ž��(�ݺ�)
	if (root) {
		inorder(root->left);// ���ʼ���Ʈ�� ��ȸ
		printf("----------------------\n");
		printf("�й�: %d\n", root->data.id); // ��� �湮
		printf("�̸�: %s\n", root->data.name);
		printf("��ȭ��ȣ: %s\n", root->data.tel);
		printf("�а�: %s\n", root->data.dept);
		inorder(root->right);// �����ʼ���Ʈ�� ��ȸ
	}
}
TreeNode* new_node(element data)  //Ž��(��ȯ) & Ž��(�ݺ�)
{
	TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));
	temp->data = data;
	temp->left = temp->right = NULL;
	return temp;
}
TreeNode* insert_node(TreeNode* root, element data) //Ž��(��ȯ)
{
	// Ʈ���� �����̸� ���ο� ��带 ��ȯ�Ѵ�. 
	if (root == NULL) return new_node(data);
	// �׷��� ������ ��ȯ������ Ʈ���� ��������. 
	if (data.id < root->data.id)
		root->left = insert_node(root->left, data);
	else if (data.id > root->data.id)
		root->right = insert_node(root->right, data);
	// ����� ��Ʈ �����͸� ��ȯ�Ѵ�. 
	return root;
}
/*TreeNode* insert_node(TreeNode* root, int key) // Ž��(�ݺ�)
{
	TreeNode* p, * t; // p�� �θ���, t�� ������
	TreeNode* n; // n�� ���ο� ���
	t = root;
	p = NULL;
	// Ž���� ���� ����, �ݺ��� �̿��ؼ� search(���� search�Լ� ����)
	while (t != NULL) { // �����尡 NULL�� �ɶ�����
		if (key == t->key) return root;
		p = t; // �����带 �θ���� �ϰ�
	   // �����带 ����
		if (key < t->key)
			t = t->left;
		else
			t = t->right;
	}
	// key�� Ʈ�� �ȿ� �����Ƿ� ���� ����
	n = new_node(key);
	// �θ� ���� ��ũ ����
	if (p != NULL)
		if (key < p->key)
			p->left = n;
		else
			p->right = n;
	else // ���ʿ� Ʈ���� ����־�����
		root = n;
	return root;
}*/

TreeNode* min_value_node(TreeNode* node) //Ž��(��ȯ)
{
	TreeNode* current = node;
	while (current->left != NULL) // �� ���� �ܸ� ��带 ã���� ������ 
		current = current->left;
	return current;
}
TreeNode* delete_node(TreeNode* root, element data) // ���� �Լ� //Ž��(��ȯ)
{
	TreeNode* temp;
	if (root == NULL) return root;
	// ���� Ű�� ��Ʈ���� ������ ���� ���� Ʈ���� �ִ� ����
	if (data.id < root->data.id)
		root->left = delete_node(root->left, data);
	// ���� Ű�� ��Ʈ���� ũ�� ������ ���� Ʈ���� �ִ� ����
	else if (data.id > root->data.id)
		root->right = delete_node(root->right, data);
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
		root->data.id = temp->data.id;
		// �߿� ��ȸ�� �İ� ��带 �����Ѵ�. 
		root->right = delete_node(root->right, temp->data);
	}
	return root;
}
/*TreeNode* delete_node(TreeNode* root, int key) // ���� �Լ� // Ž��(�ݺ�)
// ���߿� ROOT <-> *root�� �ٲ�
{
	TreeNode* p, * child, * succ, * succ_p, * t;
	// key�� ���� ��� t�� Ž��, p�� t�� �θ���
	p = NULL;
	t = root;
	// key�� ���� ��� t�� Ž���Ѵ�.
	while (t != NULL && t->key != key) {
		p = t; // �ڽĳ�带 �θ�
		t = (key < t->key) ? t->left : t->right; // �ڽĳ�� ����
	}
	// Ž���� ����� ������ t�� NULL�̸� Ʈ���ȿ� key�� ����
	if (t == NULL) { // Ž��Ʈ���� ���� Ű
		printf("key is not in the tree");
		return root;
	}
	// ù��° ���: �ܸ������ ���
	if ((t->left == NULL) && (t->right == NULL)) {
		if (p != NULL) {
			// �θ����� �ڽ��ʵ带 NULL�� �����.
			if (p->left == t) // �����Ϸ��� ���� ���� ����̸�
				p->left = NULL;
			else
				p->right = NULL;
		}
		else//p�� NULL�̸�(�� �� �ϳ��� �ܸ� ����̰� �̰� �����Ϸ���) ��Ʈ ����
			root = NULL;
	}
	// �ι�° ���: �ϳ��� �ڽĸ� ������ ���
	else if ((t->left == NULL) || (t->right == NULL)) {
		child = (t->left != NULL) ? t->left : t->right;
		if (p != NULL) {
			if (p->left == t) // �θ� �ڽİ� ����
				p->left = child;
			else p->right = child;
		}
		else // ���� �θ��尡 NULL�̸� �����Ǵ� ��尡 ��Ʈ
			root = child;
		����Ž��(3 / 4)
			4 / 5(�ڷᱸ�� 9����)
	} // ����° ���: �ΰ��� �ڽ��� ������ ���
	else {
		// ������ ����Ʈ������ �İ��ڸ� ã�´�.
		succ_p = t;
		succ = t->right;
		// �İ��ڸ� ã�Ƽ� ��� �������� �̵��Ѵ�.
		while (succ->left != NULL) {
			succ_p = succ;
			succ = succ->left;
		}
		// �ļ����� �θ�� �ڽ��� ����
		if (succ_p->left == succ)
			succ_p->left = succ->right;
		else
			succ_p->right = succ->right;
		// �ļ��ڰ� ���� Ű���� ���� ��忡 ����
		t->key = succ->key;
		// ������ �ļ��� ����
		t = succ;
	}
	free(t);
	return root;
}*/

void search(TreeNode* node, element data) {
	if (node == NULL) {
		printf("id�� %d�� �л��� �����ϴ�.\n", data.id);
		return;
	}

	if (data.id == node->data.id) {
		printf("----------------------\n");
		printf("�й�: %d\n", node->data.id); // ��� �湮
		printf("�̸�: %s\n", node->data.name);
		printf("��ȭ��ȣ: %s\n", node->data.tel);
		printf("�а�: %s\n", node->data.dept);
	}
	else if (data.id < node->data.id)
		return search(node->left, data);
	else
		return search(node->right, data);
}
/*TreeNode* search(TreeNode* node, int key) //Ž��(��ȯ)
{
	if (node == NULL) return NULL;
	if (key == node->key) return node;
	else if (key < node->key)
		return search(node->left, key);
	else
		return search(node->right, key);
}*/
/*TreeNode* search(TreeNode* node, int key) // Ž��(�ݺ�)
{
	while (node != NULL) {
		if (key == node->key) return node;
		else if (key < node->key)
			node = node->left;
		else
			node = node->right;
	}
	return NULL; //Ž���� �������� ��� NULL ��ȯ
}*/

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

/*void display(TreeNode* p) { // ���� Ž�� Ʈ�� ��� �Լ�
	if (p != NULL) {
		printf("(");
		display(p->left);
		printf("%s:%s", p->key.word, p->key.meaning);
		display(p->right);
		printf(")");
	}
}*/
void help()
{
	//printf("\n**** i: �Է�, d: ����, s: Ž��, p: ���, q: ���� ****:");
	printf("Enter i<nsert>, d<elete>, s<earch>, p<rint>, c<ount>, q<uit>:");
}
int main(void)
{
	char answer;
	element data;
	TreeNode* root = NULL;

	do
	{
		help();
		scanf("%c", &answer);
		while (getchar() != '\n');

		switch (answer) {
		case 'i':
			printf("�й� �Է� : ");
			scanf("%d", &data.id);
			printf("�̸� �Է� : ");
			scanf("%s", data.name);
			printf("��ȭ��ȣ �Է� : ");
			scanf("%s", data.tel);
			printf("�а� �Է� : ");
			scanf("%s", data.dept);
			root = insert_node(root, data);
			while (getchar() != '\n');
			break;
		case 'd':
			printf("������ �й� �Է� : ");
			scanf("%d", &data.id);
			root = delete_node(root, data);
			while (getchar() != '\n');
			break;
		case 's':
			printf("Ž���� �й� �Է� : ");
			scanf("%d", &data.id);
			search(root, data);
			while (getchar() != '\n');
			break;
		case 'p':
			printf("�л� ���� �й� �� ���\n");
			inorder(root);
			printf("\n");
			break;
		case 'c':
			printf("���� ����� �л��� �� ���� %d\n", get_node_count(root));
			break;
		}
	} while (answer != 'q');

	return 0;
}
/*// ���� Ž�� Ʈ���� ����ϴ� ���� ���� ���α׷�
int main(void)
{
	char answer;
	element e;
	TreeNode* root = NULL;
	TreeNode* tmp;

	do
	{
		help();
		answer = getchar();
		getchar(); // ����Ű ����
		switch(answer) {
			case 'i':
				printf("�ܾ�:");
				gets_s(e.word, MAX_WORD_SIZE);
				printf("�ǹ�:");
				gets_s(e.meaning, MAX_MEANING_SIZE);
				root = insert_node(root, e);
				break;
			case 'd':
				printf("�ܾ�:");
				gets_s(e.word, MAX_WORD_SIZE);
				root = delete_node(root, e);
				break;
			case 'p':
				display(root);
				printf("\n");
				break;
			case 's':
				printf("�ܾ�:");
				gets_s(e.word, MAX_WORD_SIZE);
				tmp = search(root, e);
				if (tmp != NULL)
					printf("�ǹ�:%s\n", e.meaning);
				break;
		}
	} while (answer != 'q');

	return 0;
}*/