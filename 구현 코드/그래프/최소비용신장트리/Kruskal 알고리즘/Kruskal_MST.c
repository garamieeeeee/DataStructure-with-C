//Kruskal의 MST 알고리즘
//간선 정렬을 위해 qsort를 사용하였다
#include "Kruskal_MST.h"

/*-----union & find 알고리즘-----*/
void InitSet(int n) {//집합들의 parent 배열값을 초기화(n: 노드의 개수)
	for (int i = 0; i < n; i++)
		parent[i] = i;
}

int FindSet(int x) { //x가 속한 집합의 루트노드를 반환
	if (parent[x] == x) return x;
	return parent[x] = FindSet(parent[x]); //경로 압축 사용
}

void MergeSet(int x, int y) {//x가 속한 집합과 y가 속한 집합을 합친다.
	int root1 = FindSet(x);
	int root2 = FindSet(y);

	if (root1 != root2)
		parent[root1] = root2; //x의 집합을 y의 집합에 붙인다.
}
/*-------------------------------*/

/*-----그래프 기본 함수-----*/
GraphType* CreateGraph() { //그래프 구조체 생성하고 초기화하여 반환
	GraphType* g = (GraphType*)malloc(sizeof(GraphType));
	if (!g) {
		fprintf(stderr, "memory allocation failed.\n");
		exit(EXIT_FAILURE);
	}
	g->totalVertices = g->totalEdges = 0;
	for (int i = 0; i < 2 * MAX_VERTICES; i++) {
		g->edges[i].start = g->edges[i].end = 0;
		g->edges[i].weight = INF;
	}
	return g;
}

void InsertVertex(GraphType* g, int v) {
	if (g->totalVertices + 1 > MAX_VERTICES) {
		fprintf(stderr, "The number of vertices has exceeded.\n");
		return;
	}
	g->totalVertices++;//간선 삽입
}

void InsertEdge(GraphType* g, int u, int v, int w) {//간선 (u, v)을 그래프 g에 삽입. w는 간선의 가중치
	if (u >= g->totalVertices || v >= g->totalVertices) {
		fprintf(stderr, "vertex number error.\n");
		return;
	}
	//간선 삽입
	g->edges[g->totalEdges].start = u;
	g->edges[g->totalEdges].end = v;
	g->edges[g->totalEdges].weight = w;
	//간선 개수 += 1
	g->totalEdges++;
}

void PrintGraph(GraphType* g) { //그래프의 간선들을 모두 출력한다.
	for (int i = 0; i < g->totalEdges; i++)
		printf("간선 (%d, %d), 가중치: %d\n", g->edges[i].start, g->edges[i].end, g->edges[i].weight);
	printf("\n\n");
}
/*--------------------------*/

int Compare(const void* a, const void* b) { //간선들을 정렬하기 위해 qsort를 할때 쓰는 기준함수
	//형변환
	Edge* x = (Edge*)a;
	Edge* y = (Edge*)b;
	//간선들이 가중치의 오름차순으로 정렬된다.
	return (x->weight - y->weight);
}
//kruskal의 MST 알고리즘(간선 선택 알고리즘)
GraphType* Kruskal_MST(GraphType* g) {//그래프 g의 최소신장트리를 만들어 반환한다
	//신장트리를 만들기 위한 그래프 생성, 초기화
	GraphType* mst = CreateGraph();
	mst->totalVertices = g->totalVertices;

	//정점 집합들을 초기화한다
	InitSet(g->totalVertices);

	//1. 간선들을 가중치의 오름차순으로 정렬한다.
	qsort(g->edges, g->totalEdges, sizeof(Edge), Compare);

	//2. 정렬된 간선들을 차례로 검사하여 사이클을 형성하는지 확인한다
	//사이클을 형성하지 않을때에만 해당 간선을 선택하여 MST 집합에 추가한다.
	int acceptedEdges = 0; //현재까지 선택된 간선들의 개수
	int totalWeight = 0; //MST의 간선들의 가중치 총합 저장
	int i = 0;
	printf("-----Kruskal MST 알고리즘-----\n");
	while (acceptedEdges < g->totalVertices - 1) { //선택한 간선의 개수가 정점개수-1과 같아지면 간선 추가를 중지한다.
		Edge e = g->edges[i]; //간선들을 차례로 검사
		int Uset = FindSet(e.start);
		int Vset = FindSet(e.end);
		if (Uset != Vset) {
			//정점 U가 속한 집합과 정점 V가 속한 집합이 다르다면:
			//간선 (U, V)는 사이클을 형성하지 않으므로 간선 (U, V)를 MST에 추가한다.
			printf("간선 (%d, %d) 선택: 가중치 %d\n", e.start, e.end, e.weight);
			InsertEdge(mst, e.start, e.end, e.weight);
			acceptedEdges++;
			totalWeight += e.weight;

			MergeSet(Uset, Vset); //간선 (U,V)를 선택했으므로 정점 U,V는 같은 집합에 속하게 됨
		}
		i++;
	}
	printf("------------------------------\n");
	printf("mst 트리의 가중치 총합: %d\n\n", totalWeight);
	return mst;
}
