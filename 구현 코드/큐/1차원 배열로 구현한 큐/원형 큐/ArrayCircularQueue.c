#include "ArrayCircularQueue.h"

void Error(char* message) {
	fprintf(stderr, "%s\n", message);
	exit(EXIT_FAILURE);
}

QueueType* CreateQueue() { //큐 구조체를 생성하고 초기화하여 반환
	QueueType* q = (QueueType*)malloc(sizeof(QueueType));
	if (!q) Error("memory allocation failed.");
	q->front = q->rear = 0;
	return q;
}

int IsEmpty(QueueType* q) {
	return (q->front == q->rear);
}

int IsFull(QueueType* q) {
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

void Enqueue(QueueType* q, ElementType data) {
	if (IsFull(q)) Error("Queue is full.");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->queue[q->rear] = data;
}

ElementType Dequeue(QueueType* q) {
	if (IsEmpty(q)) Error("Queue is empty.");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->queue[q->front];
}

ElementType Peek(QueueType* q) {
	if (IsEmpty(q)) Error("Queue is empty.");
	return q->queue[(q->front + 1) % MAX_QUEUE_SIZE];
}

void DestroyQueue(QueueType** q) {
	if (*q == NULL) return;
	free(*q);
	*q = NULL;
}

void PrintQueue(QueueType* q) {
	printf("Front Pos: %d, Rear Pos: %d\n", q->front, q->rear);
	if (!IsEmpty(q)) {
		int i = q->front;
		do {
			i = (i + 1) % MAX_QUEUE_SIZE;
			printf("[%d] %d | ", i, q->queue[i]);
			if (i == q->rear) {
				break;
			}
		} while (i != q->front);
	}
	printf("\n");
}
