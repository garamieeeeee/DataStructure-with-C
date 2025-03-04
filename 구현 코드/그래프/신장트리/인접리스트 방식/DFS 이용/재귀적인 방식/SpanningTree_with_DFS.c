//무방향 그래프, 인접 리스트 방식으로 구현
//1차원 배열 + 연결리스트 사용
//DFS를 수행하면서 사용한 간선들을 모아 스패닝트리를 만든다

#include <stdio.h>
#include <stdlib.h>

#define FALSE 0
#define TRUE 1
#define MAX_VERTICES 100 
typedef struct GraphNode {
	int vertex;
	struct GraphNode* link;
}GraphNode;

typedef struct {
	int totalVertices;
	GraphNode* adjList[MAX_VERTICES];
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
	for (int i = 0; i < MAX_VERTICES; i++) {
		g->adjList[i] = NULL;
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

void InsertEdge(GraphType* g, int u, int v) {//간선 삽입: v를 u의 인접리스트에 삽입한다
	if (u >= g->totalVertices || v >= g->totalVertices) {
		fprintf(stderr, "vertex number error.\n");
		return;
	}
	GraphNode* node1 = (GraphNode*)malloc(sizeof(GraphNode));
	if (!node1) Error("memory allocation failed.");
	node1->vertex = v;
	node1->link = g->adjList[u];
	g->adjList[u] = node1;

	GraphNode* node2 = (GraphNode*)malloc(sizeof(GraphNode));
	if (!node2) Error("memory allocation failed.");
	node2->vertex = u;
	node2->link = g->adjList[v];
	g->adjList[v] = node2;
}

void Print_adjList(GraphType* g) {
	for (int i = 0; i < g->totalVertices; i++) {
		GraphNode* p = g->adjList[i];
		printf("정점 %d의 인접 리스트 ", i);
		while (p != NULL) {
			printf("-> %d ", p->vertex);
			p = p->link;
		}
		printf("\n");
	}
	printf("\n");
}

void DestroyGraph(GraphType** g) {
	if (*g == NULL) return;
	for (int i = 0; i < (*g)->totalVertices; i++) {
		GraphNode* temp;
		while ((*g)->adjList[i] != NULL) {
			temp = (*g)->adjList[i];
			(*g)->adjList[i] = (*g)->adjList[i]->link;
			free(temp);
		}
	}
	free(*g);
	*g = NULL;
}

void Init() { //visited 배열을 모두 0(FALSE)로 초기화
	for (int i = 0; i < MAX_VERTICES; i++) {
		visited[i] = FALSE;
	}
}

void DFS_list(GraphType* g, int v) {//DFS 변형: DFS를 수행하면서 사용한 간선들을 edges에 저장한다
	visited[v] = TRUE; //정점 v의 방문 표시
	printf("정점 %d -> ", v); //방문한 정점 출력
	Edge e;
	e.start = v;
	GraphNode* w; //정점 w
	for (w = g->adjList[v]; w != NULL; w = w->link) {//v의 인접 정점 탐색(연결리스트 순회)
		if (!visited[w->vertex]) { //인접정점인 w를 아직 방문하지 않았다면
			e.end = w->vertex;
			edges[EdgeCount++] = e; //간선 (v, w) 저장
			DFS_list(g, w->vertex);//정점 w에서부터 DFS 다시 시작(재귀함수)
		}
	}
}

GraphType* Build_SpanningTree(GraphType* g) { //edges[]를 이용하여 그래프 g의 스패닝 트리를 만들어 반환한다.
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
	Print_adjList(g);

	//dfs
	Init(); //visited 배열 FALSE로 초기화
	printf("<< 깊이 우선 탐색 >>\n");
	DFS_list(g, 0); //0을 시작정점으로 깊이 우선 탐색
	printf("\n");
	printf("그래프 g의 신장트리:\n");
	GraphType* spanningTree = Build_SpanningTree(g);
	Print_adjList(spanningTree);

	//그래프 삭제
	DestroyGraph(&g);
	DestroyGraph(&spanningTree);

	return 0;
}
