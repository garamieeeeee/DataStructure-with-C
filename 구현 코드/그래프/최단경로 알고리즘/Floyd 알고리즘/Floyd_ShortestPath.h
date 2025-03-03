#ifndef FLOYD_SHORTESTPATH_H
#define FLOYD_SHORTESTPATH_H

#include <stdio.h>
#include <stdlib.h>

#define FALSE 0
#define TRUE 1
#define MAX_VERTICES 50
#define INF 1000000 //무한대(두 정점간 직접 간선이 없는 경우)

int D[MAX_VERTICES][MAX_VERTICES]; //D[i][j]:i->j로 가는 최단경로의 길이
int path[MAX_VERTICES][MAX_VERTICES]; //중간지점을 저장하는 배열. path[i][j] == k라면, i에서 j로 최단경로로 갈려면 무조건 정점 k를 거쳐야 한다는 뜻

/*-----그래프 관련-----*/
typedef struct {
	int totalVertices;
	int weight[MAX_VERTICES][MAX_VERTICES]; //가중치 인접 행렬 방식
}GraphType;

GraphType* Create_Graph();
void Insert_Vertex(GraphType* g, int v);
void Insert_Edge(GraphType* g, int u, int v, int w);
void Print_Graph(GraphType* g);
/*---------------------*/
void Floyd_ShortestPath(GraphType* g);
void Print_ShortestPath(int start, int end);
void Print_Path(int i, int j);

#endif
