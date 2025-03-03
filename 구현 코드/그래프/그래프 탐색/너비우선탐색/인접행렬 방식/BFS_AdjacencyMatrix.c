//무방향 그래프, 인접행렬 방식으로 구현
//2차원 배열 사용
//BFS 알고리즘(원형 큐 사용)
#include "BFS_AdjacencyMatrix.h"

void Error(char* message) {
	fprintf(stderr, "%s\n", message);
	exit(EXIT_FAILURE);
}
/*-----큐 관련 함수-----*/
QueueType* CreateQueue() { //큐 구조체를 생성하고 초기화하여 반환
	QueueType* q = (QueueType*)malloc(sizeof(QueueType));
	if (!q) Error("memory allocation failed.");
	q->front = q->rear = 0;
	return q;
}

int IsEmpty(QueueType* q) {
	return (q->front == q->rear);
}

int IsFull(QueueType* q) {
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

void Enqueue(QueueType* q, ElementType data) {
	if (IsFull(q)) Error("Queue is full.");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->queue[q->rear] = data;
}

ElementType Dequeue(QueueType* q) {
	if (IsEmpty(q)) Error("Queue is empty.");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->queue[q->front];
}

void DestroyQueue(QueueType** q) {
	if (*q == NULL) return;
	free(*q);
	*q = NULL;
}
/*----------------------*/
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

void Init() { //visited 배열을 모두 0(FALSE)로 초기화
	for (int i = 0; i < MAX_VERTICES; i++) {
		visited[i] = FALSE;
	}
}

void BFS_mat(GraphType* g, int v) {//인접 행렬로 표현된 그래프에 대한 너비 우선 탐색(시작정점: v)
	visited[v] = TRUE; //정점 v 방문 표시
	printf("정점 %d -> ", v); //방문한 정점 출력
	QueueType* q = CreateQueue(); //정점들을 저장할 큐 생성
	Enqueue(q, v); //시작 정점을 큐에 삽입해놓고 시작
	while (!IsEmpty(q)) {//큐가 빌때까지 반복
		int popped_vertex = Dequeue(q); //큐에서 정점을 하나 꺼내서
		int w; //정점 w
		for (w = 0; w < g->totalVertices; w++) { //꺼낸 정점의 인접정점 탐색
			if (g->adjMat[popped_vertex][w] && !visited[w]) { //인접정점 w가 아직 방문되지 않았다면
				visited[w] = TRUE; //방문표시 후
				printf("정점 %d -> ", w);
				Enqueue(q, w); //방문한 정점을 큐에 삽입(큐에서 꺼낸 정점의 인접 정점들을 모두 방문하고 큐에 삽입한다)
			}
		}
	}
	//사용이 끝나면 큐 삭제
	DestroyQueue(&q);
}
