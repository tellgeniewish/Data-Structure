#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>

#define MAX_WORD_SIZE	 20
#define MAX_MEANING_SIZE 40

typedef struct {
	char word[MAX_WORD_SIZE];
	char meaning[MAX_MEANING_SIZE];
} element;

typedef struct TreeNode {
	element key;
	struct TreeNode* left, * right;
} TreeNode;

// ���� e1 < e2 �̸� -1 ��ȯ
// ���� e1 == e2 �̸� 0 ��ȯ
// ���� e1 > e2 �̸� 1 ��ȯ
int compare(element e1, element e2)
{
	return strcmp(e1.word, e2.word);
}
// ���� Ž�� Ʈ�� ��� �Լ�(inorder�� ����ϹǷ� ���ĵǾ� ����)
void display(TreeNode* p)
{
	if (p != NULL) {

		display(p->left);
		printf("%s %s\n", p->key.word, p->key.meaning);
		display(p->right);
	}
}
// ���� Ž�� Ʈ�� Ž�� �Լ�
TreeNode* search(TreeNode* root, element key)
{
	TreeNode* p = root;
	while (p != NULL) {
		if (compare(key, p->key) == 0)
			return p;
		else if (compare(key, p->key) < 0)
			p = p->left;
		else if (compare(key, p->key) > 0)
			p = p->right;
	}
	return p; 	// Ž���� �������� ��� NULL ��ȯ
}


TreeNode* new_node(element item)
{
	TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));
	temp->key = item;
	temp->left = temp->right = NULL;
	return temp;
}

TreeNode* insert_node(TreeNode* node, element key)
{
	// Ʈ���� �����̸� ���ο� ��带 ��ȯ�Ѵ�. 
	if (node == NULL) return new_node(key);

	// �׷��� ������ ��ȯ������ Ʈ���� ��������. 
	if (compare(key, node->key) < 0)
		node->left = insert_node(node->left, key);
	else if (compare(key, node->key) > 0)
		node->right = insert_node(node->right, key);
	// ��Ʈ �����͸� ��ȯ�Ѵ�. 
	return node;
}

TreeNode* replaceMeaning(TreeNode* root, char* word, char* meaning) // �� �Լ��� �ۼ��϶�
{
	element e;
	strcpy(e.word, word);
	strcpy(e.meaning, meaning);
	TreeNode* node = root;
	// Ʈ���� �����̸� ���ο� ��带 ��ȯ�Ѵ�. 
	if (node == NULL) return new_node(e);

	if (compare(e, node->key) == 0)
		node->key = e;
	// �׷��� ������ ��ȯ������ Ʈ���� ��������. 
	if (compare(e, node->key) < 0)
		node->left = insert_node(node->left, e);
	else if (compare(e, node->key) > 0)
		node->right = insert_node(node->right, e);
	// ��Ʈ �����͸� ��ȯ�Ѵ�. 
	return node;
}

void help()
{
	printf("\n**** i: ����, s: Ž��, r: (��ġ) p: ���, q: ���� ****: ");
}
// ���� Ž�� Ʈ���� ����ϴ� ���� ���� ���α׷� 
int main(void)
{
	char command;
	element e;
	TreeNode* root = NULL;
	TreeNode* tmp;
	char word[20], meaning[40];

	do {
		//help(); // ���߿� �ּ�ȭ
		command = getchar();
		getchar();		// ����Ű ����: ���۸� ���� ȿ��
		switch (command) {
		case 'i':
			//printf("�ܾ�:"); // ���߿� �ּ�ȭ
			gets(e.word);
			//printf("�ǹ�:");// ���߿� �ּ�ȭ
			gets(e.meaning);
			root = insert_node(root, e);
			break;
		case 'p':
			display(root);
			//printf("\n");
			break;
		case 's':
			//printf("�ܾ�:"); // ���߿� �ּ�ȭ
			gets(e.word);
			tmp = search(root, e);
			if (tmp != NULL) {
				//printf("�ǹ�:");
				printf("%s\n", e.meaning);
			}
			break;
		case 'r': // �߰�
			//printf("�ܾ�:"); // ���߿� �ּ�ȭ
			gets(word);
			//printf("�ǹ�:");// ���߿� �ּ�ȭ
			gets(meaning);
			root = replaceMeaning(root, word, meaning);
		}
	} while (command != 'q');
	return 0;
}