//무방향 그래프, 인접행렬 방식
//2차원 배열 사용
//DFS를 수행하면서 사용한 간선들을 모아 스패닝트리를 만든다.

#include <stdio.h>
#include <stdlib.h>

#define FALSE 0
#define TRUE 1
#define MAX_VERTICES 100 
typedef struct {
	int totalVertices;
	int adjMat[MAX_VERTICES][MAX_VERTICES];
}GraphType;

typedef struct {
	int start, end; //간선 (start, end)
}Edge;

int visited[MAX_VERTICES]; //정점 방문 표시할 배열
Edge edges[MAX_VERTICES]; //신장트리 간선들을 저장할 배열
int EdgeCount = 0; //저장된 간선의 개수

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

void DFS_mat(GraphType* g, int v) {//DFS 변형: DFS를 수행하면서 사용한 간선들을 edges[]에 저장함
	visited[v] = TRUE; //정점 v의 방문 표시
	printf("정점 %d -> ", v); //방문한 정점 출력
	Edge e;
	e.start = v;

	int w; //정점 w
	for (w = 0; w < g->totalVertices; w++) { //v의 인접 정점 탐색
		if (g->adjMat[v][w] && !visited[w]) { //g->adjMat[v][w] == 1이면 인접정점인 것 && 인접정점 w를 아직 방문하지 않았다면
			e.end = w;
			edges[EdgeCount++] = e; //간선 (v, w) 저장
			DFS_mat(g, w); //정점 w에서부터 DFS 다시 시작(재귀함수)
		}
	}
}

GraphType* Build_SpanningTree(GraphType* g) { //edges[]를 이용해 그래프 g의 스패닝 트리를 만들어 반환함
	GraphType* spanningTree = CreateGraph();
	spanningTree->totalVertices = g->totalVertices;
	for (int i = 0; i < EdgeCount; i++) {
		Edge e = edges[i];
		InsertEdge(spanningTree, e.start, e.end);
	}
	return spanningTree;
}

int main() {
	GraphType* g = CreateGraph();
	//정점 삽입(0,1,2,3,4)
	for (int i = 0; i < 5; i++) {
		InsertVertex(g, i);
	}
	//간선 (0,1) 삽입
	InsertEdge(g, 0, 1);
	//간선 (0,2) 삽입
	InsertEdge(g, 0, 2);
	//간선 (0,4) 삽입
	InsertEdge(g, 0, 4);
	//간선 (1,2) 삽입
	InsertEdge(g, 1, 2);
	//간선 (2,3) 삽입
	InsertEdge(g, 2, 3);
	//간선 (2,4) 삽입
	InsertEdge(g, 2, 4);
	//간선 (3,4) 삽입
	InsertEdge(g, 3, 4);

	//그래프 출력
	Print_adjMat(g);

	//dfs
	Init(); //visited 배열 FALSE로 초기화
	printf("<< 깊이 우선 탐색 >>\n");
	DFS_mat(g, 0); //0을 시작정점으로 깊이 우선 탐색
	printf("\n");
	printf("그래프 g의 신장트리:\n");
	GraphType* spanningTree = Build_SpanningTree(g);
	Print_adjMat(spanningTree);

	//그래프 삭제
	DestroyGraph(&g);
	DestroyGraph(&spanningTree);

	return 0;
}
