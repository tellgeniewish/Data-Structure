#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "minheap.h"
#include "unionfind.h"
#define MAX_VERTICES 100
#define INF 9999
typedef struct GraphType { // (1) Kruskal �� �ּ� ��� ���� Ʈ���� ������ ���α׷� 11.8 �� ������ ���� ������ ���ÿ�. 
	int n; // ������ ���� 
	int adj_mat[MAX_VERTICES][MAX_VERTICES]; // ������ ����ġ ���� 
} GraphType; // �׷����� ������ ���� ���� ��ķ� ǥ���Ѵ�.
void graph_init(GraphType* g) // �׷��� �ʱ�ȭ
{
	int r, c;
	g->n = 0;
	for (r = 0; r < MAX_VERTICES; r++)
		for (c = 0; c < MAX_VERTICES; c++)
			g->adj_mat[r][c] = INF;
}
void insert_edge(GraphType* g, int start, int end, int weight) // ���� ���� ����
{
	if (start >= g->n || end >= g->n) {
		fprintf(stderr, "�׷���: ���� ��ȣ ����");
		return;
	}
	g->adj_mat[start][end] = weight;
	g->adj_mat[end][start] = weight;
}
void insert_all_edges(HeapType* h, GraphType* g)
{
	// ���� ����̳� ���� ����Ʈ���� �������� �о �ּ� ������ ���� 
	// ����� ���� �׷����� �������� �����Ѵ�.
	// ����
	int i, j;
	element e;
	for (i = 0; i < g->n; i++) {
		for (j = i + 1; j < g->n; j++) {
			if (g->adj_mat[i][j] != INF) {
				e.key = g->adj_mat[i][j];
				e.u = i;
				e.v = j;
				insert_min_heap(h, e);
			}
		}
	}
}
void kruskal(GraphType* g, GraphType* t) // kruskal�� �ּ� ��� ���� Ʈ�� ���α׷�
{
	// ����
	int edge_accepted = 0;
	int v, u;
	element e;

	HeapType heap;
	set_init(g->n);

	init(&heap);
	insert_all_edges(&heap, g);
	printf("���õ� ����<�������>:\n");
	while (edge_accepted < (g->n - 1)) {
		e = delete_min_heap(&heap);
		u = set_find(e.u);
		v = set_find(e.v);

		if (u != v) {
			set_union(u, v);
			insert_edge(t, e.u, e.v, e.key);
			printf("<%d, %d> %d\n", e.u, e.v, e.key);
			edge_accepted++;
		}
	}
	printf("\n");
}
void read_graph(GraphType* g, char* filename)
{
	/*
	�׷��� ������ HW6_1_1 ���� ���ǵ� �Ͱ� ���� ������ �ؽ�Ʈ ���Ϸ� �����ȴٰ� �����Ѵ�.
	��, �� ������ ���� �װ��� ����ġ�� �Բ� �����Ѵ�
	(��: ���� (1, 2)�� ����ġ�� 30 �� ���
	1 2 30 �� ������).
	�׷��� ������ ���� ��ķ� �о���̱� ���� HW6_1_1 ���� �ۼ��� read_graph() �Լ��� �����Ͽ� ����Ѵ�.
	*/
	int num, s, e, w;
	FILE* fp;
	fp = fopen(filename, "rt");
	if (fp == NULL)
	{
		printf("file %s open error!\n", filename);
		return;
	}

	fscanf(fp, "%d", &g->n);
	while (fscanf(fp, "%d %d %d", &s, &e, &w) != EOF) {
		insert_edge(g, s, e, w);
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
		for (j = i + 1; j < g->n; j++) {
			if (g->adj_mat[i][j] != INF) {
				fprintf(fp, "%d %d %d\n", i, j, g->adj_mat[i][j]);
			}
		}
	}

	if (filename != NULL) fclose(fp);
}
void main()
{
	GraphType g, t;		// �Է� �׷���, ��� Ʈ��

	graph_init(&g);
	read_graph(&g, "input.txt");
	//read_graph(&g, "input2.txt");

	graph_init(&t);
	t.n = g.n;

	kruskal(&g, &t);

	printf("���Ϸ� ���:\n");
	write_graph(&t, "output.txt");
	write_graph(&t, NULL);	// to stdout
}