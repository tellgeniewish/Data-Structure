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
	int n;	// ������ ����
	GraphNode* adj_list[MAX_VERTICES];
} GraphType;

// �׷��� �ʱ�ȭ 
void graph_init(GraphType* g)
{
	int v;
	g->n = 0;
	for (v = 0; v < MAX_VERTICES; v++)
		g->adj_list[v] = NULL;
}
// ���� ���� ����
void insert_vertex(GraphType* g, int v)
{
	if (((g->n) + 1) > MAX_VERTICES) {
		fprintf(stderr, "�׷���: ������ ���� �ʰ�");
		return;
	}
	g->n++;
}
// ���� ���� ����, v�� u�� ���� ����Ʈ�� �����Ѵ�.
void insert_edge(GraphType* g, int u, int v)
{
	GraphNode* node;
	if (u >= g->n || v >= g->n) {
		fprintf(stderr, "�׷���: ���� ��ȣ ����");
		return;
	}
	node = (GraphNode*)malloc(sizeof(GraphNode));
	node->vertex = v;
	node->link = g->adj_list[u];
	g->adj_list[u] = node;
}

// --- ���⼭���� ������ ���� ADT ����
#define MAX_STACK_SIZE 100
typedef int element;
typedef struct {
	element stack[MAX_STACK_SIZE];
	int top;
} StackType;

// ���� �ʱ�ȭ �Լ�
void init(StackType* s)
{
	s->top = -1;
}
// ���� ���� ���� �Լ�
int is_empty(StackType* s)
{
	return (s->top == -1);
}
// ��ȭ ���� ���� �Լ�
int is_full(StackType* s)
{
	return (s->top == (MAX_STACK_SIZE - 1));
}
// �����Լ�
void push(StackType* s, element item)
{
	if (is_full(s)) {
		fprintf(stderr, "���� ��ȭ ����\n");
		return;
	}
	else s->stack[++(s->top)] = item;
}
// �����Լ�
element pop(StackType* s)
{
	if (is_empty(s)) {
		fprintf(stderr, "���� ���� ����\n");
		exit(1);
	}
	else return s->stack[(s->top)--];
}
// ���� ADT ���� ��

void print_degree(int degree[], int n)
{
	for (int i = 0; i < n; i++)
		printf("%d ", degree[i]);

	printf("\n");
}

// ���������� �����Ѵ�.
void topo_sort(GraphType* g) // �� �Լ��� �����Ѵ�
{
	int i;
	StackType s;
	GraphNode* node;

	// ��� ������ ���� ������ ���
	int* in_degree = (int*)malloc(g->n * sizeof(int));
	int* out_degree = (int*)malloc(g->n * sizeof(int));
	for (i = 0; i < g->n; i++)			// �ʱ�ȭ
		in_degree[i] = 0;
	for (i = 0; i < g->n; i++)			// �ʱ�ȭ
		out_degree[i] = 0;
	for (i = 0; i < g->n; i++) {
		GraphNode* node = g->adj_list[i];//���� i���� ������ ������
		while (node != NULL) {
			in_degree[node->vertex]++;
			node = node->link;
		}
	}
	// ���� �������� �ۼ��� out_degree ��� �κ��� ���⿡ ����ϸ� �ȴ�
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
	// ���� ������ 0�� ������ ���ÿ� ����
	init(&s);
	for (i = 0; i < g->n; i++) {
		if (in_degree[i] == 0) push(&s, i);
	}
	// ���� ������ ����
	while (!is_empty(&s)) {
		int w;
		w = pop(&s);
		printf("%d->", w);			//���� ���(�������)
		node = g->adj_list[w];	//�� ������ ���� ������ ����
		while (node != NULL) {
			int u = node->vertex;
			in_degree[u]--;			//���� ������ ����
			if (in_degree[u] == 0) push(&s, u);
			node = node->link;   // ���� ����
		}
	}
	free(in_degree);
	printf("\n");

}
/*
element delete_max_heap(GraphType* h) // ���� �Լ�
{
	int parent, child;
	element item, temp;
	item = h->adj_list[1];
	temp = h->adj_list[(h->n)--];
	parent = 1;
	child = 2;
	while (child <= h->n) {
		// ���� ����� �ڽĳ�� �� �� ���� �ڽĳ�带 ã�´�.
		if ((child < h->n) && (h->adj_list[child].key) < h->adj_list[child + 1].key)
			child++;
		if (temp.key >= h->adj_list[child].key)
			break;
		// �� �ܰ� �Ʒ��� �̵�
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
	Step4: print_sorted_value �Լ� ����
	Heap �� ����ִ� ������ ������������ �����Ͽ� ����ϴ� �Լ��� �ۼ��Ͽ� main �Լ����� ȣ���غ���..
	��Ʈ : ���� <���α׷� ____>�� heap_sort �Լ��� �����϶�.
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
	// ���� �޸� ��ȯ �ڵ� ����
	return 0;
}