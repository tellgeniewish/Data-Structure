#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 50
typedef struct GraphType {
	int n;	// ������ ����
	int adj_mat[MAX_VERTICES][MAX_VERTICES];
} GraphType;

int visited[MAX_VERTICES];

// ===== ���� �ڵ��� ���� ===== 
#define MAX_STACK_SIZE 100

typedef int element;
typedef struct {
	element data[MAX_STACK_SIZE];
	int top;
} StackType;

// ���� �ʱ�ȭ �Լ�
void init_stack(StackType* s)
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
	else s->data[++(s->top)] = item;
}
// �����Լ�
element pop(StackType* s)
{
	if (is_empty(s)) {
		fprintf(stderr, "���� ���� ����\n");
		exit(1);
	}
	else return s->data[(s->top)--];
}
// ��ũ�Լ�
element peek(StackType* s)
{
	if (is_empty(s)) {
		fprintf(stderr, "���� ���� ����\n");
		exit(1);
	}
	else return s->data[s->top];
}
// ===== ���� �ڵ��� �� ===== 

// �׷��� �ʱ�ȭ 
void init(GraphType* g)
{
	int r, c;
	g->n = 0;
	for (r = 0; r < MAX_VERTICES; r++)
		for (c = 0; c < MAX_VERTICES; c++)
			g->adj_mat[r][c] = 0;
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
// ���� ���� ����
void insert_edge(GraphType* g, int start, int end)
{
	if (start >= g->n || end >= g->n) {
		fprintf(stderr, "�׷���: ���� ��ȣ ����");
		return;
	}
	g->adj_mat[start][end] = 1;
	g->adj_mat[end][start] = 1;
}

void dfs_mat_iterative(GraphType* g, int v) // �� �Լ��� �ۼ�
{
	// �ڵ� �ۼ�
	int w;
	StackType s;
	init(&s);
	visited[v] = TRUE; // ���� v �湮 ǥ�� 
	//printf("%d ", v);
	push(&s, v);
	while (!is_empty(&s)) {
		v = pop(&s);
		//for (w = 0; w < g->n; w++) // ���� ���� Ž�� 
		if (g->adj_mat[v][w] && !visited[w]) {
			visited[w] = TRUE; // �湮 ǥ�� 
			printf("%d ", w);
			//push(&s, w);
			dfs_mat_iterative(g, v);
		}
	}
}
int main(void)
{
	GraphType* g;
	g = (GraphType*)malloc(sizeof(GraphType));
	init(g);
	int start;

	int n;
	int s, e; // ������ ���� ����

	scanf("%d", &n); // ������ ����
	for (int i = 0; i < n; i++)
		insert_vertex(g, i);

	scanf("%d %d", &s, &e);
	while (s != -1) {
		insert_edge(g, s, e);

		scanf("%d %d", &s, &e);
	}

	scanf("%d", &start);
	for (int i = 0; i < n; i++)
		visited[i] = 0;
	dfs_mat_iterative(g, start);

	free(g);
	return 0;
}