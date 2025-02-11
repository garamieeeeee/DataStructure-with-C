#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>

#define MAX_ELEMENT 100

typedef struct {
	int key;
}ElementType;

typedef struct {
	ElementType heap[MAX_ELEMENT];
	int heapSize;
}HeapType;

HeapType* CreateHeap();
void Insert_minHeap(HeapType* h, ElementType newNode);
ElementType Delete_minHeap(HeapType* h);
void PrintHeap(HeapType* h);
HeapType* ReadFile(const char* fileName);

int main(int argc, char* argv[]) {
	//input파일을 읽어 힙트리 구성
	HeapType* h = ReadFile(argv[1]);
	//힙트리 출력
	PrintHeap(h);

	return 0;
}

HeapType* CreateHeap() {
	HeapType* h = (HeapType*)malloc(sizeof(HeapType));
	if (!h) {
		fprintf(stderr, "memory allocation failed.\n");
		exit(EXIT_FAILURE);
	}
	h->heapSize = 0;
	return h;
}

void Insert_minHeap(HeapType* h, ElementType newNode) {
	h->heapSize++;
	int i = h->heapSize;

	while ((i != 1) && (newNode.key < h->heap[i / 2].key)) {
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}

	h->heap[i] = newNode;
}

ElementType Delete_minHeap(HeapType* h) {
	ElementType removed = h->heap[1];
	ElementType temp = h->heap[h->heapSize];
	h->heapSize--;

	int parent = 1;
	int child = 2;

	while ((child <= h->heapSize)) {
		if (child < h->heapSize && h->heap[child].key > h->heap[child + 1].key) {
			child++;
		}
		if (temp.key <= h->heap[child].key) break;
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;
	return removed;
}

void PrintHeap(HeapType* h) {
	for (int i = 1; i <= h->heapSize; i++) {
		printf("[%d] %d ", i, h->heap[i]);
	}
}

HeapType* ReadFile(const char* fileName) {//input파일을 읽어 힙트리를 구성함
	FILE* file = fopen(fileName, "r");
	if (!file) {
		fprintf(stderr, "file open failed.\n");
		exit(EXIT_FAILURE);
	}

	int n; //n: total number of data
	fscanf(file, "%d", &n);

	HeapType* h = CreateHeap();
	ElementType data;
	while (fscanf(file, " %d", &data) != EOF) {
		Insert_minHeap(h, data);
	}

	fclose(file);

	return h;
}
