//응용화학과 20211689 김현진
#include <stdio.h> 
#include <stdlib.h> 
#include <memory.h> 
#define TRUE 1 
#define FALSE 0 
#define MAX_TREE_SIZE 20 

typedef struct TreeNode {
	int data;
	struct TreeNode* left, * right;
} TreeNode;
//	 root 				   	root2
//    15	 				  15
//  4	 15					4	 15
// 15	16 25			15		16 25
//									 28

TreeNode n1 = { 15, NULL, NULL };
TreeNode n2 = { 4, &n1, NULL };
TreeNode n3 = { 16, NULL, NULL };
TreeNode n4 = { 25, NULL, NULL };
TreeNode n5 = { 15, &n3, &n4 };
TreeNode n6 = { 15, &n2, &n5 };
TreeNode* root = &n6;

TreeNode m1 = { 15, NULL, NULL };
TreeNode m2 = { 4, &n1, NULL };
TreeNode m3 = { 16, NULL, NULL };
TreeNode m7 = { 28, NULL, NULL }; // 추가
TreeNode m4 = { 25, NULL, &m7 }; // 변경
TreeNode m5 = { 15, &m3, &m4 };
TreeNode m6 = { 15, &m2, &m5 };
TreeNode* root2 = &m6;

int get_node_count(TreeNode* node)
{
	int count = 0;
	if (node != NULL)
		count = 1 + get_node_count(node->left) + get_node_count(node->right);
	return count;
}
int get_leaf_count(TreeNode* node)
{
	int count = 0;
	if (node != NULL) {
		if (node->left == NULL && node->right == NULL)
			return 1;
		else
			count = get_leaf_count(node->left) + get_leaf_count(node->right);
	}
	return count;
}
//p281 Quiz 01 
int get_nonleaf_count(TreeNode* t)
{ 
	//printf("전체 노드 개수: %d\n", get_node_count(t));
	//printf("leaf 노드 개수: %d\n", get_leaf_count(t));
	return get_node_count(t) - get_leaf_count(t);
}
//p281 Quiz 02 
int equal(TreeNode* t1, TreeNode* t2)
{ 
	/*
	if (t1, t2가 NULL)
		return 1;
	else if (t1 == NULL || t2 == NULL) {
		return 0;
	}
	else if (t1->data != t2->data)
		return 0;
	else
		return L && R;
	*/

	if (t1 == NULL && t2 == NULL) {  // 두 개의 이진 트리가 같은 구조를 가지고 있고
		return 1; // 참이면 1
	}
	if (t1 == NULL || t2 == NULL) {
		return 0;
	}
	if (t1->data != t2->data) { // 대응되는 노드들이 같은 데이터를 가지고 있는지를 검사
		return 0; // 거짓이면 0을 반환
	}
	
	return equal(t1->left, t2->left) && equal(t1->right, t2->right);
}
//p308 #25 
int get_oneleaf_count(TreeNode* node) // 이진 트리에서 자식이 하나인 노드의 개수를 반환
{
	/*
	if (node == NULL) {
		return 0;
	}
	else if (node->left==NULL && node->right == NULL) {
		return 0;
	}
	else if (node->left==NULL && node->right != NULL) {
		return 1 + R;
	}
	else if {
		return 1 + L;
	}
	else
		return L + R + 1;
	*/
	if (node == NULL) {
		return 0;
	}

	int count = 0;
	if (node->left == NULL && node->right != NULL) {
		return 1;
	}
	if (node->left != NULL && node->right == NULL) {
		return 1;
	}
	count += get_oneleaf_count(node->left);
	count += get_oneleaf_count(node->right);

	return count;
}
/*int get_oneleaf_count(TreeNode* node) {

	int count = 0;

	if (node != NULL)
		if (node->right == NULL && node->left == NULL)
			return 0;

		else {
			if (node->right != NULL || node->left != NULL) {
				if (node->right == NULL || node->left == NULL)
					count = get_oneleaf_count(node->left) + get_oneleaf_count(node->right) + 1;
				else
					count = get_oneleaf_count(node->left) + get_oneleaf_count(node->right);
			}
		}
	return count;
}
int get_twoleaf_count(TreeNode* node) {

	int count = 0;

	if (node != NULL) {
		if (node->right == NULL && node->left == NULL)
			return 0;

		else {
			if (node->right != NULL && node->left != NULL)
				count = get_twoleaf_count(node->left) + get_twoleaf_count(node->right) + 1;
		}
	}

	return count;
}*/

//p308 #26 
int get_twoleaf_count(TreeNode* node) // 이진 트리에서 자식이 둘인 노드의 개수를 반환
{ 
	if (node == NULL) {
		return 0;
	}

	int count = 0;
	if (node->left != NULL && node->right != NULL) {
		count = 1;
	}

	count += get_twoleaf_count(node->left);
	count += get_twoleaf_count(node->right);

	return count;
}
//p308 #27 
int get_max(TreeNode* node) //이진 트리에서 노드값들 중 최대값을 반환
{
	/*if (node) {
		return max(max(node->data, get_max(node->left), get_max(node->right);
	}
	else
			return INT_MIN;
	*/
	if (node == NULL)
		return INT_MIN;
	
	int max = node->data;

	int left_max = get_max(node->left);
	int right_max = get_max(node->right);
	if (max < left_max) {
		max = left_max;
	}
	if (max < right_max) {
		max = right_max;
	}
	return max;
}

int get_min(TreeNode* node) // 이진 트리에서 노드값들 중 최소값을 반환
{ 
	/*if (node) {
		return min(max(node->data, get_min(node->left), get_max(node->right);
	}
	else
			return INT_MAX;
	*/
	if (node == NULL)
		return INT_MAX;

	int min = node->data;

	int left_min = get_min(node->left);
	int right_min = get_min(node->right);
	if (left_min < min) {
		min = left_min;
	}
	if (right_min < min) {
		min = right_min;
	}
	return min;
}
//p308 #30 
void node_increase(TreeNode* node) // 이진 트리의 노드들의 값을 1씩 증가
{
	/*
	if (node == NULL) {
		return;
	}
	else {
		node->data++;
		L;
		R;
	}
	*/
	if (node == NULL) {
		return;
	}
	node->data = node->data + 1;

	node_increase(node->left);
	node_increase(node->right);
}
void preorder(TreeNode* root) // p271 코드 복사
{
	if (root != NULL) {
		printf("[%d] ", root->data);
		preorder(root->left);
		preorder(root->right);
	}
}
void inorder(TreeNode* root) {
	if (root != NULL) {
		inorder(root->left);
		printf("[%d] ", root->data);
		inorder(root->right);
	}
}
void postorder(TreeNode* root) {
	if (root != NULL) {
		postorder(root->left);
		postorder(root->right);
		printf("[%d] ", root->data);
	}
}
int search(TreeNode* root, int key, TreeNode* result[]) { // 이진 트리에서 주어진 key 값을 갖는
//노드들을 모두 찾아 그것들의 주소값을 result 배열에 저장하고 해당 노드의 갯수를 반환
	if (root == NULL) {
		return 0;
	}

	int count = 0;
	if (root->data == key) { // 이진 트리에서 주어진 key 값을 갖는 노드들을 모두 찾아
		result[count] = root; // 그것들의 주소값을 result 배열에 저장하고
		count++;
	}
	count += search(root->left, key, &result[count]);
	count += search(root->right, key, &result[count]);

	return count; // 해당 노드의 갯수를 반환
}/**/
TreeNode* copy(TreeNode* node)
{
	if (node == NULL)
		return NULL;
	else {
		TreeNode* clone = (TreeNode*)malloc(sizeof(TreeNode));

		clone->data = node->data;
		clone->left = copy(node->left);
		clone->right = copy(node->right);
		return clone;
	}
}
int main(void)
{
	TreeNode* result[MAX_TREE_SIZE];
	TreeNode* clone;
	int i, num;

	printf("가)\n");
	printf("트리 root 중 비단말노드의 개수는 %d.\n", get_nonleaf_count(root));
	printf("트리 root2 중 비단말노드의 개수는 %d.\n", get_nonleaf_count(root2));
	
	printf("트리 root 중 자식이 하나만 있는 노드의 개수는 %d.\n", get_oneleaf_count(root));
	printf("트리 root2 중 자식이 하나만 있는 노드의 개수는 %d.\n", get_oneleaf_count(root2));
	
	printf("트리 root 중 자식이 둘이 있는 노드의 개수는 %d.\n", get_twoleaf_count(root));
	printf("트리 root2 중 자식이 둘이 있는 노드의 개수는 %d.\n", get_twoleaf_count(root2));
	/**/
	printf("트리 root 에서 가장 큰 수는 %d.\n", get_max(root));
	printf("트리 root2 에서 가장 큰 수는 %d.\n", get_max(root2));
	printf("트리 root 에서 가장 작은 수는 %d.\n", get_min(root));
	printf("트리 root2 에서 가장 작은 수는 %d.\n", get_min(root2));
	
	printf("\n 나)\n");
	num = search(root, 15, result);
	for (i = 0; i < num; i++)
		printf("(0x%p, %d), ", result[i], result[i]->data);
	printf("\n");/**/
	
	printf("\n 다)\n");
	preorder(root);
	node_increase(root);
	printf("\n");
	preorder(root);
	printf("\n");
	printf("%s\n", equal(root, root) ? "같다" : "다르다");
	printf("%s\n", equal(root2, root2) ? "같다" : "다르다");
	printf("%s\n", equal(root, root2) ? "같다" : "다르다");
	
	printf("\n 라)\n");
	clone = copy(root);
	preorder(root);
	printf("\n");
	preorder(clone);
	printf("\n");/**/
}