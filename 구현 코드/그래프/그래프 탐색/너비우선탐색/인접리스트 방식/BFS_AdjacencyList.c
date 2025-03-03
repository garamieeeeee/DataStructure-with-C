//무방향 그래프, 인접 리스트 방식으로 구현
//1차원 배열 + 연결리스트 사용
//BFS 알고리즘(원형 큐 사용)
#include "BFS_AdjacencyList.h"

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
	for (int i = 0; i < MAX_VERTICES; i++) {
		g->adjList[i] = NULL;
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
	free(*g);
	*g = NULL;
}

void Init() { //visited 배열을 모두 0(FALSE)로 초기화
	for (int i = 0; i < MAX_VERTICES; i++) {
		visited[i] = FALSE;
	}
}

void BFS_list(GraphType* g, int v) {//인접 리스트로 표현된 그래프에 대한 너비 우선 탐색(시작정점: v)
	visited[v] = TRUE; //정점 v 방문 표시
	printf("정점 %d -> ", v); //방문한 정점 출력
	QueueType* q = CreateQueue(); //정점들을 저장할 큐 생성
	Enqueue(q, v); //시작 정점인 v를 우선 큐에 삽입해놓고 시작
	while (!IsEmpty(q)) {//큐가 빌때까지 반복
		int popped_vertex = Dequeue(q); //큐에서 정점을 하나 꺼내서
		GraphNode* w; //정점 w
		for (w = g->adjList[popped_vertex]; w != NULL; w = w->link) { //꺼낸 정점의 인접 정점들을 탐색한다(연결리스트 순회)
			if (!visited[w->vertex]) { //인접정점 w를 방문하지 않았다면
				visited[w->vertex] = TRUE; //w 방문 표시하고
				printf("정점 %d -> ", w->vertex);
				Enqueue(q, w->vertex); //방문한 정점을 큐에 삽입(큐에서 꺼낸 정점의 인접 정점들을 모두 방문하고 큐에 삽입한다)
			}
		}
	}
	//사용이 끝났으면 큐 삭제
	DestroyQueue(&q);
}
