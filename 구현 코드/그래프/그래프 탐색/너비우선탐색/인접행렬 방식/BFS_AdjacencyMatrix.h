#ifndef BFS_ADJACENCYMATRIX_H
#define BFS_ADJACENCYMATRIX_H

#include <stdio.h>
#include <stdlib.h>

#define FALSE 0
#define TRUE 1
#define MAX_VERTICES 100 //정점 최대 개수
#define MAX_QUEUE_SIZE 100

typedef struct {//그래프 구조체
	int totalVertices;//정점의 개수
	int adjMat[MAX_VERTICES][MAX_VERTICES];//인접 행렬
}GraphType;

typedef int ElementType;

typedef struct {
	int front, rear;
	ElementType queue[MAX_QUEUE_SIZE];
}QueueType;

int visited[MAX_VERTICES]; //정점 방문 표시할 배열

void Error(char* message);
/*-----큐 관련 함수-----*/
QueueType* CreateQueue();
int IsEmpty(QueueType* q);
int IsFull(QueueType* q);
void Enqueue(QueueType* q, ElementType data);
ElementType Dequeue(QueueType* q);
void DestroyQueue(QueueType** q);
/*----------------------*/
GraphType* CreateGraph();
void InsertVertex(GraphType* g, int v);
void InsertEdge(GraphType* g, int u, int v);
void Print_adjMat(GraphType* g);
void DestroyGraph(GraphType** g);
void Init();
void BFS_mat(GraphType* g, int v);

#endif
