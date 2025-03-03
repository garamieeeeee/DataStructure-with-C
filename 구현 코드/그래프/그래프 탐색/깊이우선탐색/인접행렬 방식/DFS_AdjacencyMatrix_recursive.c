//무방향 그래프, 인접행렬 방식
//2차원 배열 사용
//DFS 알고리즘(재귀적인 방식)
#include "DFS_AdjacencyMatrix_recursive.h"

void Error(char* message) {
	fprintf(stderr, "%s\n", message);
	exit(EXIT_FAILURE);
}

GraphType* CreateGraph() {
	GraphType* g = (GraphType*)malloc(sizeof(GraphType));
	if (!g) Error("memory allocation failed.");
	//그래프 초기화
	g->totalVertices = 0;
	for (int r = 0; r < MAX_VERTICES; r++) {
		for (int c = 0; c < MAX_VERTICES; c++) {
			g->adjMat[r][c] = 0;
		}
	}
	return g;
}

void InsertVertex(GraphType* g, int v) { //정점 삽입
	if (g->totalVertices + 1 > MAX_VERTICES) {
		fprintf(stderr, "The number of vertices has exceeded.\n");
		return;
	}
	g->totalVertices++;
}

void InsertEdge(GraphType* g, int u, int v) {//간선 (u,v) 삽입
	if (u >= g->totalVertices || v >= g->totalVertices) {
		fprintf(stderr, "vertex number error.\n");
		return;
	}
	g->adjMat[u][v] = 1;
	g->adjMat[v][u] = 1;
}

void Print_adjMat(GraphType* g) {
	for (int r = 0; r < g->totalVertices; r++) {
		for (int c = 0; c < g->totalVertices; c++) {
			printf("%2d ", g->adjMat[r][c]);
		}
		printf("\n");
	}
	printf("\n");
}

void DestroyGraph(GraphType** g) {
	if (*g == NULL) return;
	free(*g);
	*g = NULL;
}

void Init() { //visited 배열을 모두 0(FALSE)로 초기화
	for (int i = 0; i < MAX_VERTICES; i++) {
		visited[i] = FALSE;
	}
}

void DFS_mat(GraphType* g, int v) {//인접 행렬로 표현된 그래프에 대한 깊이 우선 탐색(시작정점: v)
	visited[v] = TRUE; //정점 v의 방문 표시
	printf("정점 %d -> ", v); //방문한 정점 출력
	int w; //정점 w
	for (w = 0; w < g->totalVertices; w++) { //v의 인접 정점 탐색
		if (g->adjMat[v][w] && !visited[w]) //g->adjMat[v][w] == 1이면 인접정점인 것 && 인접정점 w를 아직 방문하지 않았다면
			DFS_mat(g, w); //정점 w에서부터 DFS 다시 시작(재귀함수)
	}
}
