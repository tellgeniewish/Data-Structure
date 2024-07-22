#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "minheap.h"
#include "unionfind.h"
#define MAX_VERTICES 100
#define INF 9999
typedef struct GraphType { // (1) Kruskal 의 최소 비용 신장 트리를 구현한 프로그램 11.8 을 다음과 같이 수정해 보시오. 
	int n; // 정점의 개수 
	int adj_mat[MAX_VERTICES][MAX_VERTICES]; // 간선의 가중치 저장 
} GraphType; // 그래프를 다음과 같이 인접 행렬로 표현한다.
void graph_init(GraphType* g) // 그래프 초기화
{
	int r, c;
	g->n = 0;
	for (r = 0; r < MAX_VERTICES; r++)
		for (c = 0; c < MAX_VERTICES; c++)
			g->adj_mat[r][c] = INF;
}
void insert_edge(GraphType* g, int start, int end, int weight) // 간선 삽입 연산
{
	if (start >= g->n || end >= g->n) {
		fprintf(stderr, "그래프: 정점 번호 오류");
		return;
	}
	g->adj_mat[start][end] = weight;
	g->adj_mat[end][start] = weight;
}
void insert_all_edges(HeapType* h, GraphType* g)
{
	// 인접 행렬이나 인접 리스트에서 간선들을 읽어서 최소 히프에 삽입 
	// 현재는 예제 그래프의 간선들을 삽입한다.
	// 구현
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
void kruskal(GraphType* g, GraphType* t) // kruskal의 최소 비용 신장 트리 프로그램
{
	// 구현
	int edge_accepted = 0;
	int v, u;
	element e;

	HeapType heap;
	set_init(g->n);

	init(&heap);
	insert_all_edges(&heap, g);
	printf("선택된 간선<순서대로>:\n");
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
	그래프 정보는 HW6_1_1 에서 정의된 것과 같은 형식의 텍스트 파일로 제공된다고 가정한다.
	단, 각 간선에 대해 그것의 가중치도 함께 저장한다
	(예: 간선 (1, 2)의 가중치가 30 인 경우
	1 2 30 을 저장함).
	그래프 정보를 인접 행렬로 읽어들이기 위해 HW6_1_1 에서 작성한 read_graph() 함수를 수정하여 사용한다.
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

	// 코드 삽입
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
	GraphType g, t;		// 입력 그래프, 결과 트리

	graph_init(&g);
	read_graph(&g, "input.txt");
	//read_graph(&g, "input2.txt");

	graph_init(&t);
	t.n = g.n;

	kruskal(&g, &t);

	printf("파일로 출력:\n");
	write_graph(&t, "output.txt");
	write_graph(&t, NULL);	// to stdout
}