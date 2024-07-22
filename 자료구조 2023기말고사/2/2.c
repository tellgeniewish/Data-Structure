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

// 만약 e1 < e2 이면 -1 반환
// 만약 e1 == e2 이면 0 반환
// 만약 e1 > e2 이면 1 반환
int compare(element e1, element e2)
{
	return strcmp(e1.word, e2.word);
}
// 이진 탐색 트리 출력 함수(inorder로 출력하므로 정렬되어 나열)
void display(TreeNode* p)
{
	if (p != NULL) {

		display(p->left);
		printf("%s %s\n", p->key.word, p->key.meaning);
		display(p->right);
	}
}
// 이진 탐색 트리 탐색 함수
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
	return p; 	// 탐색에 실패했을 경우 NULL 반환
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
	// 트리가 공백이면 새로운 노드를 반환한다. 
	if (node == NULL) return new_node(key);

	// 그렇지 않으면 순환적으로 트리를 내려간다. 
	if (compare(key, node->key) < 0)
		node->left = insert_node(node->left, key);
	else if (compare(key, node->key) > 0)
		node->right = insert_node(node->right, key);
	// 루트 포인터를 반환한다. 
	return node;
}

TreeNode* replaceMeaning(TreeNode* root, char* word, char* meaning) // 이 함수를 작성하라
{
	element e;
	strcpy(e.word, word);
	strcpy(e.meaning, meaning);
	TreeNode* node = root;
	// 트리가 공백이면 새로운 노드를 반환한다. 
	if (node == NULL) return new_node(e);

	if (compare(e, node->key) == 0)
		node->key = e;
	// 그렇지 않으면 순환적으로 트리를 내려간다. 
	if (compare(e, node->key) < 0)
		node->left = insert_node(node->left, e);
	else if (compare(e, node->key) > 0)
		node->right = insert_node(node->right, e);
	// 루트 포인터를 반환한다. 
	return node;
}

void help()
{
	printf("\n**** i: 삽입, s: 탐색, r: (대치) p: 출력, q: 종료 ****: ");
}
// 이진 탐색 트리를 사용하는 영어 사전 프로그램 
int main(void)
{
	char command;
	element e;
	TreeNode* root = NULL;
	TreeNode* tmp;
	char word[20], meaning[40];

	do {
		//help(); // 나중에 주석화
		command = getchar();
		getchar();		// 엔터키 제거: 버퍼를 비우는 효과
		switch (command) {
		case 'i':
			//printf("단어:"); // 나중에 주석화
			gets(e.word);
			//printf("의미:");// 나중에 주석화
			gets(e.meaning);
			root = insert_node(root, e);
			break;
		case 'p':
			display(root);
			//printf("\n");
			break;
		case 's':
			//printf("단어:"); // 나중에 주석화
			gets(e.word);
			tmp = search(root, e);
			if (tmp != NULL) {
				//printf("의미:");
				printf("%s\n", e.meaning);
			}
			break;
		case 'r': // 추가
			//printf("단어:"); // 나중에 주석화
			gets(word);
			//printf("의미:");// 나중에 주석화
			gets(meaning);
			root = replaceMeaning(root, word, meaning);
		}
	} while (command != 'q');
	return 0;
}