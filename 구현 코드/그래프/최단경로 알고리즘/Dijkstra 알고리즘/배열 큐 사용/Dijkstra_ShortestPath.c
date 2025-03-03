//Dijkstra 최단경로 알고리즘
//우선순위 큐로 배열(distance) 사용
#include "Dijkstra_ShortestPath.h"

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

//아직 S에 포함되지 않은 정점들 중에서 distance 값이 최소인 정점을 찾아 반환하는 함수
int Find_ShortestVertex(int n) { //n: 그래프의 정점 개수
	int minDist = INT_MAX; //비교를 통해 찾을 distance의 최솟값. 초깃값은 최대한 큰 수로 설정
	int minVertex = -1;//최단거리 정점을 저장

	for (int i = 0; i < n; i++) {
		if (!included[i]) { //아직 S에 포함되지 않은 정점들에 대하여
			if (distance[i] < minDist) {
				minDist = distance[i]; //최소 distance값 업데이트
				minVertex = i; //최단거리 정점 업데이트
			}
		}
	}
	return minVertex; //만약 S에 이미 모든 정점이 다 포함되어있다면, -1 반환
}

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

	//distance[], included[], prev[] 초기화
	for (int i = 0; i < g->totalVertices; i++) {
		//distance[i]의 초깃값: 시작정점과 정점i를 연결하는 간선의 가중치(인접정점이 아니라면 INF)
		distance[i] = g->weight[start][i];
		included[i] = FALSE;
		//prev[i]: S안에서 정점 i와 가장 가까운 정점. 정점 i가 시작정점 start와 인접정점이라면 prev[i]의 초깃값은 start
		//i가 시작정점과 인접정점이 아니라면 prev[i]는 -1로 초기화(start에서 정점i까지 가는 경로가 전혀 없을수도 있기때문)
		prev[i] = (distance[i] != INF) ? start : -1;
	}

	included[start] = TRUE; //시작정점 방문표시
	distance[start] = 0; //시작정점의 distance값은 0

	printf("----------------Dijkstra 알고리즘----------------\n");
	for (int i = 0; i < g->totalVertices - 1; i++) {//정점이 n개라면, 시작정점을 제외하고 n-1번의 작업을 해야한다.
		u = Find_ShortestVertex(g->totalVertices); //시작정점으로부터의 최단거리 정점을 찾아 u에 저장
		included[u] = TRUE; //u를 집합 S에 추가
		printf("시작정점 %d에서 %d까지의 최단거리를 찾았습니다: %d\n", start, u, distance[u]);

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
}
