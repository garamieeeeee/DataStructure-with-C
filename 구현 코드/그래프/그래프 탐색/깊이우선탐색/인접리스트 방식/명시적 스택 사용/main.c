#include "DFS_AdjacencyList_with_stack.h"

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
	Print_adjList(g);

	//dfs
	Init(); //visited 배열 FALSE로 초기화
	printf("<< 깊이 우선 탐색 >>\n");
	DFS_list_iterative(g, 0);//0을 시작정점으로 깊이 우선 탐색
	printf("\n");

	//그래프 삭제
	DestroyGraph(&g);
}

int main() {
	test();
	return 0;
}
