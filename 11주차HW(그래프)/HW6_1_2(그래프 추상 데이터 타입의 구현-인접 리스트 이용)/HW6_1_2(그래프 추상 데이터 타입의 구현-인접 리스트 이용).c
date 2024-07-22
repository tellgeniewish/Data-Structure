#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTICES 50
typedef int element;
typedef struct GraphNode {
	int vertex;
	struct GraphNode* link;
} GraphNode;
typedef struct GraphType {
	int n; // 정점의 개수
	GraphNode*adj_mat[MAX_VERTICES];
} GraphType;
void graph_init(GraphType* g) // 그래프 초기화
{
	int v;
	g->n = 0;
	for (v = 0; v < MAX_VERTICES; v++)
		g->adj_mat[v] = NULL;
}
void insert_vertex(GraphType* g, int v) // 정점 삽입 연산
{
	if (((g->n) + 1) > MAX_VERTICES) {
		fprintf(stderr, "그래프: 정점의 개수 초과");
		return;
	}
	g->n++;
}
void insert_edge(GraphType* g, int start, int end) // 간선 삽입 연산
{
	if (start >= g->n || end >= g->n) {
		fprintf(stderr, "그래프: 정점 번호 오류");
		return;
	}
	GraphNode* node = (GraphNode*)malloc(sizeof(GraphNode));
	node->vertex = end;
	node->link = g->adj_mat[start];
	g->adj_mat[start] = node;
}
void remove_node(GraphNode** phead, element item) { // 4장 리스트에서 학습한 함수에서 ListNode --> GraphNode로 변경했음
	GraphNode* p, * prevp;

	if (*phead == NULL)
		printf("리스트는 비어있습니다.\n");
	else if ((*phead)->vertex == item) {
		p = *phead;
		*phead = (*phead)->link;
		free(p);
	}
	else {
		p = *phead;
		do {
			prevp = p;
			p = p->link;
		} while (p != NULL && p->vertex != item);
		if (p != NULL) {
			prevp->link = p->link;
			free(p);
		}
		else
			printf("%d은 리스트에 없음\n", item);
	}
}
void delete_edge(GraphType* g, int start, int end) // 간선 삭제 연산
{
	if (start >= g->n || end >= g->n) {
		fprintf(stderr, "그래프: 정점 번호 오류");
		return;
	}

	remove_node(&g->adj_mat[start], end); // 얘도 포인터지만, 매개변수에서 포인터의 포인터로 받고 있기 때문에, &로 주솟값을 보내야 한다
	remove_node(&g->adj_mat[end], start);
}
void read_graph(GraphType* g, char* filename)
{
	int number, u, v;
	FILE* fp;
	fp = fopen(filename, "rt");
	if (fp == NULL)
	{
		printf("file %s open error!\n", filename);
		return;
	}

	fscanf(fp, "%d", &g->n);
	while (fscanf(fp, "%d %d", &u, &v) != EOF) {
		insert_edge(g, u, v);
	}

	fclose(fp);
}
void write_graph(GraphType* g, char* filename)
{
	int i, j;
	FILE* fp;

	if (filename == NULL) fp = stdout;
	else {
		fp = fopen(filename, "wt");
		if (fp == NULL)
		{
			printf("file %s open error!\n", filename);
			return;
		}
	}

	// 코드 삽입
	fprintf(fp, "%d\n", g->n);

	for (i = 0; i < g->n; i++) {
		GraphNode* current = g->adj_mat[i];
		while (current != NULL) {
			fprintf(fp, "%d %d\n", i, current->vertex);
			current = current->link;
		}
	}

	if (filename != NULL) fclose(fp);
}
int main(void)
{
	GraphType g;
	graph_init(&g);
	read_graph(&g, "input.txt");
	write_graph(&g, NULL);	// to stdout

	insert_edge(&g, 1, 3);
	write_graph(&g, NULL);	// to stdout

	delete_edge(&g, 2, 0);
	write_graph(&g, NULL);	// to stdout

	write_graph(&g, "output.txt");
}
/*
void main()
{
	GraphType* g;
	g = (GraphType*)malloc(sizeof(GraphType));
	init(g);
	for (int i = 0; i < 4; i++)
		insert_vertex(g, i);

	insert_edge(g, 0, 1);
	insert_edge(g, 0, 2);
	insert_edge(g, 0, 3);
	insert_edge(g, 1, 2);
	insert_edge(g, 2, 3);
	print_adj_mat(g);

	free(g);
}
*/