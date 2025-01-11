#include "CircularQueue.h"

void Error(char* message) {
	fprintf(stderr, "%s\n", message);
	exit(EXIT_FAILURE);
}

void InitQueue(QueueType* q) {
	q->front = 0;
	q->rear = 0;

	return;
}

int IsFull(QueueType* q) {
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

int IsEmpty(QueueType* q) {
	return (q->front == q->rear);
}

void PrintQueue(QueueType* q) {
	printf("Front Pos: %d, Rear Pos: %d\n", q->front, q->rear);
	if (!IsEmpty(q)) {
		int i = q->front;
		do {
			i = (i + 1) % MAX_QUEUE_SIZE;
			printf("[%d] %d | ", i, q->data[i]);
			if (i == q->rear) {
				break;
			}
		} while (i != q->front);
	}
	printf("\n");
}

void Enqueue(QueueType* q, element data) {
	if (IsFull(q)) {
		Error("Queue is Full\n");
		return;
	}

	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = data;

	return;
}

element Dequeue(QueueType* q) {
	if (IsEmpty(q)) {
		Error("Queue is Empty\n");
		return -1;
	}

	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->data[q->front];
}

element Peek(QueueType* q) {
	if (IsEmpty(q)) {
		Error("Queue is Empty\n");
		return -1;
	}

	return q->data[(q->front + 1) % MAX_QUEUE_SIZE];
}
