//무방향 그래프, 인접행렬 방식
//2차원 배열 사용
//DFS 알고리즘(명시적 스택 사용)
#include "DFS_AdjacencyMatrix_with_stack.h"

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

void DFS_mat_iterative(GraphType* g, int v) {//인접 행렬로 표현된 그래프에 대한 깊이 우선 탐색(시작정점: v)
	StackType* s = CreateStack(); //정점들을 저장할 스택 생성
	Push(s, v); //시작정점인 v를 스택에 우선 삽입
	while (!IsEmpty(s)) { //스택이 빌때까지 반복
		int popped_vertex = Pop(s); //스택에서 정점을 하나 꺼내서
		if (!visited[popped_vertex]) { //만약 꺼낸 정점이 아직 방문이 안되었다면
			visited[popped_vertex] = TRUE; //방문 표시
			printf("정점 %d -> ", popped_vertex); //방문한 정점 출력
			int w; //정점 w
			for (w = 0; w < g->totalVertices; w++) {//꺼낸 정점의 인접 정점 탐색
				if (g->adjMat[popped_vertex][w] && !visited[w]) //인접 정점w를 아직 방문하지 않았다면
					Push(s, w); //스택에 삽입(꺼낸 정점의 모든 인접 정점을 스택에 삽입한다)
			}
		}
	}
	//스택 사용이 끝나면 삭제
	DestroyStack(&s);
}
