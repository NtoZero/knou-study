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

//quicksort()용 크기 비교함수,  
int comparator(const void *p1, const void *p2) {
	
	const int (*x)[3] = p1;
	const int (*y)[3] = p2;
	return (*x)[2]-(*y)[2];
}

//최소비용 간선을 선택하기 위해 가중치를 기준으로 정렬하기 위한 준비  
void makeSet(int root[], int rank[], int n) {
	
	int i;
	for(i = 0; i < n; i++) {
		root[i] = i;
		rank[i] = 0;
	}
}

//두 트리를 하나로 묶을 때 해당 노드(node)의 루트를 찾는 함수   
int findRoot(int root[], int u) {
	
	if(root[u] == u) return u;
	else return root[u] = findRoot(root, root[u]);
}

//두 트리를 하나로 묶는 함수  
void unionSet(int u, int v, int root[], int rank[]) {

	u = findRoot(root,u);
	v = findRoot(root,v);

	if(rank[u] < rank[v]) {
		root[u] = v;
	} else if(rank[u] > rank[v]) 	{
		root[v] = u;
	} else {
		root[v] = u;
		rank[u]++;
	}
}

void kruskalMST(int n, int cost[n][3]) {
	
	int i;
	
	//비용으로 간선을 정렬, stdlib의 quicksort() 사용  
	qsort(cost, n, sizeof(cost[0]), comparator);

	int root[n];
	int rank[n];
	makeSet(root, rank, n);

	int minCost = 0;
	
	//MST에 추가할 간선
	for(i=0; i<n; i++) {
		int u = findRoot(root, cost[i][0]);
		int v = findRoot(root, cost[i][1]);
		int w = cost[i][2];
		
		//루트가 다르면 다른 트리에 있다는 의미 따라서 하나로 묶음  
		if(u != v) {
			unionSet(u, v, root, rank);
			minCost += w;
			printf("간선: %d -- %d (%d)\n", cost[i][0], cost[i][1], w);
		}
	}
	printf("Kruskal's MST: %d\n", minCost);
}


void main() {

	int i,j, ne;
	
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
	
	//그래프에 반영 및 MST 생성을 위한 cost 배열 생성, 이 시점엔 간선의 갯수 ne가 정해짐 
	ne = 10; 
	int cost[ne][3];
	int nne=0; //간선 인덱스 
	for (i = 0; i < g->nv; i++) {
		for(j = 0; j < g->nv; j++) {
			if (i<j && w[i][j] != 0) { //무방향 그래프이므로 상삼각행렬 부분만...
				g->adj[i][j] = w[i][j]; g->adj[j][i] = w[i][j]; 
				cost[nne][0] = i; 
				cost[nne][1] = j;				
				cost[nne][2] = w[i][j];
				nne++;
			}
		}
	}

	printGraph(g);
	
	kruskalMST(ne, cost);

}

