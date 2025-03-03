//DFS를 하면서 사용한 간선들을 모아 mst를 구성하는 코드
//무방향 그래프, 인접행렬 방식
//2차원 배열 사용
//DFS 알고리즘(재귀적인 방식)

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
Edge spanningTree[MAX_VERTICES]; //신장트리 간선들을 저장할 배열
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

void Build_SpanninTree(GraphType* mst) { //스패닝 트리를 구성하는 함수
	for (int i = 0; i < EdgeCount; i++) {
		Edge e = spanningTree[i];
		InsertEdge(mst, e.start, e.end);
	}
}

GraphType* DFS_mat(GraphType* g, int v) {//DFS 변형: 깊이우선탐색을 하면서 사용된 간선을 배열에 저장하고, 배열을 사용해 신장트리를 구성해 반환한다.
	visited[v] = TRUE; //정점 v의 방문 표시
	printf("정점 %d -> ", v); //방문한 정점 출력
	Edge e;
	e.start = v;

	int w; //정점 w
	GraphType* mst = CreateGraph(); mst->totalVertices = g->totalVertices;
	for (w = 0; w < g->totalVertices; w++) { //v의 인접 정점 탐색
		if (g->adjMat[v][w] && !visited[w]) { //g->adjMat[v][w] == 1이면 인접정점인 것 && 인접정점 w를 아직 방문하지 않았다면
			e.end = w;
			spanningTree[EdgeCount++] = e; //간선 (v, w) 저장
			DFS_mat(g, w); //정점 w에서부터 DFS 다시 시작(재귀함수)
		}
	}
	Build_SpanninTree(mst); //스패닝트리 만들어 반환
	return mst;
}

int main() {
	GraphType* g = CreateGraph();
	GraphType* mst;

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
	mst = DFS_mat(g, 0); //0을 시작정점으로 깊이 우선 탐색. 반환값으로 신장트리를 받음
	printf("\n그래프 g의 신장트리 출력: \n");
	Print_adjMat(mst);

	//그래프 삭제
	DestroyGraph(&g);

	return 0;
}
