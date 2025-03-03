//무방향 그래프, 인접 리스트 방식으로 구현
//1차원 배열 + 연결리스트 사용
//DFS 알고리즘(명시적 스택 사용)
#include "DFS_AdjacencyList_with_stack.h"

void Error(char* message) {
	fprintf(stderr, "%s\n", message);
	exit(EXIT_FAILURE);
}
/*-----스택 관련 함수-----*/
StackType* CreateStack() {
	StackType* s = (StackType*)malloc(sizeof(StackType));
	if (!s) Error("memory allocation failed.");
	s->top = -1;
	return s;
}

int IsEmpty(StackType* s) {
	return (s->top == -1);
}

int IsFull(StackType* s) {
	return (s->top == MAX_STACK_SIZE - 1);
}

void Push(StackType* s, ElementType data) {
	if (IsFull(s)) Error("Stack is full.");
	s->stack[++(s->top)] = data;
}

ElementType Pop(StackType* s) {
	if (IsEmpty(s)) Error("Stack is empty.");
	return s->stack[(s->top)--];
}

void DestroyStack(StackType** s) {
	if (*s == NULL) return;
	free(*s);
	*s = NULL;
}
/*------------------------*/

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

void DFS_list_iterative(GraphType* g, int v) {//인접 리스트로 표현된 그래프에 대한 깊이 우선 탐색(시작정점: v)
	StackType* s = CreateStack(); //정점들을 저장할 스택 생성
	Push(s, v); //시작정점인 v를 스택에 우선 삽입
	while (!IsEmpty(s)) { //스택이 빌때까지 반복
		int popped_vertex = Pop(s); //스택에서 정점을 하나 꺼내서
		if (!visited[popped_vertex]) { //만약 꺼낸 정점이 아직 방문이 안되었다면
			visited[popped_vertex] = TRUE; //방문 표시
			printf("정점 %d -> ", popped_vertex); //방문한 정점 출력
			GraphNode* w; //정점 w
			for (w = g->adjList[popped_vertex]; w != NULL; w = w->link) {//꺼낸 정점의 인접 정점 탐색(연결리스트 순회)
				if (!visited[w->vertex]) //인접정점인 w를 아직 방문하지 않았다면
					Push(s, w->vertex);//스택에 삽입(꺼낸 정점의 모든 인접 정점을 스택에 삽입한다)
			}
		}
	}
	//스택 사용이 끝나면 삭제
	DestroyStack(&s);
}
