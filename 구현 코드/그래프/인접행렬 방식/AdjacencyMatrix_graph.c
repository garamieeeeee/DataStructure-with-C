//무방향 그래프, 인접행렬 방식으로 구현
//정적 2차원 배열 사용
#include "AdjacencyMatrix_graph.h"

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
	//정점 개수가 초과되는 경우, 정점을 삽입하지 않고 종료한다
	if (g->totalVertices + 1 > MAX_VERTICES) {
		fprintf(stderr, "The number of vertices has exceeded.\n");
		return;
	}
	//정점 삽입(정점 개수 증가)
	//정점 v는 사용되지 않는다.
	//정점 번호 0,1,2...대로 차례로 삽입됨
	g->totalVertices++;
}

void InsertEdge(GraphType* g, int u, int v) {//간선 (u,v) 삽입
	if (u >= g->totalVertices || v >= g->totalVertices) {
		//정점 번호 에러: 간선을 삽입하지 않고 종료
		fprintf(stderr, "vertex number error.\n");
		return;
	}
	//간선 삽입
	//방향 그래프의 경우라면 g->adjMat[start][end]에만 1을 삽입한다
	g->adjMat[u][v] = 1;
	g->adjMat[v][u] = 1;
}

void Print_adjMat(GraphType* g) {//정점 개수만큼의 사이즈(n*n)로 인접행렬을 출력한다
	for (int r = 0; r < g->totalVertices; r++) {
		for (int c = 0; c < g->totalVertices; c++) {
			printf("%2d ", g->adjMat[r][c]);
		}
		printf("\n");
	}
	printf("\n");
}

void DestroyGraph(GraphType** g) {//그래프 메모리 해제
	if (*g == NULL) return;
	free(*g);
	*g = NULL;
}
