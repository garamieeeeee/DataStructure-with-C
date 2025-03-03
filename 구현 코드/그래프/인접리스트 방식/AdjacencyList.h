#ifndef ADJACENCYLIST_GRAPH_H
#define ADJACENCYLIST_GRAPH_H

#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100 //정점 최대 개수
typedef struct GraphNode {
	int vertex; //정점 번호
	struct GraphNode* link;
}GraphNode; //(정점)연결리스트의 노드 구조체

typedef struct {//그래프 구조체
	int totalVertices;
	GraphNode* adjList[MAX_VERTICES]; //연결리스트를 가리키는 포인터 배열
}GraphType;

void Error(char* message);
GraphType* CreateGraph();
void InsertVertex(GraphType* g, int v);
void InsertEdge(GraphType* g, int u, int v);
void Print_adjList(GraphType* g);
void DestroyGraph(GraphType** g);

#endif
