// 응용화학과 20211689 김현진
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <memory.h> 

/*#define MAX_WORD_SIZE 100
#define MAX_MEANING_SIZE 200
// 데이터 형식
typedef struct {
	char word[MAX_WORD_SIZE]; // 키필드
	char meaning[MAX_MEANING_SIZE];
} element;
// 노드의 구조
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

void inorder(TreeNode* root) { // 중위 순회 //탐색(순환) & 탐색(반복)
	if (root) {
		inorder(root->left);// 왼쪽서브트리 순회
		printf("----------------------\n");
		printf("학번: %d\n", root->data.id); // 노드 방문
		printf("이름: %s\n", root->data.name);
		printf("전화번호: %s\n", root->data.tel);
		printf("학과: %s\n", root->data.dept);
		inorder(root->right);// 오른쪽서브트리 순회
	}
}
TreeNode* new_node(element data)  //탐색(순환) & 탐색(반복)
{
	TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));
	temp->data = data;
	temp->left = temp->right = NULL;
	return temp;
}
TreeNode* insert_node(TreeNode* root, element data) //탐색(순환)
{
	// 트리가 공백이면 새로운 노드를 반환한다. 
	if (root == NULL) return new_node(data);
	// 그렇지 않으면 순환적으로 트리를 내려간다. 
	if (data.id < root->data.id)
		root->left = insert_node(root->left, data);
	else if (data.id > root->data.id)
		root->right = insert_node(root->right, data);
	// 변경된 루트 포인터를 반환한다. 
	return root;
}
/*TreeNode* insert_node(TreeNode* root, int key) // 탐색(반복)
{
	TreeNode* p, * t; // p는 부모노드, t는 현재노드
	TreeNode* n; // n은 새로운 노드
	t = root;
	p = NULL;
	// 탐색을 먼저 수행, 반복을 이용해서 search(위의 search함수 참조)
	while (t != NULL) { // 현재노드가 NULL이 될때까지
		if (key == t->key) return root;
		p = t; // 현재노드를 부모노드로 하고
	   // 현재노드를 전진
		if (key < t->key)
			t = t->left;
		else
			t = t->right;
	}
	// key가 트리 안에 없으므로 삽입 가능
	n = new_node(key);
	// 부모 노드와 링크 연결
	if (p != NULL)
		if (key < p->key)
			p->left = n;
		else
			p->right = n;
	else // 애초에 트리가 비어있었으면
		root = n;
	return root;
}*/

TreeNode* min_value_node(TreeNode* node) //탐색(순환)
{
	TreeNode* current = node;
	while (current->left != NULL) // 맨 왼쪽 단말 노드를 찾으러 내려감 
		current = current->left;
	return current;
}
TreeNode* delete_node(TreeNode* root, element data) // 삭제 함수 //탐색(순환)
{
	TreeNode* temp;
	if (root == NULL) return root;
	// 만약 키가 루트보다 작으면 왼쪽 서브 트리에 있는 것임
	if (data.id < root->data.id)
		root->left = delete_node(root->left, data);
	// 만약 키가 루트보다 크면 오른쪽 서브 트리에 있는 것임
	else if (data.id > root->data.id)
		root->right = delete_node(root->right, data);
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
		root->data.id = temp->data.id;
		// 중외 순회시 후계 노드를 삭제한다. 
		root->right = delete_node(root->right, temp->data);
	}
	return root;
}
/*TreeNode* delete_node(TreeNode* root, int key) // 삭제 함수 // 탐색(반복)
// 나중에 ROOT <-> *root로 바꿈
{
	TreeNode* p, * child, * succ, * succ_p, * t;
	// key를 갖는 노드 t를 탐색, p는 t의 부모노드
	p = NULL;
	t = root;
	// key를 갖는 노드 t를 탐색한다.
	while (t != NULL && t->key != key) {
		p = t; // 자식노드를 부모가
		t = (key < t->key) ? t->left : t->right; // 자식노드 전진
	}
	// 탐색이 종료된 시점에 t가 NULL이면 트리안에 key가 없음
	if (t == NULL) { // 탐색트리에 없는 키
		printf("key is not in the tree");
		return root;
	}
	// 첫번째 경우: 단말노드인 경우
	if ((t->left == NULL) && (t->right == NULL)) {
		if (p != NULL) {
			// 부모노드의 자식필드를 NULL로 만든다.
			if (p->left == t) // 삭제하려는 것이 왼쪽 노드이면
				p->left = NULL;
			else
				p->right = NULL;
		}
		else//p가 NULL이면(즉 단 하나의 단말 노드이고 이걸 삭제하려면) 루트 삭제
			root = NULL;
	}
	// 두번째 경우: 하나의 자식만 가지는 경우
	else if ((t->left == NULL) || (t->right == NULL)) {
		child = (t->left != NULL) ? t->left : t->right;
		if (p != NULL) {
			if (p->left == t) // 부모를 자식과 연결
				p->left = child;
			else p->right = child;
		}
		else // 만약 부모노드가 NULL이면 삭제되는 노드가 루트
			root = child;
		이진탐색(3 / 4)
			4 / 5(자료구조 9주차)
	} // 세번째 경우: 두개의 자식을 가지는 경우
	else {
		// 오른쪽 서브트리에서 후계자를 찾는다.
		succ_p = t;
		succ = t->right;
		// 후계자를 찾아서 계속 왼쪽으로 이동한다.
		while (succ->left != NULL) {
			succ_p = succ;
			succ = succ->left;
		}
		// 후속자의 부모와 자식을 연결
		if (succ_p->left == succ)
			succ_p->left = succ->right;
		else
			succ_p->right = succ->right;
		// 후속자가 가진 키값을 현재 노드에 복사
		t->key = succ->key;
		// 원래의 후속자 삭제
		t = succ;
	}
	free(t);
	return root;
}*/

void search(TreeNode* node, element data) {
	if (node == NULL) {
		printf("id가 %d인 학생은 없읍니다.\n", data.id);
		return;
	}

	if (data.id == node->data.id) {
		printf("----------------------\n");
		printf("학번: %d\n", node->data.id); // 노드 방문
		printf("이름: %s\n", node->data.name);
		printf("전화번호: %s\n", node->data.tel);
		printf("학과: %s\n", node->data.dept);
	}
	else if (data.id < node->data.id)
		return search(node->left, data);
	else
		return search(node->right, data);
}
/*TreeNode* search(TreeNode* node, int key) //탐색(순환)
{
	if (node == NULL) return NULL;
	if (key == node->key) return node;
	else if (key < node->key)
		return search(node->left, key);
	else
		return search(node->right, key);
}*/
/*TreeNode* search(TreeNode* node, int key) // 탐색(반복)
{
	while (node != NULL) {
		if (key == node->key) return node;
		else if (key < node->key)
			node = node->left;
		else
			node = node->right;
	}
	return NULL; //탐색에 실패했을 경우 NULL 반환
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

/*void display(TreeNode* p) { // 이진 탐색 트리 출력 함수
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
	//printf("\n**** i: 입력, d: 삭제, s: 탐색, p: 출력, q: 종료 ****:");
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
			printf("학번 입력 : ");
			scanf("%d", &data.id);
			printf("이름 입력 : ");
			scanf("%s", data.name);
			printf("전화번호 입력 : ");
			scanf("%s", data.tel);
			printf("학과 입력 : ");
			scanf("%s", data.dept);
			root = insert_node(root, data);
			while (getchar() != '\n');
			break;
		case 'd':
			printf("삭제할 학번 입력 : ");
			scanf("%d", &data.id);
			root = delete_node(root, data);
			while (getchar() != '\n');
			break;
		case 's':
			printf("탐색할 학번 입력 : ");
			scanf("%d", &data.id);
			search(root, data);
			while (getchar() != '\n');
			break;
		case 'p':
			printf("학생 정보 학번 순 출력\n");
			inorder(root);
			printf("\n");
			break;
		case 'c':
			printf("현재 저장된 학생의 총 수는 %d\n", get_node_count(root));
			break;
		}
	} while (answer != 'q');

	return 0;
}
/*// 이진 탐색 트리를 사용하는 영어 사전 프로그램
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
		getchar(); // 엔터키 제거
		switch(answer) {
			case 'i':
				printf("단어:");
				gets_s(e.word, MAX_WORD_SIZE);
				printf("의미:");
				gets_s(e.meaning, MAX_MEANING_SIZE);
				root = insert_node(root, e);
				break;
			case 'd':
				printf("단어:");
				gets_s(e.word, MAX_WORD_SIZE);
				root = delete_node(root, e);
				break;
			case 'p':
				display(root);
				printf("\n");
				break;
			case 's':
				printf("단어:");
				gets_s(e.word, MAX_WORD_SIZE);
				tmp = search(root, e);
				if (tmp != NULL)
					printf("의미:%s\n", e.meaning);
				break;
		}
	} while (answer != 'q');

	return 0;
}*/