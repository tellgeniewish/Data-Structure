#include <stdio.h>
#include <stdlib.h>
#include "queue.h"  // <------

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 50

typedef struct GraphNode
{  
   int vertex;
   struct GraphNode *link;
} GraphNode;

typedef struct GraphType {
	int n;	// ������ ����
	GraphNode *adj_list[MAX_VERTICES];
} GraphType;

// �׷��� �ʱ�ȭ 
void graph_init(GraphType *g)
{
	int v;
	g->n=0;
	for(v=0;v<MAX_VERTICES;v++)
		g->adj_list[v]=NULL;
}
// ���� ���� ����
void insert_vertex(GraphType *g, int v)
{
	if( ((g->n)+1) > MAX_VERTICES ){ 
		fprintf(stderr, "�׷���: ������ ���� �ʰ�");
		return;
	}
	g->n++;
}
// ���� ���� ����, v�� u�� ���� ����Ʈ�� �����Ѵ�.
void insert_edge(GraphType *g, int u, int v)
{

     // ���� �����ڵ忡��
}
int visited[MAX_VERTICES];


// �ʺ� �켱 Ž��(���� ����Ʈ)
// �� �ڵ忡 ������ ����ϱ� ���� �ڵ带 �����ϴ� ���� HW6_2_2�� �����̴�
void bfs_list(GraphType *g, int v) 
{  
	GraphNode *w;
	QueueType q;
	init(&q);    				// ť �ʱ� ȭ 
	visited[v] = TRUE;      // ���� v �湮 ǥ�� 
	enqueue(&q, v);			// ���������� ť�� ���� 
	while(!is_empty(&q)){			
 		v = dequeue(&q);		// ť�� ����� ���� ���� 
		for(w=g->adj_list[v]; w; w = w->link) //���� ���� Ž��
	  		if(!visited[w->vertex]){	// �̹湮 ���� Ž�� 
	    		visited[w->vertex] = TRUE;   // �湮 ǥ��
	     		enqueue(&q, w->vertex);	//������ ť�� ����
			}
	}
}

void read_graph(GraphType *g, char *filename)
{

     // ���� ���� �ڵ忡��
}
int main(void)
{
     GraphType graph;
     int u, v;

     graph_init(&graph);
     read_graph(&graph, "infile.txt");
     
     printf("Enter ����:");
     scanf("%d", &v);
     
     bfs_list(&graph, v);
}
