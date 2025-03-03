#ifndef MINHEAP_H
#define MINHEAP_H

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
void Insert_minHeap(HeapType* h, ElementType newNode);
ElementType Delete_minHeap(HeapType* h);
void PrintHeap(HeapType* h);
void HeapSort(ElementType e[], int n);

#endif
