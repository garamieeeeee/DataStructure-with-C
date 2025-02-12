//덱 구현 (1차원 배열 사용, 원형 큐를 변형해서 만듦)

#include "ArrayCircularDeque.h"

void Error(char* message) {
	fprintf(stderr, "%s\n", message);
	exit(EXIT_FAILURE);
}

DequeType* CreateDeque() {
	DequeType* dq = (DequeType*)malloc(sizeof(DequeType));
	if (!dq) Error("memory allocation failed.");
	dq->front = dq->rear = 0;
	return dq;
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
			printf("[%d] %d | ", i, dq->deque[i]);
			if (i == dq->rear) {
				break;
			}
		} while (i != dq->front);
	}
	printf("\n");
}

void AddRear(DequeType* dq, ElementType data) {
	if (IsFull(dq)) Error("Deque is Full.");
	dq->rear = (dq->rear + 1) % MAX_QUEUE_SIZE;
	dq->deque[dq->rear] = data;
}

ElementType DeleteFront(DequeType* dq) {
	if (IsEmpty(dq)) Error("Deque is Empty.");
	dq->front = (dq->front + 1) % MAX_QUEUE_SIZE;
	return dq->deque[dq->front];
}

ElementType GetFront(DequeType* dq) {
	if (IsEmpty(dq)) Error("Deque is Empty.");
	return dq->deque[(dq->front + 1) % MAX_QUEUE_SIZE];
}

void AddFront(DequeType* dq, ElementType data) {
	if (IsFull(dq)) Error("Deque is Full.");
	dq->deque[dq->front] = data;
	dq->front = (dq->front - 1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
	return;
}

ElementType DeleteRear(DequeType* dq) {
	if (IsEmpty(dq)) Error("Deque is Empty.");
	int prev = dq->rear;
	dq->rear = (dq->rear - 1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
	return dq->deque[prev];
}

ElementType GetRear(DequeType* dq) {
	if (IsEmpty(dq)) Error("Deque is Empty.");
	return dq->deque[dq->rear];
}

void DestroyDeque(DequeType** dq) {
	if (*dq == NULL) return;
	free(*dq);
	*dq = NULL;
}
