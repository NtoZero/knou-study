#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 10
#define MAX_COST 1000000000

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

int printGraph(Graph* g) {
	
	int i,j;
	printf("그래프:\n");
		
	for (i = 0; i < g->nv; i++) {
		for(j = 0; j < g->nv; j++) {
			if (g->adj[i][j] != 0)
				printf("%d - %d \t(%d)\t", i, j, g->adj[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

int min_costVertex(int cost[], int MSTSet[], int n) {

	int i;
	int min = MAX_COST, min_index;

	for (i = 0; i < n; i++)
		if (MSTSet[i] == 0 && cost[i] < min)
			min = cost[i], min_index = i;

	return min_index;
}

//결과만 출력하지만, 이것과 트리 구축 알고리즘을 이용해서 트리를 구축할 수 있다. 
int printMST(int root[], Graph* g) {
	
	int i;
	int minCost = 0;
	
	for (i = 1; i < g->nv; i++) {
		printf("간선: %d -- %d (%d)\n", root[i], i,	g->adj[i][root[i]]);
		minCost += g->adj[i][root[i]];
	}
	printf("Prim's MST Cost: %d\n", minCost);
	//이건 결과를 출력하는 것이고, 추가 과정을 보면 10, 25, 15, 20, 35순서로 교재와 일치함을 알 수 있다.	
}

void primMST(Graph* g) {
	
	int i, j, count;
	int root[g->nv];
	int cost[g->nv];
	int MSTSet[g->nv];

	//가중치를 최대로 설정  
	for (i = 0; i < g->nv; i++)
		cost[i] = MAX_COST, MSTSet[i] = 0;

	cost[0] = 0;
	root[0] = -1;

	//모든 정점에 대해... 
	for (count = 0; count < g->nv - 1; count++) {
		//최소 비용 정점 선택  
		i = min_costVertex(cost, MSTSet, g->nv);

		MSTSet[i] = 1;
		
		printf("For Vertex: %d\n", count);
		for (j = 0; j < g->nv; j++)
			//최소비용 간선으로 교체  
			if (g->adj[i][j] && MSTSet[j] == 0 && g->adj[i][j] < cost[j]) {
				root[j] = i, cost[j] = g->adj[i][j];
				//간선 선택 과정을 보기 위한 출력...  
				printf("추가: %d -- %d (%d)\n", i, j, cost[j]);
			}
	}
	
	printf("\n");
	printMST(root, g);
}

void main() {


	int i,j;
	
	Graph* g = make_nullGraph(6);
	
	//교재의 그래프  
	//add_edgeGraph()를 사용하지 않고, 가중치를 쉽게 정의  
	//대칭이므로 상삼각행렬로 입력   
	int w[6][6] = { { 0, 10, 0,  30, 45, 0},
					{ 0, 0,  50, 0,  40, 25},
					{ 0, 0,  0,  0,  35, 15},
					{ 0, 0,  0,  0,  0,  20},
					{ 0, 0,  0,  0,  0,  55},						
					{ 0, 0,  0,  0,  0,  0}};
						
	//그래프에 반영
	for (i = 0; i < g->nv; i++) {
		for(j = 0; j < g->nv; j++) {
			if (i<j && w[i][j] != 0) {
				g->adj[i][j] = w[i][j]; g->adj[j][i] = w[i][j]; 
			}
		}
	}

	printGraph(g);

	primMST(g);

}


