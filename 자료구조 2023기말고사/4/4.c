#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define TRUE 1 
#define FALSE 0 
#define MAX_VERTICES 100 
#define INF 1000000 /* 무한대 (연결이 없는 경우) */
typedef struct GraphType {
	int n; // 정점의 개수
	int weight[MAX_VERTICES][MAX_VERTICES];
	//int adj_mat[MAX_VERTICES][MAX_VERTICES]; // 간선의 가중치 저장 
	//GraphNode* previous[MAX_VERTICES];
} GraphType;
int distance[MAX_VERTICES]; /* 시작정점으로부터의 최단경로 거리 */
int found[MAX_VERTICES]; /* 방문한 정점 표시 */
int previous[MAX_VERTICES]; // 최단 경로 추적
void graph_init(GraphType* g) // 그래프 초기화
{
	int r, c;
	g->n = 0;
	for (r = 0; r < MAX_VERTICES; r++) {
		for (c = 0; c < MAX_VERTICES; c++)
			g->weight[r][c] = INF;
	}
	for (r = 0; r < MAX_VERTICES; r++)
		g->weight[r][r] = 0;
}
void insert_edge(GraphType* g, int start, int end, int weight) // 간선 삽입 연산
{
	if (start >= g->n || end >= g->n) {
		fprintf(stderr, "그래프: 정점 번호 오류");
		return;
	}
	g->weight[start][end] = weight;
	g->weight[end][start] = weight;
}
int choose(int distance[], int n, int found[])
{
	// 생략
	int i, min, minpos;
	min = INT_MAX;
	minpos = -1;
	for (i = 0; i < n; i++)
		if (distance[i] < min && !found[i]) {
			min = distance[i];
			minpos = i;
		}
	return minpos;
}
/*void print_status(GraphType* g)
{
	int i = 0;
	while (sequence[i] != 0) {
		if (sequence[i] != start) {
			printf("%d ", start);
			int sq = sequence[i];
			while (previous[sq] != 0) {
				sq = previous[sq];
				printf("-> %d ", sq);
			}
			printf("-> %d ", sequence[i]);
			printf("<%d>\n", distance[sequence[i]]);
		}
		i++;
	}
}*/
void print_path(int start, int end)
{
	if (start == end)
		printf("%d", start);
	else {
		print_path(start, previous[end]);
		printf("-<%d>->%d", distance[end], end); //distance[previous[end] + 1]
	}
}
void shortest_path(GraphType* g, int start)
{
	int i, u, w;
	//sequence = (int*)malloc(sizeof(int) * g->n);
	for (i = 0; i < g->n; i++) /* 초기화 */
	{
		//sequence[i] = -1;
		distance[i] = g->weight[start][i];
		found[i] = FALSE;
		previous[i] = start;
	}
	found[start] = TRUE; /* 시작 정점 방문 표시 */
	distance[start] = 0;
	for (i = 0; i < g->n - 1; i++) {
		u = choose(distance, g->n, found);
		//sequence[i] = u;
		found[u] = TRUE;
		print_path(start, u);
		printf("(%d)\n", distance[u]);
		for (w = 0; w < g->n; w++)
			if (!found[w])
				if (distance[u] + g->weight[u][w] < distance[w]) {
					distance[w] = distance[u] + g->weight[u][w];
					//printf("w=%d dist[w]=%d	u=%d dist[u]=%d	g->weight[u][v]=%d\n", w, distance[w], u, distance[u], g->weight[u][w]);
					previous[w] = u;
				}
		/*
		printf("selected[] =	");
		for (w = 0; w < g->n; w++)
			printf("%d	", found[w]);
		printf("\ndist[] =	");
		for (w = 0; w < g->n; w++)
			printf("%d	", distance[w]);
		*/
	}
	//print_status(g);
}
void read_graph(GraphType* g)
{
	int num, s, e, w;
	scanf("%d", &g->n);
	scanf("%d %d %d", &s, &e, &w);
	while (s != -1) {
		insert_edge(g, s, e, w);
		scanf("%d %d %d", &s, &e, &w);
	}
}
int main(void)
{
	GraphType g;
	graph_init(&g);
	read_graph(&g);
	shortest_path(&g, 4);
	return 0;
}