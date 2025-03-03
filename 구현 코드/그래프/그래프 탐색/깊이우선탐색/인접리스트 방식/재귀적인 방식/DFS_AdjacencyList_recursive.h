#ifndef DFS_ADJACENCYMATRIX_H
#define DFS_ADJACENCYMATRIX_H

#include <stdio.h>
#include <stdlib.h>

#define FALSE 0
#define TRUE 1
#define MAX_VERTICES 100 
typedef struct GraphNode {
	int vertex;
	struct GraphNode* link;
}GraphNode;

typedef struct {
	int totalVertices;
	GraphNode* adjList[MAX_VERTICES];
}GraphType;

int visited[MAX_VERTICES]; //정점 방문 표시할 배열

void Error(char* message);
GraphType* CreateGraph();
void InsertVertex(GraphType* g, int v);
void InsertEdge(GraphType* g, int u, int v);
void Print_adjList(GraphType* g);
void DestroyGraph(GraphType** g);
void Init();
void DFS_list(GraphType* g, int v);

#endif
