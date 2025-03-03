//무방향 그래프, 인접행렬 방식
//2차원 배열 사용
//DFS 알고리즘(명시적 스택 사용)

#include <stdio.h>
#include <stdlib.h>

#define FALSE 0
#define TRUE 1
#define MAX_VERTICES 100 
#define MAX_STACK_SIZE 100

typedef struct {
	int totalVertices;
	int adjMat[MAX_VERTICES][MAX_VERTICES];
}GraphType;

typedef int ElementType;
typedef struct {
	int top;
	ElementType stack[MAX_STACK_SIZE];
}StackType;

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
			Edge e;
			e.start = popped_vertex;
			e.end = -1;
			printf("정점 %d -> ", popped_vertex); //방문한 정점 출력
			int w; //정점 w
			for (w = 0; w < g->totalVertices; w++) {//꺼낸 정점의 인접 정점 탐색
				if (g->adjMat[popped_vertex][w] && !visited[w]) //인접 정점w를 아직 방문하지 않았다면
					e.end = w;
					Push(s, w); //스택에 삽입(꺼낸 정점의 모든 인접 정점을 스택에 삽입한다)
			}
			if(e.end != -1)
				spanningTree[EdgeCount++] = e; //간선 (popped_vertex, w) 저장
		}
	}
	//스택 사용이 끝나면 삭제
	DestroyStack(&s);
}

void Print_SpanninTree() { //스패닝 트리의 간선들을 출력하는 함수
	for (int i = 0; i < EdgeCount; i++) {
		printf("(%d, %d)\n", spanningTree[i].start, spanningTree[i].end);
	}
	printf("\n");
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
	DFS_mat_iterative(g, 0);//0을 시작정점으로 깊이 우선 탐색
	printf("\n");
	printf("신장트리 간선들 출력:\n");
	Print_SpanninTree();

	//그래프 삭제
	DestroyGraph(&g);

	return 0;
}
