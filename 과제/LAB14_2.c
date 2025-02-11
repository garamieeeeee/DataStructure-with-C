#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE 20
#define MAX_ELEMENT 100

typedef struct {
	int key;
}ElementType;

typedef struct {
	ElementType heap[MAX_ELEMENT];
	int heapSize;
}HeapType;

HeapType* CreateHeap();
void Insert_maxHeap(HeapType* h, ElementType newNode);
ElementType Delete_maxHeap(HeapType* h);
void HeapSort(ElementType e[], int n);
void PrintHeap(HeapType* h);
int ReadFile(const char* fileName, ElementType array[]);

int main(int argc, char* argv[]) {
	//input파일을 읽어 배열에 저장
	ElementType array[ARRAY_SIZE];
	int n = ReadFile(argv[1], array);//n: total 노드 개수이자 배열의 크기

	//최대 힙을 이용해 array를 오름차순으로 정렬하고, max heap의 노드값을 출력
	HeapSort(array, n);

	//오름차순으로 정렬된 array 확인
	printf("오름차순 정렬: ");
	for (int i = 0; i < n; i++) {
		printf("%d ", array[i].key);
	}
	printf("\n");

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

void Insert_maxHeap(HeapType* h, ElementType newNode) {
	h->heapSize++;
	int i = h->heapSize;

	while ((i != 1) && (newNode.key > h->heap[i / 2].key)) {
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}

	h->heap[i] = newNode;
}

ElementType Delete_maxHeap(HeapType* h) {
	ElementType removed = h->heap[1];
	ElementType temp = h->heap[h->heapSize];
	h->heapSize--;

	int parent = 1;
	int child = 2;

	while ((child <= h->heapSize)) {
		if (child < h->heapSize && h->heap[child].key < h->heap[child + 1].key) {
			child++;
		}
		if (temp.key >= h->heap[child].key) break;
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;
	return removed;
}

void HeapSort(ElementType e[], int n) {
	HeapType* h = CreateHeap();
	for (int i = 0; i < n; i++) {
		Insert_maxHeap(h, e[i]);
	}
	PrintHeap(h); printf("\n");
	for (int i = n - 1; i >= 0; i--) {
		e[i] = Delete_maxHeap(h);
	}
	free(h);
}

void PrintHeap(HeapType* h) {
	for (int i = 1; i <= h->heapSize; i++) {
		printf("[%d] %d ", i, h->heap[i].key);
	}
}

int ReadFile(const char* fileName, ElementType array[]) {//input파일을 읽어 배열에 저장. total 노드 개수인 n을 반환
	FILE* file = fopen(fileName, "r");
	if (!file) {
		fprintf(stderr, "file open failed.\n");
		exit(EXIT_FAILURE);
	}

	int n; //n: total number of data
	fscanf(file, "%d", &n);

	int data;
	int i = 0;
	while (fscanf(file, " %d", &data) != EOF) {
		array[i++].key = data;
	}

	fclose(file);

	return n;
}
