#include <stdio.h>
#include "minheap.h"
#include "unionfind.h"

#define MAX_VERTICES 100
#define INF 9999

typedef struct GraphType {
	int n;					// ������ ����
	int adj_mat[MAX_VERTICES][MAX_VERTICES];
} GraphType;

// �׷��� �ʱ�ȭ 
void graph_init(GraphType *g)
{
     // ����
}

/*  */
void read_graph(GraphType *g, char *filename)
{
     // ����
}

/*  */
void write_graph(GraphType *g, char *filename)
{
     // ����
}

// ���� ����̳� ���� ����Ʈ���� �������� �о �ּ� ������ ���� 
// ����� ���� �׷����� �������� �����Ѵ�.
void insert_all_edges(HeapType *h, GraphType *g)
{
     // ����
}

// kruskal�� �ּ� ��� ���� Ʈ�� ���α׷�
void kruskal(GraphType *g, GraphType *t)
{
     // ����
}

main()
{
	GraphType g, t;		// �Է� �׷���, ��� Ʈ��
	
	graph_init(&g);
	//read_graph(&g, "input1.txt");
	read_graph(&g, "input2.txt");

	graph_init(&t);
	t.n = g.n;
	
	kruskal(&g, &t);
	
     printf("���Ϸ� ���:\n");
	write_graph(&t, "output.txt");	
	write_graph(&t, NULL);	// to stdout
}
