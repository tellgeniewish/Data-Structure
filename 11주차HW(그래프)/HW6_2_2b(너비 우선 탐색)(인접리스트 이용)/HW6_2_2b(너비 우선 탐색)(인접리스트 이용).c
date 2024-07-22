//인접행렬그래프.c 소스파일 
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "queue.h" // <------ 
#define MAX_VERTICES 50 
#define TRUE 1
#define FALSE 0
int visited[MAX_VERTICES]; // 전역변수는 0 으로 자동 초기화 
typedef struct GraphNode {
	int vertex;
	struct GraphNode* link;
} GraphNode;
typedef struct GraphType {
	int n; // 정점의 개수 
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
/*
void insert_edge(GraphType* g, int u, int v) // 간선 삽입 연산, v 를 u 의 인접 리스트에 삽입한다.
{
	GraphNode* node;
	if (u >= g->n || v >= g->n) {
		fprintf(stderr, "그래프: 정점 번호 오류");
		return;
	}
	// u 에 v 를 매단다
	node = (GraphNode*)malloc(sizeof(GraphNode));
	node->vertex = v;
	node->link = g->adj_list[u];
	g->adj_list[u] = node;
	// v 에 u 를 매단다
	node = (GraphNode*)malloc(sizeof(GraphNode));
	node->vertex = u;
	node->link = g->adj_list[v];
	g->adj_list[v] = node;
}
*/

void insert_edge(GraphType* g, int start, int end) // 간선 삽입 연산
{
	if (start >= g->n || end >= g->n) {
		fprintf(stderr, "그래프: 정점 번호 오류");
		return;
	}
	GraphNode* node = (GraphNode*)malloc(sizeof(GraphNode));
	node->vertex = end;
	node->link = g->adj_list[start];
	g->adj_list[start] = node;
}
/**/
/* 깊이 우선 탐색 depth_first_search(v) v 를 방문되었다고 표시;
for all u ∈ (v 에 인접한 정점) do
 if (u 가 아직 방문되지 않았으면)
 then depth_first_search(u) 
void dfs_list(GraphType* g, int v) // 깊이 우선 탐색(인접 리스트) 
{
	GraphNode* w;
	visited[v] = TRUE; // 정점 v 의 방문 표시 
	printf("%d ", v); // 방문한 정점 출력 
	for (w = g->adj_list[v]; w != NULL; w = w->link) // 인접 정점 탐색 
		if (!visited[w->vertex])
			dfs_list(g, w->vertex); //정점 w->vertex 에서 DFS 새로시작 
}*/
/* 넓이 우선 탐색 breadth_first_search(v)
v 를 방문되었다고 표시;
큐 Q 에 정점 v 를 삽입;
while (not is_empty(Q)) do
 큐 Q 에서 정점 w 를 삭제;
 for all u ∈ (w 에 인접한 정점) do
 if (u 가 아직 방문되지 않았으면) then u 를 방문되었다고 표시;
u 를 큐 Q 에 삽입; */
void bfs_list(GraphType* g, int v) // 너비 우선 탐색(인접 리스트) 
{
	GraphNode* w;
	QueueType q;
	init(&q); // 큐 초기 화 
	visited[v] = TRUE; // 정점 v 방문 표시 
	//printf("%d ", v);
	enqueue(&q, v); // 시작정점을 큐에 저장 
	while (!is_empty(&q)) {
		v = dequeue(&q); // 큐에 저장된 정점 선택 
		for (w = g->adj_list[v]; w; w = w->link) //인접 정점 탐색 
			if (!visited[w->vertex]) { // 미방문 정점 탐색 
				visited[w->vertex] = TRUE; // 방문 표시 
				printf("<%d %d>\n", v, w->vertex);
				//printf("%d ", w->vertex);
				enqueue(&q, w->vertex); //정점을 큐에 삽입 
			}
	}
}
void visited_init()
{
	int i;
	for (i = 0; i < MAX_VERTICES; i++)
		visited[i] = 0;
}
void read_graph(GraphType* g, char* filename)
{
	int num, s, e;
	FILE* fp;
	fp = fopen(filename, "rt");
	if (fp == NULL)
	{
		printf("file %s open error!\n", filename);
		return;
	}

	fscanf(fp, "%d", &num);
	//graph_init(g);
	for (int i = 0; i < num; i++) {
		insert_vertex(g, i);
	}
	while (fscanf(fp, "%d %d", &s, &e) != EOF) {
		insert_edge(g, s, e);
	}

	fclose(fp);
}
int main(void)
{
	GraphType g;
	graph_init(&g);
	/*
	insert_vertex(&g, 0);
	insert_vertex(&g, 1);
	insert_vertex(&g, 2);
	insert_vertex(&g, 3);
	insert_edge(&g, 0, 1);
	insert_edge(&g, 1, 2);
	insert_edge(&g, 2, 3);
	insert_edge(&g, 3, 0);
	insert_edge(&g, 0, 2);
	*/

	read_graph(&g, "input.txt");

	int v;
	printf("Enter 정점:");
	scanf("%d", &v);
	bfs_list(&g, v);

	/*printf("\n 깊이 우선 탐색\n");
	dfs_list(&g, 0); printf("\n");
	visited_init();
	dfs_list(&g, 1); printf("\n");
	visited_init();
	dfs_list(&g, 2); printf("\n");
	visited_init();
	dfs_list(&g, 3); printf("\n");*/
	/*printf("\n 넓이 우선 탐색\n");
	visited_init();
	bfs_list(&g, 0); printf("\n");
	visited_init();
	bfs_list(&g, 1); printf("\n");
	visited_init();
	bfs_list(&g, 2); printf("\n");
	visited_init();
	bfs_list(&g, 3); printf("\n");*/
}