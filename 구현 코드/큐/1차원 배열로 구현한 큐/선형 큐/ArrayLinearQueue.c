#include "LinearQueue.h"

void Error(char* message) {
	fprintf(stderr, "%s\n", message);
	exit(EXIT_FAILURE);
}

void InitQueue(QueueType* q) {
	q->front = -1;
	q->rear = -1;

	return;
}

void PrintQueue(QueueType* q) {
	printf("Front Pos: %d, Rear Pos: %d\n", q->front, q->rear);
	for (int i = 0; i < MAX_QUEUE_SIZE; i++) {
		if (i <= q->front || i > q->rear) {
			printf("[%d]  |", i);
		}
		else {
			printf("[%d] %d| ", i, q->data[i]);
		}
	}
	printf("\n");
	return;
}

int IsFull(QueueType* q) {
	return (q->rear == MAX_QUEUE_SIZE - 1);
}

int IsEmpty(QueueType* q) {
	return (q->front == q->rear);
}

void Enqueue(QueueType* q, element data) {
	if (IsFull(q)) {
		Error("Queue is Full\n");
		return;
	}

	q->data[++(q->rear)] = data;

	return;
}

element Dequeue(QueueType* q) {
	if (IsEmpty(q)) {
		Error("Queue is Empty\n");
		return -1;
	}

	return (q->data[++(q->front)]);
}
