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
	int n; // ������ ����
	GraphNode*adj_mat[MAX_VERTICES];
} GraphType;
void graph_init(GraphType* g) // �׷��� �ʱ�ȭ
{
	int v;
	g->n = 0;
	for (v = 0; v < MAX_VERTICES; v++)
		g->adj_mat[v] = NULL;
}
void insert_vertex(GraphType* g, int v) // ���� ���� ����
{
	if (((g->n) + 1) > MAX_VERTICES) {
		fprintf(stderr, "�׷���: ������ ���� �ʰ�");
		return;
	}
	g->n++;
}
void insert_edge(GraphType* g, int start, int end) // ���� ���� ����
{
	if (start >= g->n || end >= g->n) {
		fprintf(stderr, "�׷���: ���� ��ȣ ����");
		return;
	}
	GraphNode* node = (GraphNode*)malloc(sizeof(GraphNode));
	node->vertex = end;
	node->link = g->adj_mat[start];
	g->adj_mat[start] = node;
}
void remove_node(GraphNode** phead, element item) { // 4�� ����Ʈ���� �н��� �Լ����� ListNode --> GraphNode�� ��������
	GraphNode* p, * prevp;

	if (*phead == NULL)
		printf("����Ʈ�� ����ֽ��ϴ�.\n");
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
			printf("%d�� ����Ʈ�� ����\n", item);
	}
}
void delete_edge(GraphType* g, int start, int end) // ���� ���� ����
{
	if (start >= g->n || end >= g->n) {
		fprintf(stderr, "�׷���: ���� ��ȣ ����");
		return;
	}

	remove_node(&g->adj_mat[start], end); // �굵 ����������, �Ű��������� �������� �����ͷ� �ް� �ֱ� ������, &�� �ּڰ��� ������ �Ѵ�
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

	// �ڵ� ����
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