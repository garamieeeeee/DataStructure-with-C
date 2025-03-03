//무방향 그래프, 인접 리스트 방식으로 구현
//동적 1차원 배열 + 연결리스트 사용
//정점 개수 제한 없음

#include "Dynamic_AdjacencyList_graph.h"

void Error(char* message) {
	fprintf(stderr, "%s\n", message);
	exit(EXIT_FAILURE);
}

GraphType* CreateGraph() {
	GraphType* g = (GraphType*)malloc(sizeof(GraphType));
	if (!g) Error("memory allocation failed.");
	//그래프 초기화
	g->totalVertices = 0;
	g->adjList = NULL;
	return g;
}

void InsertVertex(GraphType* g, int v) { //정점 삽입
	int n = g->totalVertices + 1; //새로운 정점 개수
	if (g->adjList == NULL) {
		g->adjList = (GraphNode**)malloc(sizeof(GraphNode*) * n);
	}
	else {
		g->adjList = (GraphNode**)realloc(g->adjList, sizeof(GraphNode*) * n);
	}
	if (!g->adjList) Error("memory allocation failed.");

	//새로 추가된 정점의 인접리스트 초기화
	g->adjList[n - 1] = NULL;

	//정점 삽입(정점 개수 증가)
	//정점 v는 사용되지 않는다.
	//정점 번호 0,1,2...대로 차례로 삽입됨
	g->totalVertices = n;
}

void InsertEdge(GraphType* g, int u, int v) {//간선 삽입: v를 u의 인접리스트에 삽입한다
	if (u >= g->totalVertices || v >= g->totalVertices) {
		//정점 번호 에러: 간선을 삽입하지 않고 종료
		fprintf(stderr, "vertex number error.\n");
		return;
	}
	//새로운 노드 생성:v 노드를 생성하여 u의 인접리스트에 추가한다.
	//위치는 상관이 없으므로, 삽입을 편하게 하기 위하여 리스트의 맨 앞에 삽입한다.
	GraphNode* node1 = (GraphNode*)malloc(sizeof(GraphNode));
	if (!node1) Error("memory allocation failed.");
	node1->vertex = v;
	//노드 삽입
	node1->link = g->adjList[u];
	g->adjList[u] = node1;

	//무방향 그래프이므로 반대 방향도 추가:u 노드를 생성하여 v의 인접리스트에 삽입한다
	//방향 그래프라면 이 과정은 생략한다.
	GraphNode* node2 = (GraphNode*)malloc(sizeof(GraphNode));
	if (!node2) Error("memory allocation failed.");
	node2->vertex = u;
	node2->link = g->adjList[v];
	g->adjList[v] = node2;
}

void Print_adjList(GraphType* g) {
	for (int i = 0; i < g->totalVertices; i++) {//각 정점의 연결리스트들을 출력한다.
		GraphNode* p = g->adjList[i];//p: 정점 i의 연결리스트를 순회한다
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
	free((*g)->adjList);
	free(*g);
	*g = NULL;
}
