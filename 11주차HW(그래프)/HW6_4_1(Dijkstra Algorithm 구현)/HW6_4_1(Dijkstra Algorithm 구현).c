#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#define TRUE 1 
#define FALSE 0 
#define MAX_VERTICES 100 
#define INF 1000000 /* ���Ѵ� (������ ���� ���) */
int start;
/*typedef struct GraphNode {
	int vertex;
	struct GraphNode* link;
} GraphNode;*/
typedef struct GraphType {
	int n; // ������ ����
	int weight[MAX_VERTICES][MAX_VERTICES];
	//int adj_mat[MAX_VERTICES][MAX_VERTICES]; // ������ ����ġ ���� 
	//GraphNode* previous[MAX_VERTICES];
} GraphType;
int distance[MAX_VERTICES]; /* �����������κ����� �ִܰ�� �Ÿ� */
int found[MAX_VERTICES]; /* �湮�� ���� ǥ�� */
int previous[MAX_VERTICES]; // �ִ� ��� ����
void graph_init(GraphType* g) // �׷��� �ʱ�ȭ
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
void insert_edge(GraphType* g, int start, int end, int weight) // ���� ���� ����
{
	if (start >= g->n || end >= g->n) {
		fprintf(stderr, "�׷���: ���� ��ȣ ����");
		return;
	}
	g->weight[start][end] = weight;
	g->weight[end][start] = weight;
}
int choose(int distance[], int n, int found[])
{
	// ����
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
		printf(" -> %d", end);
	}
}
void shortest_path(GraphType* g, int start)
{
	int i, u, w;
	//sequence = (int*)malloc(sizeof(int) * g->n);
	for (i = 0; i < g->n; i++) /* �ʱ�ȭ */
	{
		//sequence[i] = -1;
		distance[i] = g->weight[start][i];
		found[i] = FALSE;
		previous[i] = start;
	}
	found[start] = TRUE; /* ���� ���� �湮 ǥ�� */
	distance[start] = 0;
	for (i = 0; i < g->n - 1; i++) {
		u = choose(distance, g->n, found);
		//sequence[i] = u;
		found[u] = TRUE;
		print_path(start, u);
		printf(" <%d>\n", distance[u]);
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
int main(void)
{
	GraphType g;
	graph_init(&g);
	read_graph(&g, "input.txt");
	/*������ ������ ����
	5
	0 1 10
	0 3 60
	1 3 30
	1 2 45
	1 4 50
	2 3 5
	2 4 20
	*/
	shortest_path(&g, 0);
	//start = 0;
	/*
	0 -> 1<10>
	0 -> 1 ->3<40>
	0 -> 1 -> 3 -> 2<45>
	0 -> 1 -> 4<60>
	*/

	//start = 4;
	//shortest_path(&g, 4);
	/*4 -> 2<20>
	4 -> 2 -> 3<25>
	4 -> 1<50>
	4 -> 1 -> 0<60>
	*/
	return 0;
}
/*
	GraphType g = { 7,
	{{ 0, 7, INF, INF, 3, 10, INF },
	{ 7, 0, 4, 10, 2, 6, INF },
	{ INF, 4, 0, 2, INF, INF, INF },
	{ INF, 10, 2, 0, 11, 9, 4 },
	{ 3, 2, INF, 11, 0, INF, 5 },
	{ 10, 6, INF, 9, INF, 0, INF },
	{ INF, INF, INF, 4, 5, INF, 0 } }
	};*/