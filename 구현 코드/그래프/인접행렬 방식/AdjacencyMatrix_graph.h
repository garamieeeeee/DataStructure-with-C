#ifndef ADJACENCTMATRIX_H
#define ADJACENCTMATRIX_H

#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100 //정점 최대 개수
typedef struct {//그래프 구조체
	int totalVertices;//정점의 개수
	int adjMat[MAX_VERTICES][MAX_VERTICES];//인접 행렬
}GraphType;

void Error(char* message);
GraphType* CreateGraph();
void InsertVertex(GraphType* g, int v);
void InsertEdge(GraphType* g, int u, int v);
void Print_adjMat(GraphType* g);
void DestroyGraph(GraphType** g);

#endif
