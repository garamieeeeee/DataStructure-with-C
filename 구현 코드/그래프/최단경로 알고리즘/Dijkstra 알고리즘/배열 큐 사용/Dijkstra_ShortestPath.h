#ifndef DIJKSTRA_SHORTESTPATH_H
#define DIJKSTRA_SHORTESTPATH_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define FALSE 0
#define TRUE 1
#define MAX_VERTICES 50
#define INF 1000000

int distance[MAX_VERTICES]; //distance[i]: 시작정점으로부터 현재 S에 속한 정점들만 거쳐서 정점 i로 가는 최단거리
int included[MAX_VERTICES]; //방문한 정점 표시(included[i]==TRUE이면 정점 i는 이미 최단경로가 발견되어 S에 포함되었다는 뜻)
int prev[MAX_VERTICES]; //최단경로를 추적하기위한 배열. prev[i]: 정점 i와 가장 가까운 정점

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
int Find_ShortestVertex(int n);
void Print_ShortestPath(int start, int v);
void Dijkstra_shortestPath(GraphType* g, int start);

#endif
