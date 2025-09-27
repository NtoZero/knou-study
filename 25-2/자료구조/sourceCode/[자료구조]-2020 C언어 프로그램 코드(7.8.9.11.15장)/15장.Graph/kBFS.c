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

//���� �߰�
void add_edgeGraph(Graph* g, int v, int w) {
	g->adj[v][w] = 1;
}

int printGraph(Graph* g) {
	
	int i,j;
	printf("�׷���:\n");
		
	for (i = 0; i < g->nv; i++) {
		for(j = 0; j < g->nv; j++) {
			if (g->adj[i][j] != 0)
				printf("%d - %d \t%d \t", i, j, g->adj[i][j]);
		}
		printf("\n");
	}
}

// ���� ���� s���� �ʺ� �켱 Ž��  
void BFS(Graph* g, int s) {
	
	int i, adjacent;
	//�湮 ����Ʈ
	int visited[MAX_VERTICES];
	for (i = 0; i < g->nv; i++) {
		visited[i] = 0;
	}

	//�� �� ����
	int queue[MAX_VERTICES];
	int front = 0, rear = 0;

	//���� ������ �湮 ǥ���ϰ� ť�� ����  
	visited[s] = 1;
	queue[rear++] = s;

	//ť�� ������ �ִ� �� �ݺ� 
	while (front != rear) {
		//������ ������ �湮�ϰ�, 
		s = queue[front++];
		printf("%d ", s);

		// ��� ���� ������ ����,
		// �湮���� �ʾ����� �湮 ǥ�� �� ť�� ����
		for (adjacent = 0; adjacent < g->nv; adjacent++) {
			if (g->adj[s][adjacent] && !visited[adjacent]) {
				visited[adjacent] = 1;
				queue[rear++] = adjacent;
			}
		}
	}
}

int main() {

	//���� �׸�15-1 
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

	printf("�ʺ� �켱 Ž��\n");
	BFS(g, 0);

	freeGraph(g);

	return 0;
}
