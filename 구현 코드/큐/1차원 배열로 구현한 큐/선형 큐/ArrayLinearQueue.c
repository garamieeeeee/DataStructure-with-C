#include "ArrayLinearQueue.h"

void Error(char* message) {
	fprintf(stderr, "%s\n", message);
	exit(EXIT_FAILURE);
}

QueueType* CreateQueue() { //큐 구조체를 생성하고 초기화하여 반환
	QueueType* q = (QueueType*)malloc(sizeof(QueueType));
	if (!q) Error("memory allocation failed.");
	q->front = q->rear = -1;
	return q;
}

int IsEmpty(QueueType* q) {
	return (q->front == q->rear);
}

int IsFull(QueueType* q) {
	return (q->rear == MAX_QUEUE_SIZE - 1);
}

void Enqueue(QueueType* q, ElementType data) {
	if (IsFull(q)) Error("Queue is full.");
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
	free(*q);
	*q = NULL;
}

void PrintQueue(QueueType* q) {
	printf("Front Pos: %d, Rear Pos: %d\n", q->front, q->rear);
	for (int i = 0; i < MAX_QUEUE_SIZE; i++) {
		if (i <= q->front || i > q->rear) {
			printf("[%d]  |", i);
		}
		else {
			printf("[%d] %d| ", i, q->queue[i]);
		}
	}
	printf("\n");
}
