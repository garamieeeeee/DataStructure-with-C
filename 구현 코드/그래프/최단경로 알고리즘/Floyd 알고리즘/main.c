#include "Floyd_ShortestPath.h"

void test() {
	GraphType* g = Create_Graph();
	//정점 삽입(0,1,2,3,4,5,6)
	for (int i = 0; i < 7; i++) {
		Insert_Vertex(g, i);
	}
	//간선 삽입
	Insert_Edge(g, 0, 1, 7);
	Insert_Edge(g, 0, 4, 3);
	Insert_Edge(g, 0, 5, 10);
	Insert_Edge(g, 1, 2, 4);
	Insert_Edge(g, 1, 3, 10);
	Insert_Edge(g, 1, 4, 2);
	Insert_Edge(g, 1, 5, 6);
	Insert_Edge(g, 2, 3, 2);
	Insert_Edge(g, 3, 4, 11);
	Insert_Edge(g, 3, 5, 9);
	Insert_Edge(g, 3, 6, 4);
	Insert_Edge(g, 4, 6, 5);

	//그래프 확인
	printf("그래프 g: \n");
	Print_Graph(g);

	//플로이드 최단경로 알고리즘 실행
	Floyd_ShortestPath(g);

	Print_ShortestPath(0, 3); //0에서 3으로 가는 최단경로 출력
	Print_ShortestPath(2, 0); //2에서 0으로 가는 최단경로 출력

	//그래프 삭제
	free(g);
}

int main() {
	test();
	return 0;
}
