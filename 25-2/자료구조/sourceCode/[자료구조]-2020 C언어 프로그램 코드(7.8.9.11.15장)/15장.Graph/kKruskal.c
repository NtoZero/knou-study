#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 10

typedef struct Graph {
  
	int nv;	//���� ���� 
	int adj[MAX_VERTICES][MAX_VERTICES];

} Graph;

//�� �׷��� ����  
Graph* make_nullGraph(int n) {
	
	int i,j;
	Graph* g = malloc(sizeof(Graph));
	g->nv = n;
	//���� 
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			g->adj[i][j] = 0;
		}
	}
	return g;
}

//������ ��ȯ   
void freeGraph(Graph* g) { free(g); }

int printGraph(Graph* g) {
	
	int i,j;
	printf("�׷���:\n");
		
	for (i = 0; i < g->nv; i++) {
		for(j = 0; j < g->nv; j++) {
			if (g->adj[i][j] != 0)
				printf("%d - %d \t(%d)\t", i, j, g->adj[i][j]);
		}
		printf("\n");
	}
	
	printf("\n");
}

//quicksort()�� ũ�� ���Լ�,  
int comparator(const void *p1, const void *p2) {
	
	const int (*x)[3] = p1;
	const int (*y)[3] = p2;
	return (*x)[2]-(*y)[2];
}

//�ּҺ�� ������ �����ϱ� ���� ����ġ�� �������� �����ϱ� ���� �غ�  
void makeSet(int root[], int rank[], int n) {
	
	int i;
	for(i = 0; i < n; i++) {
		root[i] = i;
		rank[i] = 0;
	}
}

//�� Ʈ���� �ϳ��� ���� �� �ش� ���(node)�� ��Ʈ�� ã�� �Լ�   
int findRoot(int root[], int u) {
	
	if(root[u] == u) return u;
	else return root[u] = findRoot(root, root[u]);
}

//�� Ʈ���� �ϳ��� ���� �Լ�  
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
	
	//������� ������ ����, stdlib�� quicksort() ���  
	qsort(cost, n, sizeof(cost[0]), comparator);

	int root[n];
	int rank[n];
	makeSet(root, rank, n);

	int minCost = 0;
	
	//MST�� �߰��� ����
	for(i=0; i<n; i++) {
		int u = findRoot(root, cost[i][0]);
		int v = findRoot(root, cost[i][1]);
		int w = cost[i][2];
		
		//��Ʈ�� �ٸ��� �ٸ� Ʈ���� �ִٴ� �ǹ� ���� �ϳ��� ����  
		if(u != v) {
			unionSet(u, v, root, rank);
			minCost += w;
			printf("����: %d -- %d (%d)\n", cost[i][0], cost[i][1], w);
		}
	}
	printf("Kruskal's MST: %d\n", minCost);
}


void main() {

	int i,j, ne;
	
	Graph* g = make_nullGraph(6);
	
	//������ �׷���  	
	//add_edgeGraph()�� ������� �ʰ�, ����ġ�� ���� ����  
	//��Ī�̹Ƿ� ��ﰢ��ķ� �Է�   
	int w[6][6] = { { 0, 10, 0,  30, 45, 0},
					{ 0, 0,  50, 0,  40, 25},
					{ 0, 0,  0,  0,  35, 15},
					{ 0, 0,  0,  0,  0,  20},
					{ 0, 0,  0,  0,  0,  55},						
					{ 0, 0,  0,  0,  0,  0}};
	
	//�׷����� �ݿ� �� MST ������ ���� cost �迭 ����, �� ������ ������ ���� ne�� ������ 
	ne = 10; 
	int cost[ne][3];
	int nne=0; //���� �ε��� 
	for (i = 0; i < g->nv; i++) {
		for(j = 0; j < g->nv; j++) {
			if (i<j && w[i][j] != 0) { //������ �׷����̹Ƿ� ��ﰢ��� �κи�...
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

