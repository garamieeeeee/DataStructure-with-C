#ifndef LINKEDLINEARDEQUE_H
#define LINKEDLINEARDEQUE_H

#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;

typedef struct DequeNode {
	ElementType data;
	struct DequeNode* Llink;
	struct DequeNode* Rlink;
}DequeNode;

typedef struct {
	int currentNodeCount;
	DequeNode* front;
	DequeNode* rear;
}LinkedDequeType;

void Init(LinkedDequeType* dq);
int IsEmpty(LinkedDequeType* dq);
int GetSize(LinkedDequeType* dq);
DequeNode* CreateDequeNode(ElementType data);
void AddFront(LinkedDequeType* dq, ElementType data);
void AddRear(LinkedDequeType* dq, ElementType data);
ElementType DeleteFront(LinkedDequeType* dq);
ElementType DeleteRear(LinkedDequeType* dq);
ElementType GetRear(LinkedDequeType* dq);
ElementType GetFront(LinkedDequeType* dq);
void PrintDeque(LinkedDequeType* dq);

#endif
