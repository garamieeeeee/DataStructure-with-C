#include "Dynamic_AdjacencyMatrix_graph.h"

void test() {
	GraphType* g = CreateGraph();
	//정점 삽입(0,1,2,3)
	for (int i = 0; i < 4; i++) {
		InsertVertex(g, i);
	}
	//간선 (0,1) 삽입
	InsertEdge(g, 0, 1);
	//간선 (0,2) 삽입
	InsertEdge(g, 0, 2);
	//간선 (0,3) 삽입
	InsertEdge(g, 0, 3);
	//간선 (1,2) 삽입
	InsertEdge(g, 1, 2);
	//간선 (2,3) 삽입
	InsertEdge(g, 2, 3);

	//그래프 출력
	Print_adjMat(g);

	//그래프 삭제
	DestroyGraph(&g);
}

int main() {
	test();
	return 0;
}
