#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 10

typedef struct Graph {
  
	int nv;	//정점 갯수 
	int adj[MAX_VERTICES][MAX_VERTICES];

} Graph;

//각 정점의 최소 비용 간선  
int min_edge[MAX_VERTICES];

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

void sollinMST(int nv, int ne, int cost[ne][3]) {

    int trees = nv; //독립된 노드나 트리가 없는 그래프로 가정

	int root[nv];
	int rank[nv];
	makeSet(root, rank, nv);
		
	int minCost = 0;
				 
    while (trees > 1) {//부분 트리가 없을 때 까지  
 
 	printf("# of Trees: %d\n", trees);   
    	//최소 비용 edge 저장 배열 
	    int i;
	    for (i = 0; i <nv; ++i) {
       		min_edge[i]	= -1;
		}
 
        for (i = 0; i < ne; ++i) {
            int u, v;
 
            u = findRoot(root, cost[i][0]);
			v = findRoot(root, cost[i][1]);
 
			//다른 트리인 경우
			//노드의 간선 중 최소 비용인 간선을 저장, 
			//즉, "min_edge[x] = i"는 노드 x의 최소 비용 간선이 i와 연결된 간선이라는 뜻
            if (u != v) {
	            if (min_edge[u] == -1 || cost[min_edge[u]][2] > cost[i][2]) min_edge[u] = i;
            	if (min_edge[v] == -1 || cost[min_edge[v]][2] > cost[i][2]) min_edge[v] = i;
      		}
		}
		
        for (i = 0; i < nv; ++i) {

			//해당 노드(i번)는 최소 비용 간선 없음  
            if (min_edge[i] == -1) continue;
            
            int u = findRoot(root, cost[min_edge[i]][0]);
			int v = findRoot(root, cost[min_edge[i]][1]);

			//루트가 다르면 다른 트리에 있다는 의미 따라서 하나로 묶음 
			if (u != v) {
				unionSet(u, v, root, rank);
				//추가 노드가 트리에 속하는 경우 루트가 출력; 예제의 경우 0-2는 1-5를 의미 				
				//printf("추가: %d -- %d (%d)\n", u, v, cost[min_edge[i]][2]);
				printf("간선: (%d)\n", cost[min_edge[i]][2]);				

				minCost += cost[min_edge[i]][2];				
				--trees;
			}
        }
	}
	printf("Sollin's MST: %d\n", minCost);
}

void main() {

	int i,j, ne;
	
	Graph* g = make_nullGraph(6);
	
	//add_edgeGraph()를 사용하지 않고, 가중치를 쉽게 정의  
	//대칭이므로 반드시 삼각행렬로 입력   
	//또한, 고립 노드가 존재하면 안됨!!!!!!!!!!!!
	
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
				g->adj[i][j] = w[i][j]; g->adj[j][i] = w[i][j]; //하삼각부분 포함  
				cost[nne][0] = i; 
				cost[nne][1] = j;				
				cost[nne][2] = w[i][j];
				nne++;
			}
		}
	}
	
	printGraph(g);

	sollinMST(g->nv, ne, cost);

}
