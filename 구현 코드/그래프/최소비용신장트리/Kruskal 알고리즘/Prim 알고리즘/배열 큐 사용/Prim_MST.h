#ifndef PRIM_MST_H
#define PRIM_MST_H

#include <stdio.h>
#include <stdlib.h>

#define FALSE 0
#define TRUE 1
#define MAX_VERTICES 50
#define INF 1000l //INF: 무한대

typedef struct { //그래프 구조체: 인접 행렬 방식으로 그래프 저장
	int totalVertices;
	int weight[MAX_VERTICES][MAX_VERTICES];
	//weight[u][v]: 간선(u, v)의 가중치. weight[u][v] == INF이면 u->v로 바로 가는 간선이 없다는 뜻
}GraphType;

//현재까지 완성된 MST에 포함된 정점들을 저장
//selectedVertices[i] == TRUE이면 정점 i는 이미 MST에 포함되어있다는 뜻
int selectedVertices[MAX_VERTICES];
//현재까지 완성된 MST에 포함된 정점들에서 정점i까지 가는 최소거리를 저장
int distance[MAX_VERTICES];

/*-----그래프 기본함수-----*/
GraphType* CreateGraph();
void InsertVertex(GraphType* g, int v);
void InsertEdge(GraphType* g, int u, int v, int w);
void PrintGraph(GraphType* g);
/*-------------------------*/
int GetMinVertex(int n);
int BuildMST(GraphType* g, int order[], GraphType* mst);
GraphType* Prim_MST(GraphType* g, int s);

#endif
