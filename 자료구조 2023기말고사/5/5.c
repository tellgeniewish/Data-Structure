#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 50

typedef struct GraphNode
{
	int vertex;
	struct GraphNode* link;
} GraphNode;

typedef struct GraphType {
	int n;	// 정점의 개수
	GraphNode* adj_list[MAX_VERTICES];
} GraphType;

// 그래프 초기화 
void graph_init(GraphType* g)
{
	int v;
	g->n = 0;
	for (v = 0; v < MAX_VERTICES; v++)
		g->adj_list[v] = NULL;
}
// 정점 삽입 연산
void insert_vertex(GraphType* g, int v)
{
	if (((g->n) + 1) > MAX_VERTICES) {
		fprintf(stderr, "그래프: 정점의 개수 초과");
		return;
	}
	g->n++;
}
// 간선 삽입 연산, v를 u의 인접 리스트에 삽입한다.
void insert_edge(GraphType* g, int u, int v)
{
	GraphNode* node;
	if (u >= g->n || v >= g->n) {
		fprintf(stderr, "그래프: 정점 번호 오류");
		return;
	}
	node = (GraphNode*)malloc(sizeof(GraphNode));
	node->vertex = v;
	node->link = g->adj_list[u];
	g->adj_list[u] = node;
}

// --- 여기서부터 스택을 위한 ADT 구현
#define MAX_STACK_SIZE 100
typedef int element;
typedef struct {
	element stack[MAX_STACK_SIZE];
	int top;
} StackType;

// 스택 초기화 함수
void init(StackType* s)
{
	s->top = -1;
}
// 공백 상태 검출 함수
int is_empty(StackType* s)
{
	return (s->top == -1);
}
// 포화 상태 검출 함수
int is_full(StackType* s)
{
	return (s->top == (MAX_STACK_SIZE - 1));
}
// 삽입함수
void push(StackType* s, element item)
{
	if (is_full(s)) {
		fprintf(stderr, "스택 포화 에러\n");
		return;
	}
	else s->stack[++(s->top)] = item;
}
// 삭제함수
element pop(StackType* s)
{
	if (is_empty(s)) {
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else return s->stack[(s->top)--];
}
// 스택 ADT 구현 끝

void print_degree(int degree[], int n)
{
	for (int i = 0; i < n; i++)
		printf("%d ", degree[i]);

	printf("\n");
}

// 위상정렬을 수행한다.
void topo_sort(GraphType* g) // 이 함수를 수정한다
{
	int i;
	StackType s;
	GraphNode* node;

	// 모든 정점의 진입 차수를 계산
	int* in_degree = (int*)malloc(g->n * sizeof(int));
	int* out_degree = (int*)malloc(g->n * sizeof(int));
	for (i = 0; i < g->n; i++)			// 초기화
		in_degree[i] = 0;
	for (i = 0; i < g->n; i++)			// 초기화
		out_degree[i] = 0;
	for (i = 0; i < g->n; i++) {
		GraphNode* node = g->adj_list[i];//정점 i에서 나오는 간선들
		while (node != NULL) {
			in_degree[node->vertex]++;
			node = node->link;
		}
	}
	// 이전 문제에서 작성한 out_degree 계산 부분을 여기에 사용하면 된다
	for (i = 0; i < g->n; i++) {
		node = g->adj_list[i];
		while (node != NULL) {
			out_degree[i]++;
			node = node->link;
		}
	}
	//print_degree(in_degree, g->n);
	//print_degree(out_degree, g->n);
	print_sorted_value(g);
	// 진입 차수가 0인 정점을 스택에 삽입
	init(&s);
	for (i = 0; i < g->n; i++) {
		if (in_degree[i] == 0) push(&s, i);
	}
	// 위상 순서를 생성
	while (!is_empty(&s)) {
		int w;
		w = pop(&s);
		printf("%d->", w);			//정점 출력(공백없이)
		node = g->adj_list[w];	//각 정점의 진입 차수를 변경
		while (node != NULL) {
			int u = node->vertex;
			in_degree[u]--;			//진입 차수를 감소
			if (in_degree[u] == 0) push(&s, u);
			node = node->link;   // 다음 정점
		}
	}
	free(in_degree);
	printf("\n");

}
/*
element delete_max_heap(GraphType* h) // 삭제 함수
{
	int parent, child;
	element item, temp;
	item = h->adj_list[1];
	temp = h->adj_list[(h->n)--];
	parent = 1;
	child = 2;
	while (child <= h->n) {
		// 현재 노드의 자식노드 중 더 작은 자식노드를 찾는다.
		if ((child < h->n) && (h->adj_list[child].key) < h->adj_list[child + 1].key)
			child++;
		if (temp.key >= h->adj_list[child].key)
			break;
		// 한 단계 아래로 이동
		h->adj_list[parent] = h->adj_list[child];
		parent = child;
		child *= 2;
	}
	h->adj_list[parent] = temp;
	return item;
}
*/
void print_sorted_value(GraphType* a)
{
	/*
	Step4: print_sorted_value 함수 구현
	Heap 에 들어있는 값들을 내림차순으로 정렬하여 출력하는 함수를 작성하여 main 함수에서 호출해보라..
	힌트 : 교재 <프로그램 ____>의 heap_sort 함수를 참조하라.
	*/
	//printf("size %d\n", a.heap_size);
	int i;
	/*for (i = a.n; i > 0; i--) {
		printf("%d ", delete_max_heap(&a).key);
	}*/
	GraphType* h;
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
	free(h);
}
int main(void)
{
	GraphType g;
	int u, v;
	int n;

	graph_init(&g);

	scanf("%d", &n);

	for (int i = 0; i < n; i++)
		insert_vertex(&g, i);

	scanf("%d %d", &u, &v);
	while (u != -1) {
		insert_edge(&g, u, v);
		scanf("%d %d", &u, &v);
	}

	topo_sort(&g);
	// 동적 메모리 반환 코드 생략
	return 0;
}