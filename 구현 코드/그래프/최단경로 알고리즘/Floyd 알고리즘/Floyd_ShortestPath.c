//Floyd 최단경로 알고리즘
#include "Floyd_ShortestPath.h"

GraphType* Create_Graph() {
	GraphType* g = (GraphType*)malloc(sizeof(GraphType));
	if (!g) {
		fprintf(stderr, "memory allocation failed.\n");
		exit(EXIT_FAILURE);
	}
	g->totalVertices = 0;
	for (int i = 0; i < MAX_VERTICES; i++) {
		for (int j = 0; j < MAX_VERTICES; j++) {
			if (i == j) g->weight[i][j] = 0;
			else g->weight[i][j] = INF;
		}
	}
	return g;
}

void Insert_Vertex(GraphType* g, int v) {
	if (g->totalVertices + 1 > MAX_VERTICES) {
		fprintf(stderr, "The number of vertices has exceeded.\n");
		return;
	}
	g->totalVertices++;
}

void Insert_Edge(GraphType* g, int u, int v, int w) {
	if (u >= g->totalVertices || v >= g->totalVertices) {
		fprintf(stderr, "vertex number error.\n");
		return;
	}
	g->weight[u][v] = w;
	g->weight[v][u] = w;
}

void Print_Graph(GraphType* g) {
	for (int i = 0; i < g->totalVertices; i++) {
		for (int j = 0; j < g->totalVertices; j++) {
			if (g->weight[i][j] == INF) printf(" - ");
			else printf("%2d ", g->weight[i][j]);
		}
		printf("\n");
	}
	printf("\n\n");
}
/*---------------------*/

//플로이드 최단경로 알고리즘
//모든 정점 사이의 최단경로를 구한다.
void Floyd_ShortestPath(GraphType* g) {
	int i, j, k;

	//배열 D, path 초기화
	for (i = 0; i < g->totalVertices; i++) {
		for (j = 0; j < g->totalVertices; j++) {
			//D[i][j]의 초깃값: i->j로 가는 직접간선의 가중치
			//만약 두 정점 i,j간의 직접간선이 없다면 초깃값은 INF
			D[i][j] = g->weight[i][j];
			//path[i][j]의 초깃값은 -1
			//나중에 Floyd 알고리즘을 수행하면서 중간지점 k가 생긴다면 path[i][j] = k;
			//만약 Floyd 알고리즘을 다 끝냈는데도 path[i][j] == -1이라면 i->j로 갈때 중간에 다른 정점을 거치지 않고 바로 i->j로 가는것이 최단경로라는 뜻
			path[i][j] = -1;
		}
	}

	//Floyd 알고리즘: 모든 정점 사이의 최단거리를 구한다.
	//k정점을 거쳐서 i->j로가는 모든 경우를 고려하여 D[i][j]를 업데이트한다.
	for (k = 0; k < g->totalVertices; k++) { //(k:경유지점 / i:시작점 / j: 도착점)
		for (i = 0; i < g->totalVertices; i++) {
			for (j = 0; j < g->totalVertices; j++) {
				if (D[i][k] + D[k][j] < D[i][j]) {
					//모든 정점 i와 j에 대하여
					//k를 거쳐서 i->j로 가는게 빠른지, 아니면 k를 거치지 않고 가는게 더 빠른지 비교
					D[i][j] = D[i][k] + D[k][j]; //k를 거쳐서 가는게 더 빠르다면, 최단경로가 i->..->k->..->j가 될것
					path[i][j] = k; //i->j로 가는 최단경로의 중간지점은 k가 됨
				}
			}
		}
	}
}

//정점 i->j로 가는 최단거리 경로를 재귀적으로 출력한다(도착정점인 j는 출력하지 않음)
void Print_Path(int i, int j) {
	if (path[i][j] == -1) {
		//중간지점 없이 바로 i->j로 가는게 최단경로인 경우: i만 출력하고 종료
		printf("%d -> ", i);
		return;
	}
	Print_Path(i, path[i][j]); //path[i][j]가 k라면, 중간지점인 k에 대하여 i->k로 가는 최단경로를 출력한다.
	Print_Path(path[i][j], j); //path[i][j]가 k라면, 중간지점인 k에 대하여 k->j로 가는 최단경로를 출력한다.
}

//Print_Path()를 호출하여 start->end로 가는 최단거리 경로를 전체 출력한다.
//마지막 정점(도착정점)을 출력하기 위해 필요
void Print_ShortestPath(int start, int end) {
	if (D[start][end] == INF) {//D[i][j]가 INF라는 것은 정점i에서 정점j까지 가는 경로가 전혀 없다는 뜻
		printf("%d에서 %d로 갈 수 있는 경로가 없습니다.\n", start, end);
		return;
	}
	printf("%d에서 %d로 가는 최단 경로: ", start, end);
	Print_Path(start, end);
	printf("%d ", end); //도착정점 출력
	printf("(최단거리: %d)\n", D[start][end]);
}
