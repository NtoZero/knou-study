#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 10

typedef struct Graph {
  
	int nv;	//정점 갯수 
	int adj[MAX_VERTICES][MAX_VERTICES];

} Graph;

//빈 그래프 생성  
Graph* make_nullGraph(int n) {
	
	int i,j;
	Graph* g = malloc(sizeof(Graph));
	g->nv = n;
	//간선 
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			g->adj[i][j] = 0;
		}
	}

	return g;
}

//기억장소 반환   
void freeGraph(Graph* g) { free(g); }

//간선 추가
void add_edgeGraph(Graph* g, int v, int w) {
	g->adj[v][w] = 1;
}

int printGraph(Graph* g) {
	
	int i,j;
	printf("그래프:\n");
		
	for (i = 0; i < g->nv; i++) {
		for(j = 0; j < g->nv; j++) {
			if (g->adj[i][j] != 0)
				printf("%d - %d \t%d \t", i, j, g->adj[i][j]);
		}
		printf("\n");
	}
}

// 시작 점점 s부터 너비 우선 탐색  
void BFS(Graph* g, int s) {
	
	int i, adjacent;
	//방문 리스트
	int visited[MAX_VERTICES];
	for (i = 0; i < g->nv; i++) {
		visited[i] = 0;
	}

	//빈 규 생성
	int queue[MAX_VERTICES];
	int front = 0, rear = 0;

	//현재 정점을 방문 표시하고 큐에 넣음  
	visited[s] = 1;
	queue[rear++] = s;

	//큐에 정점이 있는 한 반복 
	while (front != rear) {
		//정점을 꺼내서 방문하고, 
		s = queue[front++];
		printf("%d ", s);

		// 모든 인접 정점에 대해,
		// 방문하지 않았으면 방문 표시 후 큐에 넣음
		for (adjacent = 0; adjacent < g->nv; adjacent++) {
			if (g->adj[s][adjacent] && !visited[adjacent]) {
				visited[adjacent] = 1;
				queue[rear++] = adjacent;
			}
		}
	}
}

int main() {

	//교재 그림15-1 
	Graph* g = make_nullGraph(8);
	add_edgeGraph(g, 0, 1);
	add_edgeGraph(g, 0, 2);
	add_edgeGraph(g, 1, 0);
	add_edgeGraph(g, 1, 3);
	add_edgeGraph(g, 1, 4);	
	add_edgeGraph(g, 2, 0);
	add_edgeGraph(g, 2, 5);
	add_edgeGraph(g, 2, 6);
	add_edgeGraph(g, 3, 1);
	add_edgeGraph(g, 3, 7);
	add_edgeGraph(g, 4, 1);
	add_edgeGraph(g, 4, 7);
	add_edgeGraph(g, 5, 2);
	add_edgeGraph(g, 5, 7);
	add_edgeGraph(g, 6, 2);
	add_edgeGraph(g, 6, 7);
	add_edgeGraph(g, 7, 3);
	add_edgeGraph(g, 7, 4);
	add_edgeGraph(g, 7, 5);
	add_edgeGraph(g, 7, 6);	
	
	printGraph(g);

	printf("너비 우선 탐색\n");
	BFS(g, 0);

	freeGraph(g);

	return 0;
}
