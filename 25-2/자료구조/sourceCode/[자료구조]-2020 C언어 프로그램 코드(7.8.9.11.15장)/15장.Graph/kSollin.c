#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 10

typedef struct Graph {
  
	int nv;	//���� ���� 
	int adj[MAX_VERTICES][MAX_VERTICES];

} Graph;

//�� ������ �ּ� ��� ����  
int min_edge[MAX_VERTICES];

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

void sollinMST(int nv, int ne, int cost[ne][3]) {

    int trees = nv; //������ ��峪 Ʈ���� ���� �׷����� ����

	int root[nv];
	int rank[nv];
	makeSet(root, rank, nv);
		
	int minCost = 0;
				 
    while (trees > 1) {//�κ� Ʈ���� ���� �� ����  
 
 	printf("# of Trees: %d\n", trees);   
    	//�ּ� ��� edge ���� �迭 
	    int i;
	    for (i = 0; i <nv; ++i) {
       		min_edge[i]	= -1;
		}
 
        for (i = 0; i < ne; ++i) {
            int u, v;
 
            u = findRoot(root, cost[i][0]);
			v = findRoot(root, cost[i][1]);
 
			//�ٸ� Ʈ���� ���
			//����� ���� �� �ּ� ����� ������ ����, 
			//��, "min_edge[x] = i"�� ��� x�� �ּ� ��� ������ i�� ����� �����̶�� ��
            if (u != v) {
	            if (min_edge[u] == -1 || cost[min_edge[u]][2] > cost[i][2]) min_edge[u] = i;
            	if (min_edge[v] == -1 || cost[min_edge[v]][2] > cost[i][2]) min_edge[v] = i;
      		}
		}
		
        for (i = 0; i < nv; ++i) {

			//�ش� ���(i��)�� �ּ� ��� ���� ����  
            if (min_edge[i] == -1) continue;
            
            int u = findRoot(root, cost[min_edge[i]][0]);
			int v = findRoot(root, cost[min_edge[i]][1]);

			//��Ʈ�� �ٸ��� �ٸ� Ʈ���� �ִٴ� �ǹ� ���� �ϳ��� ���� 
			if (u != v) {
				unionSet(u, v, root, rank);
				//�߰� ��尡 Ʈ���� ���ϴ� ��� ��Ʈ�� ���; ������ ��� 0-2�� 1-5�� �ǹ� 				
				//printf("�߰�: %d -- %d (%d)\n", u, v, cost[min_edge[i]][2]);
				printf("����: (%d)\n", cost[min_edge[i]][2]);				

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
	
	//add_edgeGraph()�� ������� �ʰ�, ����ġ�� ���� ����  
	//��Ī�̹Ƿ� �ݵ�� �ﰢ��ķ� �Է�   
	//����, �� ��尡 �����ϸ� �ȵ�!!!!!!!!!!!!
	
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
				g->adj[i][j] = w[i][j]; g->adj[j][i] = w[i][j]; //�ϻﰢ�κ� ����  
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
