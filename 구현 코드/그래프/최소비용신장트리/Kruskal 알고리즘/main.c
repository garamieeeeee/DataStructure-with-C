#include "Kruskal_MST.h"

void test() {
	GraphType* g = CreateGraph();
	////그래프 구성
	//정점 삽입(0,1,2,3,4,5,6)
	for (int i = 0; i < 7; i++)
		InsertVertex(g, i);
	//간선 삽입
	InsertEdge(g, 0, 1, 29);
	InsertEdge(g, 1, 2, 16);
	InsertEdge(g, 2, 3, 12);
	InsertEdge(g, 3, 4, 22);
	InsertEdge(g, 4, 5, 27);
	InsertEdge(g, 5, 0, 10);
	InsertEdge(g, 6, 1, 15);
	InsertEdge(g, 6, 3, 18);
	InsertEdge(g, 6, 4, 25);

	//전체 그래프 g 출력
	printf("그래프 g:\n");
	PrintGraph(g);
	//그래프 g의 최소신장트리 mst를 만들어 출력
	GraphType* mst = Kruskal_MST(g);
	printf("그래프 g의 최소신장트리: \n");
	PrintGraph(mst);

	//그래프 삭제
	free(g);
	free(mst);
}

int main() {
	test();
	return 0;
}
