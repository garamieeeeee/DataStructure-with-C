//Dijkstra 최단경로 알고리즘
//우선순위 큐를 최소힙으로 구현
#include "Dijkstra_ShortestPath_with_queue.h"

GraphType* Create_Graph() {
	GraphType* g = (GraphType*)malloc(sizeof(GraphType));
	if (!g) {
		fprintf(stderr, "memory allocation failed.\n");
		exit(EXIT_FAILURE);
	}
	g->totalVertices = 0;
	for (int i = 0; i < MAX_VERTICES; i++) {
		for (int j = 0; j < MAX_VERTICES; j++) {
			if (i == j) g->weight[i][j] = 0;
			else g->weight[i][j] = INF;
		}
	}
	return g;
}

void Insert_Vertex(GraphType* g, int v) {
	if (g->totalVertices + 1 > MAX_VERTICES) {
		fprintf(stderr, "The number of vertices has exceeded.\n");
		return;
	}
	g->totalVertices++;
}

void Insert_Edge(GraphType* g, int u, int v, int w) {
	if (u >= g->totalVertices || v >= g->totalVertices) {
		fprintf(stderr, "vertex number error.\n");
		return;
	}
	g->weight[u][v] = w;
	g->weight[v][u] = w;
}

void Print_Graph(GraphType* g) {
	for (int i = 0; i < g->totalVertices; i++) {
		for (int j = 0; j < g->totalVertices; j++) {
			if (g->weight[i][j] == INF) printf(" - ");
			else printf("%2d ", g->weight[i][j]);
		}
		printf("\n");
	}
	printf("\n\n");
}
/*---------------------*/

/*-----최소 힙 관련-----*/
MinHeapType* Create_Heap() {
	MinHeapType* h = (MinHeapType*)malloc(sizeof(MinHeapType));
	if (!h) {
		fprintf(stderr, "memory allocation failed.\n");
		exit(EXIT_FAILURE);
	}
	h->heapSize = 0;
	return h;
}

void Insert_MinHeap(MinHeapType* h, Node node) {
	h->heapSize++;
	int i = h->heapSize;
	while ((i != 1) && (node.key < h->heap[i / 2].key)) {
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i] = node;
}

Node Extract_MinHeap(MinHeapType* h) { //최솟값을 삭제해 반환하는 함수(distance 값을 key로 하여 최소정점을 반환한다!!)
	Node removed = h->heap[1];
	Node temp = h->heap[h->heapSize];
	h->heapSize--;

	int p = 1; //p: 부모노드를 가리킴
	int c = 2; //c: 자식노드를 가리킴
	while (c <= h->heapSize) {
		if ((c < h->heapSize) && (h->heap[c].key > h->heap[c + 1].key))
			c++;
		if (temp.key <= h->heap[c].key) break;
		h->heap[p] = h->heap[c];
		p = c;
		c *= 2;
	}
	h->heap[p] = temp;
	return removed;
}

int IsEmpty(MinHeapType* h) { //힙이 비어있는지 여부를 리턴
	return (h->heapSize == 0);
}
/*----------------------*/

//Dijkstra 알고리즘을 수행하면서 저장한 prev 배열을 이용해
//시작정점 start에서 정점 v까지 가는 경로를 역추적한 후, 전체 경로를 출력함
void Print_ShortestPath(int start, int v) {
	if (distance[v] == INF) { //start->v로 가는 경로가 전혀 없는 경우(예외처리)
		printf("시작정점 %d에서 %d까지 가는 경로가 존재하지 않음.\n", start, v);
		return;
	}

	int path[MAX_VERTICES]; //start->v까지의 경로를 기록할 배열
	int j = 0;

	path[j++] = v;
	while (v != start) {
		v = prev[v];
		path[j++] = v;
	}
	//path 배열에는 start->v까지의 최단거리 경로가 역순으로 저장되어 있음
	for (int i = j - 1; i >= 0; i--) {
		if (i == 0) printf("%d\n", path[i]);
		else printf("%d -> ", path[i]);
	}
}

//다익스트라 최단경로 알고리즘
//시작정점 start에서부터 다른 모든 정점까지의 최단거리를 구하는 함수
void Dijkstra_shortestPath(GraphType* g, int start) {
	int u, w;//정점 u,w
	MinHeapType* h = Create_Heap(); //정점들을 저장할 우선순위 큐(최소힙. distance가 작을수록 우선순위가 높음)

	//distance[], included[], prev[] 초기화
	for (int i = 0; i < g->totalVertices; i++) {
		//distance[i]의 초깃값: 시작정점과 정점i를 연결하는 간선의 가중치(인접정점이 아니라면 INF)
		distance[i] = g->weight[start][i];
		included[i] = FALSE;
		//prev[i]: S안에서 정점 i와 가장 가까운 정점. 정점 i가 시작정점 start와 인접정점이라면 prev[i]의 초깃값은 start
		//i가 시작정점과 인접정점이 아니라면 prev[i]는 -1로 초기화(start에서 정점i까지 가는 경로가 전혀 없을수도 있기때문)
		prev[i] = (distance[i] != INF) ? start : -1;
	}

	distance[start] = 0; //시작정점의 distance값은 0
	Node node = { start, distance[start] };
	Insert_MinHeap(h, node); //시작정점을 큐에 삽입해놓고 반복문 시작

	printf("----------------Dijkstra 알고리즘----------------\n");
	while (!IsEmpty(h)) {//큐가 빌때까지 반복
		u = Extract_MinHeap(h).vertex; //큐에서 (시작정점으로부터의) 최단거리 정점을 꺼내 u에 저장한다

		if (included[u]) continue; //u가 이미 집합 S에 포함되어있다면 이미 최단경로를 찾은 것이므로, 다시한번 큐에서 정점을 꺼낸다.
		included[u] = TRUE; //u를 집합 S에 추가
		if (u != start) printf("시작정점 %d에서 %d까지의 최단거리를 찾았습니다: %d\n", start, u, distance[u]);

		//S에 u가 새롭게 추가되었으므로, S에 포함되지 않은 정점들의 distance 값을 업데이트
		for (w = 0; w < g->totalVertices; w++) {
			if (!included[w]) { //아직 S에 포함되지 않은 정점들에 대하여
				if (distance[w] > distance[u] + g->weight[u][w]) {
					//새로 추가된 정점 u를 거쳐서 w까지 가는 거리가 더 가깝다면
					//w의 distance를 업데이트
					distance[w] = distance[u] + g->weight[u][w];
					//이제 (S안에서) w와 가장 가까운 정점은 u
					prev[w] = u;
				}
				//w의 distance를 업데이트 하고나서(또는 하지 않더라도)
				//w의 distance값이 INF가 아니라면. 즉 시작정점에서 w까지 가는 경로가 존재한다면
				if (distance[w] != INF) {
					//정점 w를 큐에 삽입한다.
					node.vertex = w; node.key = distance[w];
					Insert_MinHeap(h, node);
				}
			}
		}
	}
	printf("-------------------------------------------------\n");

	//시작정점에서 다른 모든 정점까지의 최단거리 경로를 출력한다
	for (int i = 0; i < g->totalVertices; i++) {
		if (i != start) {
			printf("시작정점 %d에서 %d까지 가는 최단거리 경로: \n", start, i);
			Print_ShortestPath(start, i);
		}
	}

	//힙 사용이 끝나면 삭제
	free(h);
}
