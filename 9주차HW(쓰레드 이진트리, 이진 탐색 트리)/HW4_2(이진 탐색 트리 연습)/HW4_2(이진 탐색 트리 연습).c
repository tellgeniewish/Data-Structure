// 응용화학과 20211689 김현진
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <memory.h> 

// 노드의 구조
typedef struct {
	int key;
	struct TreeNode* left, * right;
} TreeNode;

void inorder(TreeNode* root) { // 중위 순회 //탐색(순환) & 탐색(반복)
	if (root) {
		inorder(root->left);// 왼쪽서브트리 순회
		printf("[%d] ", root->key); // 노드 방문
		inorder(root->right);// 오른쪽서브트리 순회
	}
}
TreeNode* new_node(int item)  //탐색(순환) & 탐색(반복)
{
	TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));
	temp->key = item;
	temp->left = temp->right = NULL;
	return temp;
}
TreeNode* insert_node(TreeNode* root, int key) //탐색(순환)
{
	// 트리가 공백이면 새로운 노드를 반환한다. 
	if (root == NULL) return new_node(key);
	// 그렇지 않으면 순환적으로 트리를 내려간다. 
	if (key < root->key)
		root->left = insert_node(root->left, key);
	else if (key > root->key)
		root->right = insert_node(root->right, key);
	// 변경된 루트 포인터를 반환한다. 
	return root;
}

TreeNode* min_value_node(TreeNode* node) //탐색(순환)
{
	TreeNode* current = node;
	while (current->left != NULL) // 맨 왼쪽 단말 노드를 찾으러 내려감 
		current = current->left;
	return current;
}
TreeNode* delete_node(TreeNode* root, int key) // 삭제 함수 //탐색(순환)
{
	TreeNode* temp;
	if (root == NULL) return root;
	// 만약 키가 루트보다 작으면 왼쪽 서브 트리에 있는 것임
	if (key < root->key)
		root->left = delete_node(root->left, key);
	// 만약 키가 루트보다 크면 오른쪽 서브 트리에 있는 것임
	else if (key > root->key)
		root->right = delete_node(root->right, key);
	// 키가 루트와 같으면 이 노드를 삭제하면 됨
	else {
		// 첫 번째나 두 번째 경우
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
		// 세 번째 경우
		temp = min_value_node(root->right);
		// 중외 순회시 후계 노드를 복사한다. 
		root->key = temp->key;
		// 중외 순회시 후계 노드를 삭제한다. 
		root->right = delete_node(root->right, temp->key);
	}
	return root;
}

void search(TreeNode* node, int key) {
	if (node == NULL) {
		printf("없음\n");
		return;
	}

	if (key == node->key) 
		printf("있음\n");
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
void preorder(TreeNode* root) { // 이진 탐색 트리 출력 함수
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
			printf("삽입할 key값 입력 : ");
			scanf("%d", &key);
			root = insert_node(root, key);
			while (getchar() != '\n');
			break;
		case 'd':
			printf("삭제할 key값 입력 : ");
			scanf("%d", &key);
			root = delete_node(root, key);
			while (getchar() != '\n');
			break;
		case 's':
			printf("탐색할 key값 입력 : ");
			scanf("%d", &key);
			search(root, key);
			while (getchar() != '\n');
			break;
		case 'p':
			preorder(root);
			printf("\n");
			break;
		case 'h':
			printf("트리의 높이는 %d\n", get_height(root));
			break;
		case 'c':
			printf("노드의 개수는 %d\n", get_node_count(root));
			break;
		case 'm':
			printf("가장 큰 값은 %d\n", get_maximum(root));
			break;
		case 'n':
			printf("가장 작은 값은 %d\n", get_minimum(root));
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

	printf("이진 탐색 트리 중위 순회 결과\n");
	inorder(root);
	printf("\n\n");

	if (search(root, 30) != NULL)
		printf("이진 탐색 트리에서 30을 발견함\n");
	else
		printf("이진 탐색 트리에서 30을 발견못함\n");

	return 0;
}*/