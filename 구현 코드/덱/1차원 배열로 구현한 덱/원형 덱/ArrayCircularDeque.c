//덱 구현 (1차원 배열 사용, 원형 큐를 변형해서 만듦)

#include "Deque.h"

void Error(char* message) {
	fprintf(stderr, "%s\n", message);
	exit(EXIT_FAILURE);
}

void InitDeque(DequeType* dq) {
	dq->front = 0;
	dq->rear = 0;

	return;
}

int IsEmpty(DequeType* dq) {
	return (dq->front == dq->rear);
}

int IsFull(DequeType* dq) {
	return ((dq->rear + 1) % MAX_QUEUE_SIZE == dq->front);
}

void PrintDequeue(DequeType* dq) {
	printf("Front Pos: %d, Rear Pos: %d\n", dq->front, dq->rear);
	if (!IsEmpty(dq)) {
		int i = dq->front;
		do {
			i = (i + 1) % MAX_QUEUE_SIZE;
			printf("[%d] %d | ", i, dq->data[i]);
			if (i == dq->rear) {
				break;
			}
		} while (i != dq->front);
	}
	printf("\n");

	return;
}

void AddRear(DequeType* dq, element data) {
	if (IsFull(dq)) {
		Error("DEQUE is Full");
		return;
	}

	dq->rear = (dq->rear + 1) % MAX_QUEUE_SIZE;
	dq->data[dq->rear] = data;

	return;
}

element DeleteFront(DequeType* dq) {
	if (IsEmpty(dq)) {
		Error("DEQUE is Empty");
		return -1;
	}

	dq->front = (dq->front + 1) % MAX_QUEUE_SIZE;
	return dq->data[dq->front];
}

element GetFront(DequeType* dq) {
	if (IsEmpty(dq)) {
		Error("DEQUE is Empty");
		return -1;
	}

	return dq->data[(dq->front + 1) % MAX_QUEUE_SIZE];
}

void AddFront(DequeType* dq, element data) {
	if (IsFull(dq)) {
		Error("DEQUE is Full");
		return;
	}

	dq->data[dq->front] = data;
	dq->front = (dq->front - 1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;

	return;
}

element DeleteRear(DequeType* dq) {
	if (IsEmpty(dq)) {
		Error("DEQUE is Empty");
		return -1;
	}

	int prev = dq->rear;
	dq->rear = (dq->rear - 1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;

	return dq->data[prev];
}

element GetRear(DequeType* dq) {
	if (IsEmpty(dq)) {
		Error("DEQUE is Empty");
		return -1;
	}

	return dq->data[dq->rear];
}
