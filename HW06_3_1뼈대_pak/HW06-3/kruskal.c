#include <stdio.h>
#include "minheap.h"
#include "unionfind.h"

#define MAX_VERTICES 100
#define INF 9999

typedef struct GraphType {
	int n;					// 정점의 개수
	int adj_mat[MAX_VERTICES][MAX_VERTICES];
} GraphType;

// 그래프 초기화 
void graph_init(GraphType *g)
{
     // 구현
}

/*  */
void read_graph(GraphType *g, char *filename)
{
     // 구현
}

/*  */
void write_graph(GraphType *g, char *filename)
{
     // 구현
}

// 인접 행렬이나 인접 리스트에서 간선들을 읽어서 최소 히프에 삽입 
// 현재는 예제 그래프의 간선들을 삽입한다.
void insert_all_edges(HeapType *h, GraphType *g)
{
     // 구현
}

// kruskal의 최소 비용 신장 트리 프로그램
void kruskal(GraphType *g, GraphType *t)
{
     // 구현
}

main()
{
	GraphType g, t;		// 입력 그래프, 결과 트리
	
	graph_init(&g);
	//read_graph(&g, "input1.txt");
	read_graph(&g, "input2.txt");

	graph_init(&t);
	t.n = g.n;
	
	kruskal(&g, &t);
	
     printf("파일로 출력:\n");
	write_graph(&t, "output.txt");	
	write_graph(&t, NULL);	// to stdout
}
