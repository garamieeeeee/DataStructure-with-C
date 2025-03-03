//Prim의 MST 알고리즘
//우선순위 큐를 배열(distance)로 구현함
#include "Prim_MST.h"

/*-----그래프 기본함수-----*/
GraphType* CreateGraph() {
	GraphType* g = (GraphType*)malloc(sizeof(GraphType));
	if (!g) {
		fprintf(stderr, "memory allocation failed.\n");
		exit(EXIT_FAILURE);
	}
	g->totalVertices = 0;
	for (int i = 0; i < MAX_VERTICES; i++) {
		for (int j = 0; j < MAX_VERTICES; j++) {
			if (i == j) g->weight[i][j] = 0; //자기 자신을 가리키는 간선의 가중치는 0으로 표시 
			else g->weight[i][j] = INF;
		}
	}
	return g;
}

void InsertVertex(GraphType* g, int v) {
	if (g->totalVertices + 1 > MAX_VERTICES) {
		fprintf(stderr, "The number of vertices has exceeded.\n");
		return;
	}
	g->totalVertices++; //정점 삽입
}

void InsertEdge(GraphType* g, int u, int v, int w) {//간선 (u,v) 삽입. w는 간선의 가중치
	if (u >= g->totalVertices || v >= g->totalVertices) {
		fprintf(stderr, "vertex number error.\n");
		return;
	}
	//간선 삽입
	g->weight[u][v] = w;
	g->weight[v][u] = w;
}

void PrintGraph(GraphType* g) {
	for (int i = 0; i < g->totalVertices; i++) {
		for (int j = 0; j < g->totalVertices; j++) {
			if (g->weight[i][j] == INF) printf(" - ");
			else printf("%2d ", g->weight[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}
/*-------------------------*/

//현재 MST에 포함된 정점들과 인접한 정점들 중 가중치가 최소인 정점을 반환함(n: 그래프의 정점 개수)
//더 이상 인접한 정점을 찾을 수 없다면,즉 모든 정점을 다 MST에 추가했다면 -1을 반환
int GetMinVertex(int n) {
	int v = -1; //정점 v (초기값은 -1)
	for (int i = 0; i < n; i++) {
		if (!selectedVertices[i]) { //아직 MST에 추가되지 않은 정점을 골라 v에 저장한다.
			v = i;
			break;
		}
	}
	//v가 최소정점인지를 확인해야한다.
	//즉 아직 선택되지 않은 다른 정점들과 distance 값을 비교해야함
	for (int i = 0; i < n; i++) {
		if (!selectedVertices[i] && (distance[i] < distance[v])) {
			//distance가 더 적은 정점이 있다면 v에 저장
			v = i;
		}
	}
	//v는 최소정점임(최소거리 노드)
	//만약 그래프의 모든 정점을 MST에 추가했다면, for문을 거치지 않고 그냥 -1을 그대로 반환함
	return v;
}

//배열 order에는 그래프 g의 정점이 Prim 알고리즘에서 선택한 순서대로 저장되어있다
//order 배열을 이용해서 MST를 구성한다.
//mst의 간선들의 가중치 총합을 계산하여 반환한다.
int BuildMST(GraphType* g, int order[], GraphType* mst) {
	mst->totalVertices = g->totalVertices;
	//order[]: 0,5,4,3,2,1,6이면 mst의 간선은 (0,5), (5,4),(4,3),(3,2),(2,1),(1,6)
	//mst의 간선은 정점개수-1
	int n = mst->totalVertices - 1;
	int totalWeight = 0;
	for (int i = 0; i < n; i++) {
		int u = order[i];
		int v = order[i + 1];
		int w = g->weight[u][v];
		if (w != INF) {//혹시나 잘못된 값이 들어가는 것을 반지
			InsertEdge(mst, u, v, w); //mst에 간선 추가
			totalWeight += w; //mst의 간선들의 가중치 총합 갱신
		}
	}
	return totalWeight;
}

//그래프 g의 최소신장트리를 만들어 반환한다. (s: 시작정점)
//MST에 정점을 추가할때마다 출력한다.
GraphType* Prim_MST(GraphType* g, int s) {
	int u, v;//정점 u, v
	int order[MAX_VERTICES]; //Prim 알고리즘을 수행하면서 선택한 정점들을 차례로 저장할 배열

	//distance와 selectedVertices 배열 초기화
	for (int i = 0; i < g->totalVertices; i++) {
		distance[i] = INF;
		selectedVertices[i] = FALSE;
	}
	//시작정점 s의 distance값은 0
	distance[s] = 0;

	int j = 0;
	printf("-----Prim MST 알고리즘-----\n");
	for (int i = 0; i < g->totalVertices; i++) {
		u = GetMinVertex(g->totalVertices); //최소정점을 찾아 u에 저장

		//GetMinVertex의 반환값이 -1이라는 것은 MST에 모든 정점을 추가했다는 뜻이므로, 정점 추가를 종료한다.
		if (u == -1) break;

		selectedVertices[u] = TRUE; //최소정점 u를 MST에 추가했다고 표시
		order[j++] = u; //order에 정점u 기록
		printf("정점 %d를 MST에 추가\n", u); //추가한 정점 출력

		//이제 정점u가 MST에 새롭게 추가되었으므로, u의 인접정점들의 distance값을 업데이트 해줘야 함
		for (v = 0; v < g->totalVertices; v++) {//u의 모든 인접정점을 검사
			//아직 MST에 추가되지 않은 정점 v에 대하여
			// 기존의 MST에서 v까지의 거리보다, 새롭게 MST에 추가된 u에서 v까지의 거리가 더 가깝다면
			if (!selectedVertices[v] && g->weight[u][v] < distance[v])
				distance[v] = g->weight[u][v]; //v의 distance 값을 u->v의 거리로 업데이트
		}
	}
	printf("---------------------------\n");

	//order 배열을 근거로 mst를 구성한다
	GraphType* mst = CreateGraph();
	int totalWeight = BuildMST(g, order, mst);

	printf("mst 트리의 가중치 총합: %d\n\n", totalWeight);

	return mst;
}
