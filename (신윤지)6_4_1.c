// 20200224 일본어과 신윤지
// Dijkstra Algorithm 구현
// 그래프는 인접 행렬, input.txt를 읽어들임
#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

#define MAX_VERTICES 50
#define INF 1000

int start; // print 함수에서 시작 정점 지정을 위함
int distance[MAX_VERTICES]; // 거리 배열
int found[MAX_VERTICES]; // 얘는 이미 찾아진 애들이에요 = selected[]
int previous[MAX_VERTICES]; // 최단 경로가 발견될 때 그 경로의 바로 앞 정점을 알 수 있음
int* sequence; // 최단 경로대로 출력하기 위해서 사용하는 배열입니다

typedef struct GraphType {
    int n;
    int adj_mat[MAX_VERTICES][MAX_VERTICES];
} GraphType;

void graph_init(GraphType *g) {
    int r, c;
    g->n=0;
    for(r=0; r<MAX_VERTICES; r++) {
        for(c=0; c<MAX_VERTICES; c++) {
            g->adj_mat[r][c]=INF;
        }
    }
}

void insert_edge(GraphType *g, int start, int end, int weight) {
    if(start>=g->n || end>=g->n) {
        fprintf(stderr, "그래프: 정점 번호 오류");
        return;
    }

    g->adj_mat[start][end] = weight;
    g->adj_mat[end][start] = weight;
}

void delete_edge(GraphType *g, int start, int end) {
    if(start>=g->n || end>=g->n) {
        fprintf(stderr, "그래프: 정점 번호 오류");
        return;
    }

    g->adj_mat[start][end] = 0;
    g->adj_mat[end][start] = 0;
}

void read_graph(GraphType *g, char *filename) {
    int number, u, v, w;
    FILE *fp;
    fp = fopen(filename, "rt");
    if(fp == NULL) {
        printf("file %s open error!\n", filename);
        return;
    }

    fscanf(fp, "%d\n", &number);
    g->n = number;

    while(fscanf(fp, "%d %d %d\n", &u, &v, &w)!=EOF) {
        insert_edge(g, u, v, w);
    }

    fclose(fp);
}

void write_graph(GraphType *g, char *filename) {
    int i = 0, j; 
    FILE *fp;

    if(filename==NULL) fp = stdout;
    else {
        fp = fopen(filename, "wt");
        if(fp==NULL) 
        {
            printf("file %s open error!\n", filename);
            return;
        }
    }

    while(sequence[i] >= 0) {
        if(sequence[i]!=start) {
        fprintf(fp, "%d ", start);
            int k = sequence[i];
            while(previous[k]!=0) {
                k = previous[k];
                fprintf(fp, "-> %d ", k);
            }
            fprintf(fp, "-> %d ", sequence[i]);
            fprintf(fp, "<%d>\n", distance[sequence[i]]);
        }
        i++;
    }
}

int choose(int distance[], int n, int found[]) {
    int i, min, minpos;
    min = INT_MAX;
    minpos = -1;
    for(i=0; i<n; i++) {
        if(distance[i] < min && !found[i]) {
            min = distance[i];
            minpos = i;
        }
    }
    return minpos;
}

void shortest_path(GraphType *g, int start) {
    int i, u, w;
    sequence = (int*)malloc(sizeof(int)*g->n);
    for(i=0; i<g->n; i++) {
        sequence[i] = -1;
        distance[i] = g->adj_mat[start][i];
        found[i] = 0;
    }
    found[start] = 1;
    distance[start] = 0;

    
    for(i=0; i<g->n-1; i++) {
        u = choose(distance, g->n, found);
        sequence[i] = u;
        found[u] = 1;
        for(w=0; w<g->n; w++) {
            if(!found[w]) {
                if(distance[u]+g->adj_mat[u][w] < distance[w]) {
                    distance[w] = distance[u] + g->adj_mat[u][w];
                    previous[w] = u;
                }
            }
        }
    }
}

int main(void) {
    GraphType g;

    graph_init(&g);
    read_graph(&g, "input.txt");
    shortest_path(&g, 0);
    start = 0;
    
    write_graph(&g, "output.txt");
    return 0;
}