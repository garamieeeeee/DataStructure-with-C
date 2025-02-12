//큐 구조체를 생성할때, 큐의 초기 용량을 설정한다.
//만약 큐가 꽉 찼는데 삽입할 경우, 용량을 2배로 늘리고 realloc한 후 삽입한다.
#include "DynamicArrayLinearQueue.h"

void Error(char* message) {
	fprintf(stderr, "%s\n", message);
	exit(EXIT_FAILURE);
}

QueueType* CreateQueue(int capacity) { //큐 구조체를 생성하고 초기화하여 반환, 초기 용량을 전달해야함
	QueueType* q = (QueueType*)malloc(sizeof(QueueType));
	if (!q) Error("memory allocation failed.");

	q->queue = (ElementType*)malloc(capacity * sizeof(ElementType));
	if (!q->queue) Error("memory allocation failed.");

	//initialize;
	q->capacity = capacity;
	q->front = q->rear = -1;

	return q;
}

int IsEmpty(QueueType* q) {
	return (q->front == q->rear);
}

int IsFull(QueueType* q) {
	return (q->rear == q->capacity - 1);
}

void resizeQueue(QueueType* q) { //큐의 용량을 2배로 확장
	int newCapacity = 2 * (q->capacity);
	q->queue = (ElementType*)realloc(q->queue, newCapacity * sizeof(ElementType));
	q->capacity = newCapacity;
}

void Enqueue(QueueType* q, ElementType data) {
	if (IsFull(q)) resizeQueue(q);

	q->queue[++(q->rear)] = data;
}

ElementType Dequeue(QueueType* q) {
	if (IsEmpty(q)) Error("Queue is empty.");
	return (q->queue[++(q->front)]);
}

ElementType Peek(QueueType* q) {
	if (IsEmpty(q)) Error("Queue is empty.");
	return (q->queue[q->front]);
}

void DestroyQueue(QueueType** q) {
	if (*q == NULL) return;

	free((*q)->queue); (*q)->queue = NULL;

	free(*q); *q = NULL;
}

void PrintQueue(QueueType* q) {
	printf("Front Pos: %d, Rear Pos: %d\n", q->front, q->rear);
	for (int i = 0; i <= q->rear; i++) {
		if (i <= q->front || i > q->rear) {
			printf("[%d]  |", i);
		}
		else {
			printf("[%d] %d| ", i, q->queue[i]);
		}
	}
	printf("\n");
}
