#ifndef MAXHEAP_H
#define MAXHEAP_H

#include <stdio.h>
#include <stdlib.h>

#define MAX_ELEMENT 200

typedef struct {//힙 트리 노드의 요소type
	int key;
}ElementType;

typedef struct { //힙 구조체 
	ElementType heap[MAX_ELEMENT];
	int heapSize;
}HeapType;

HeapType* CreateHeap();
void Insert_maxHeap(HeapType* h, ElementType newNode);
ElementType Delete_maxHeap(HeapType* h);
void PrintHeap(HeapType* h);
void HeapSort(ElementType e[], int n);

#endif
