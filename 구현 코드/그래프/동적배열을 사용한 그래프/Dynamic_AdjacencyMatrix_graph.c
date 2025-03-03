//무방향 그래프, 인접행렬 방식으로 구현
//동적 2차원 배열 사용
#include "Dynamic_AdjacencyMatrix_graph.h"

void Error(char* message) {
	fprintf(stderr, "%s\n", message);
	exit(EXIT_FAILURE);
}

GraphType* CreateGraph() {
	GraphType* g = (GraphType*)malloc(sizeof(GraphType));
	if (!g) Error("memory allocation failed.");
	//그래프 초기화
	g->totalVertices = 0;
	g->adjMat = NULL;
	return g;
}

void InsertVertex(GraphType* g, int v) { //정점 삽입
	int n = g->totalVertices + 1; //새로운 정점 개수
	//1. 전체 행 포인터 배열 - 처음에는 malloc, 이후에는 realloc
	if (g->adjMat == NULL) {
		g->adjMat = (int**)malloc(sizeof(int*) * n);
	}
	else {
		g->adjMat = (int**)realloc(g->adjMat, sizeof(int*) * n);
	}
	if (!g->adjMat) Error("memory allocation failed.");

	//2. 새로 추가된 행 할당(malloc 사용)하고, 새 행을 0으로 초기화
	g->adjMat[n - 1] = (int*)malloc(sizeof(int) * n);
	if (!g->adjMat[n - 1]) Error("memory allocation failed.");
	for (int i = 0; i < n; i++) {
		g->adjMat[n - 1][i] = 0;//새로 추가된 n-1번째 행을 0으로 초기화
	}

	//3. 기존 행 크기 증가(1열 추가) 및 0으로 초기화(realloc 사용)
	for (int i = 0; i < n - 1; i++) {
		g->adjMat[i] = (int*)realloc(g->adjMat[i], sizeof(int) * n);
		if (!g->adjMat[i]) Error("memory allocation failed.");
		g->adjMat[i][n - 1] = 0; //새로 추가된 n-1번째 열을 0으로 초기화
	}

	//4.정점 삽입(정점 개수 증가)
	//정점 v는 사용되지 않는다.
	//정점 번호 0,1,2...대로 차례로 삽입됨
	g->totalVertices = n;
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
	for (int i = 0; i < (*g)->totalVertices; i++) {
		free((*g)->adjMat[i]);
	}
	free((*g)->adjMat);
	free(*g);
	*g = NULL;
}
