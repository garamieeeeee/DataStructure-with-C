#ifndef KRUSKAL_MST_H
#define KRUSKAL_MST_H

#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 50 //최대 정점 수
int parent[MAX_VERTICES]; //각 노드의 부모노드를 저장해둔 배열(union-find 알고리즘에 사용)

#define INF 1000 //INF: 무한대
typedef struct {//간선 구조체: (시작 정점, 종료 정점)과 가중치 정보를 갖고있음
	int start, end; //간선의 시작 정점, 종료 정점
	int weight; //가중치
}Edge;

typedef struct { //그래프 구조체: 그래프는 간선들의 집합으로 표현됨
	int totalVertices, totalEdges; //그래프의 정점, 간선 개수
	Edge edges[2 * MAX_VERTICES]; //간선들의 집합(정점 당 2개씩 간선을 가진다고 치고 최대 2*MAX_VERTICES 개의 간선을 가질 수 있도록 함
}GraphType;

/*-----union & find 알고리즘-----*/
void InitSet(int n);
int FindSet(int x);
void MergeSet(int x, int y);
/*-------------------------------*/
/*-----그래프 기본 함수-----*/
GraphType* CreateGraph();
void InsertVertex(GraphType* g, int v);
void InsertEdge(GraphType* g, int u, int v, int w);
void PrintGraph(GraphType* g);
/*--------------------------*/
int Compare(const void* a, const void* b);
GraphType* Kruskal_MST(GraphType* g);

#endif
