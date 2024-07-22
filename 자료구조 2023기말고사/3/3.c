#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 50
typedef struct GraphType {
	int n;	// 정점의 개수
	int adj_mat[MAX_VERTICES][MAX_VERTICES];
} GraphType;

int visited[MAX_VERTICES];

// ===== 스택 코드의 시작 ===== 
#define MAX_STACK_SIZE 100

typedef int element;
typedef struct {
	element data[MAX_STACK_SIZE];
	int top;
} StackType;

// 스택 초기화 함수
void init_stack(StackType* s)
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
	else s->data[++(s->top)] = item;
}
// 삭제함수
element pop(StackType* s)
{
	if (is_empty(s)) {
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else return s->data[(s->top)--];
}
// 피크함수
element peek(StackType* s)
{
	if (is_empty(s)) {
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else return s->data[s->top];
}
// ===== 스택 코드의 끝 ===== 

// 그래프 초기화 
void init(GraphType* g)
{
	int r, c;
	g->n = 0;
	for (r = 0; r < MAX_VERTICES; r++)
		for (c = 0; c < MAX_VERTICES; c++)
			g->adj_mat[r][c] = 0;
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
// 간선 삽입 연산
void insert_edge(GraphType* g, int start, int end)
{
	if (start >= g->n || end >= g->n) {
		fprintf(stderr, "그래프: 정점 번호 오류");
		return;
	}
	g->adj_mat[start][end] = 1;
	g->adj_mat[end][start] = 1;
}

void dfs_mat_iterative(GraphType* g, int v) // 이 함수를 작성
{
	// 코드 작성
	int w;
	StackType s;
	init(&s);
	visited[v] = TRUE; // 정점 v 방문 표시 
	//printf("%d ", v);
	push(&s, v);
	while (!is_empty(&s)) {
		v = pop(&s);
		//for (w = 0; w < g->n; w++) // 인접 정점 탐색 
		if (g->adj_mat[v][w] && !visited[w]) {
			visited[w] = TRUE; // 방문 표시 
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
	int s, e; // 간선의 양쪽 정점

	scanf("%d", &n); // 정점의 개수
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