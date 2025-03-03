#ifndef DYNAMIC_ADJACENCYMATRIX_GRAPH_H
#define DYNAMIC_ADJACENCYMATRIX_GRAPH_H

#include <stdio.h>
#include <stdlib.h>

//정점 개수 제한 없음
typedef struct {//그래프 구조체
	int totalVertices;//정점의 개수
	int** adjMat;
}GraphType;

void Error(char* message);
GraphType* CreateGraph();
void InsertVertex(GraphType* g, int v);
void InsertEdge(GraphType* g, int u, int v);
void Print_adjMat(GraphType* g);
void DestroyGraph(GraphType** g);

#endif
