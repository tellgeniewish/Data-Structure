//응용화학과 20211689 김현진
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_ELEMENT 200
typedef struct {
	int key;
} element;
typedef struct {
	element heap[MAX_ELEMENT];
	int heap_size;
} HeapType;
HeapType* create() // 생성 함수
{
	return (HeapType*)malloc(sizeof(HeapType));
}
void init(HeapType* h) // 초기화 함수
{
	h->heap_size = 0;
}
void insert_max_heap(HeapType* h, element item) // 삽입 함수
{
	// 현재 요소의 개수가 heap_size인 히프 h에 item을 삽입한다.
	int i;
	i = ++(h->heap_size);
	// 트리를 거슬러 올라가면서 부모 노드와 비교하는 과정
	while ((i != 1) && (item.key > h->heap[i / 2].key)) {
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i] = item; // 새로운 노드를 삽입
}
element delete_max_heap(HeapType* h) // 삭제 함수
{
	int parent, child;
	element item, temp;
	item = h->heap[1];
	temp = h->heap[(h->heap_size)--];
	parent = 1;
	child = 2;
	while (child <= h->heap_size) {
		// 현재 노드의 자식노드 중 더 작은 자식노드를 찾는다.
		if ((child < h->heap_size) && (h->heap[child].key) < h->heap[child + 1].key)
			child++;
		if (temp.key >= h->heap[child].key) 
			break;
		// 한 단계 아래로 이동
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;
	return item;
}
void print_sorted_value(HeapType a)
{
	/*
	Step4: print_sorted_value 함수 구현
	Heap 에 들어있는 값들을 내림차순으로 정렬하여 출력하는 함수를 작성하여 main 함수에서 호출해보라..
	힌트 : 교재 <프로그램 ____>의 heap_sort 함수를 참조하라.
	*/
	//printf("size %d\n", a.heap_size);
	int i;
	for (i = a.heap_size; i > 0; i--) {
		printf("%d ", delete_max_heap(&a).key);
	}
	/*HeapType* h;
	h = create();
	init(h);
	for (i = 1; i <= a.heap_size; i++) {
		insert_max_heap(h, a.heap[i]);
	}
	for (i = 1; i <= a.heap_size; i++) {
		a.heap[i] = delete_max_heap(h);
	}
	for (i = 1; i <= a.heap_size; i++) {
		printf("%d ", a.heap[i]);
	}
	free(h);*/
}
int find(HeapType* h, int root, int key)
{
	/*
	Step 3: find 함수 구현
	 Heap 트리 내에 주어진 key값을 포함하는 element를 찾아
	그 위치(index)를 반환하는 find 함수를 작성하여	main 함수에서 테스트해보라.
	Key 값이 없으면 0을 반환한다.
	순환적으로 작성하라.
	함수의 원형은 int find(HeapType * h, int root, int key);
	*/
	
	if (h->heap_size < root)
		return 0;
	if (key == h->heap[root].key)
		return root;
	else if (h->heap[root].key < key) // heap의 성질
		return 0;
	else // 2가지 의미: 두 개 중 하나를 선택하거나, 찾은 경우
		return max(find(h, root * 2, key), find(h, root * 2 + 1, key));
	/*if (root <= h->heap_size) {
		if (key == h->heap[root].key)
			return root;

		int left_child = find(h, root * 2, key);
		if (left_child != 0)
			return left_child;
		int right_child = find(h, root * 2 + 1, key);
		if (right_child != 0)
			return right_child;
	}
	return 0;*/
}
int find2(HeapType* h, int key)
{
	/*
	(try)최대 Heap을 레벨 순회 순서로 탐색하면서
	주어진 key 값을 포함하는 element를 찾아
	그 위치(index)를 반환하는 find2 함수를 작성하고 테스트해 보라.
	탐색 도중에 더 이상 탐색을 계속할 필요가 없을 때
	(즉, Heap에 key 값이 존재하지 않음이 확실할 때)
	탐색을 중단하도록 프로그램을 작성해야 한다.
	Heap에서 Key 값은 중복되지 않는다고 가정한다.
	함수의 원형은 int find2(HeapType* h, int key)
	*/

	/*
	10
	8 6
	5 4 3 2
	3

	9를 찾을 때, 8 6을 보고 멈추기
	7을 찾을 때, 8이 있기 때문에 다음 레벨로 가야 함
	->하나라도 큰 수가 있으면 다음 레벨로 가야 한다

	10
	8 6
	4 6 3 2
	3

	5를 찾을 때, flag 변수 사용!
	*/
	int s, i;
	for (s = 1; s <= h->heap_size; s *= 2) { // s = 1. 2. 4. 8...
		int flag = 0;
		for (i = s; i < s * 2 && i <= h->heap_size; i++) { // s = 4, i = 4, 5, 6, 7
			if (h->heap[i].key == key) {
				return i;
			}
			else if (key < h->heap[i].key) {
				flag = 1;
			}
		}
		if (flag == 0)
			break;
	}
	return 0;
}
modify_priority(HeapType* h, int oldKey, int newKey)
{
	/*
	Step5 : (try)modify_priority 함수 구현
	max Heap 과 두 개의 key 값(oldkey 와 newkey)이 주어졌을 때
	oldkey 를 갖고 있는 element 를 Heap 에서 찾아
	key 값을 newkey 로 변경하는 함수를 작성하라.
	함수가 수행된 다음에는 최대 Heap 의 조건을 만족해야 한다.
	Heap 에서 Key 값은 중복되지 않는다고 가정한다.
	힌트 : Heap 에서의 삽입과 삭제 알고리즘을 참조하라.
	*/
	/*
	10
	8 7
	6 5
	
	8->4 or 9
	*/

	int i, child;
	if (oldKey == newKey)
		return;
	i = find(h, 1, oldKey);
	if (i == 0)
		return; //fail to find oldkey
	h->heap[i].key = newKey;
	if (oldKey < newKey) { // level up
		while (i > 1 && h->heap[i].key > h->heap[i / 2].key) {
			int temp = h->heap[i].key;
			h->heap[i].key = h->heap[i / 2].key;
			h->heap[i / 2].key = temp;
			i /= 2;
		}
	}
	else { // newkey < oldkey: level down
		child = i * 2;
		while (child <= h->heap_size && newKey < h->heap[child].key) {
			int temp = h->heap[i].key;
			h->heap[i].key = h->heap[child].key;
			h->heap[child].key = temp;
			i = child;
		}
	}

	/*int index = find(h, 1, oldKey);
	if (index != 0) {
		h->heap[index].key = newKey;

		while (index > 1 && h->heap[index].key > h->heap[index / 2].key) {
			int temp = h->heap[index].key;
			h->heap[index].key = h->heap[index / 2].key;
			h->heap[index / 2].key = temp;
			index /= 2;
		}
	}*/
}
void preorder(HeapType* h, int root) // p271 코드 복사
{
	/*
	Step 2: preorder과 print_heap 함수 구현
	 전위 순회함수 preorder를 작성하여 main 함수에서 호출하여 자신의 추측과 일치하나 확인하라.
	(7장의 p271에 주어진 preorder함수는 링크로 구현된 이진트리에 대한 함수이므로 배열 구현을 위해서는 조금 변형해야한다.
	힌트: void preorder(HeapType * h, int root)로 구현한다.
	자식트리는 root * 2, root * 2 + 1로 표현함에 착안하라.)
	Step1처럼 원소가 삽입되었다면 출력 결과는 다음과 같다.
	39 15 5 9 30 10
	*/
	if (h->heap_size < root)
		return;
	else {
		printf("%d ", h->heap[root].key);
		preorder(h, root * 2);
		preorder(h, root * 2 + 1);
	}
	/*if (root <= h->heap_size) {
		printf("%d ", h->heap[root].key);
		preorder(h, root * 2);
		preorder(h, root * 2 + 1);
	}*/
}
void print_heap(HeapType* h)
{
	/*
	 print_heap(HeapType * h) 함수는 Heap h에 저장된 값들을 레벨 순회 순서로 출력하되,
	레벨 단위로	줄바꿈을 하여 출력하도록 한다.
	예를 들면 교재 p.____[그림 ____]의 Heap은 다음과 같이 출력되어야
	한다.
	39
	19 30
	5 9 10
	*/
	/*
	*/
	int s, i;
	for (s = 1; s <= h->heap_size; s *= 2) { // s = 1. 2. 4. 8...
		for (i = s; i < s * 2 && i <= h->heap_size; i++) { // s = 4, i = 4, 5, 6, 7
			printf("%d ", h->heap[i]);
		}
		printf("\n");
	}

	//for (int i = 1; i <= h->heap_size; i++)
	//	printf("i는 %d 값은 %d\n", i, h->heap[i].key);

	/*int level = 1;
	for (int i = 1; i <= h->heap_size; i++) {
		if (i == level) {
			if (i != 1) {
				//printf("현재 레벨은 %d\n", level);
				printf("\n");
			}
			level = level * 2;
		}

		printf("%d ", h->heap[i].key);
	}
	printf("\n");*/
}
int main(void)
{
	element e1 = { 10 }, e2 = { 5 }, e3 = { 30 }, eA = { 9 }, eB = { 19 }, eC = { 39 };
	element e4, e5, e6;
	int index;
	int key, oldKey, newKey;
	HeapType heap; // 히프 생성 

	init(&heap); // 초기화 

	/*
	Step 1:main 함수 변경
	주어진 main 함수를 아래와 같다.
	10, 5, 30, 9, 19, 39의 매 삽입마다 Heap의 모양이 어떻게 바뀌는지 그림으로 그려보라.
	<삭제>가 일어나면 Heap의 모양이 어떻게 바뀌는지 그림으로 그려보라.
	*/
	printf("Step1: 삽입된 10, 5, 30 에 추가적으로 9, 19, 39 를 <삽입> 한다");
	insert_max_heap(&heap, e1);
	insert_max_heap(&heap, e2);
	insert_max_heap(&heap, e3);
	insert_max_heap(&heap, eA);
	insert_max_heap(&heap, eB);
	insert_max_heap(&heap, eC);

	printf("\nStep2: preorder, print_heap 함수 테스트\n");
	preorder(&heap, 1);
	printf("\n\n");
	print_heap(&heap);


	e4 = delete_max_heap(&heap);
	printf("\n삭제: 루트가 삭제됨\n", e4.key);
	print_heap(&heap);

	printf("\nStep3: find 함수 테스트\n");
	printf("찾을 key 입력(-1 for exit):");
	scanf("%d", &key);
	while (key != -1) {
		if ((index = find(&heap, 1, key)) == 0)
		//if ((index = find2(&heap, key)) == 0)
			printf("%d 는 없음\n", key);
		else
			printf("%d 은 [%d]에 있음\n", key, index);
		printf("찾을 key 입력(-1 for exit):");
		scanf("%d", &key);
	}

	printf("\nStep4: print_sorted_value 함수 테스트\n");
	print_sorted_value(heap);

	printf("\nStep5: modify_priority 함수 테스트\n");
	printf("바꿀 key 입력(-1 for exit):");
	scanf("%d", &oldKey);
	while (oldKey != -1) {
		printf("새 key 입력:");
		scanf("%d", &newKey);
		modify_priority(&heap, oldKey, newKey);
		print_heap(&heap);
		printf("바꿀 key 입력(-1 for exit):");
		scanf("%d", &oldKey);
	}
}