#ifndef DFS_ADJACENCYMATRIX_WITH_STACK
#define DFS_ADJACENCYMATRIX_WITH_STACK

#include <stdio.h>
#include <stdlib.h>

#define FALSE 0
#define TRUE 1
#define MAX_VERTICES 100 
#define MAX_STACK_SIZE 100

typedef struct {
	int totalVertices;
	int adjMat[MAX_VERTICES][MAX_VERTICES];
}GraphType;

typedef int ElementType;
typedef struct {
	int top;
	ElementType stack[MAX_STACK_SIZE];
}StackType;

int visited[MAX_VERTICES]; //정점 방문 표시할 배열

void Error(char* message);
/*-----스택 관련 함수-----*/
StackType* CreateStack();
int IsEmpty(StackType* s);
int IsFull(StackType* s);
void Push(StackType* s, ElementType data);
ElementType Pop(StackType* s);
void DestroyStack(StackType** s);
/*------------------------*/
GraphType* CreateGraph();
void InsertVertex(GraphType* g, int v);
void InsertEdge(GraphType* g, int u, int v);
void Print_adjMat(GraphType* g);
void DestroyGraph(GraphType** g);
void Init();
void DFS_mat_iterative(GraphType* g, int v);

#endif
