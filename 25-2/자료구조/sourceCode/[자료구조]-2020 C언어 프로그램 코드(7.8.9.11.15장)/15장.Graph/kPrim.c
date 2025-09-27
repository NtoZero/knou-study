#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 10
#define MAX_COST 1000000000

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

int min_costVertex(int cost[], int MSTSet[], int n) {

	int i;
	int min = MAX_COST, min_index;

	for (i = 0; i < n; i++)
		if (MSTSet[i] == 0 && cost[i] < min)
			min = cost[i], min_index = i;

	return min_index;
}

//����� ���������, �̰Ͱ� Ʈ�� ���� �˰����� �̿��ؼ� Ʈ���� ������ �� �ִ�. 
int printMST(int root[], Graph* g) {
	
	int i;
	int minCost = 0;
	
	for (i = 1; i < g->nv; i++) {
		printf("����: %d -- %d (%d)\n", root[i], i,	g->adj[i][root[i]]);
		minCost += g->adj[i][root[i]];
	}
	printf("Prim's MST Cost: %d\n", minCost);
	//�̰� ����� ����ϴ� ���̰�, �߰� ������ ���� 10, 25, 15, 20, 35������ ����� ��ġ���� �� �� �ִ�.	
}

void primMST(Graph* g) {
	
	int i, j, count;
	int root[g->nv];
	int cost[g->nv];
	int MSTSet[g->nv];

	//����ġ�� �ִ�� ����  
	for (i = 0; i < g->nv; i++)
		cost[i] = MAX_COST, MSTSet[i] = 0;

	cost[0] = 0;
	root[0] = -1;

	//��� ������ ����... 
	for (count = 0; count < g->nv - 1; count++) {
		//�ּ� ��� ���� ����  
		i = min_costVertex(cost, MSTSet, g->nv);

		MSTSet[i] = 1;
		
		printf("For Vertex: %d\n", count);
		for (j = 0; j < g->nv; j++)
			//�ּҺ�� �������� ��ü  
			if (g->adj[i][j] && MSTSet[j] == 0 && g->adj[i][j] < cost[j]) {
				root[j] = i, cost[j] = g->adj[i][j];
				//���� ���� ������ ���� ���� ���...  
				printf("�߰�: %d -- %d (%d)\n", i, j, cost[j]);
			}
	}
	
	printf("\n");
	printMST(root, g);
}

void main() {


	int i,j;
	
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
						
	//�׷����� �ݿ�
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


