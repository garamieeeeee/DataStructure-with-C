#include <stdio.h>
#include <stdlib.h>
#define MAX_QUEUE_SIZE 100

typedef int ElementType;
typedef struct {
	ElementType queue[MAX_QUEUE_SIZE];
	int front, rear;
}QueueType;

void Error(char* message) {
	fprintf(stderr, "%s\n", message);
	exit(EXIT_FAILURE);
}

QueueType* CreateQueue() {
	QueueType* q = (QueueType*)malloc(sizeof(QueueType));
	if (!q) Error("memory allocation failed.");

	q->front = q->rear = 0;//원형 큐로 구현
	return q;
}

int IsEmpty(QueueType* q) {
	return (q->front == q->rear);
}

int IsFull(QueueType* q) {
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

void Enqueue(QueueType* q, ElementType data) {
	if (IsFull(q)) Error("Queue id Full.");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->queue[q->rear] = data;
}

ElementType Dequeue(QueueType* q) {
	if (IsEmpty(q)) Error("Queue is empty.");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->queue[q->front];
}

#define BUCKETS 10 //10진수 표현법에서는 버킷이 10개 필요하다
#define DIGITS 4

void RadixSort(int list[], int n) { //기수 정렬
	int i, b, d, factor = 1;
	QueueType* queues[BUCKETS]; //큐(버킷)은 10개가 필요

	for (b = 0; b < BUCKETS; b++) //10개의 큐를 동적으로 생성하고 초기화
		queues[b] = CreateQueue();

	for (d = 0; d < DIGITS; d++) {
		for (i = 0; i < n; i++) 
			Enqueue(queues[(list[i] / factor) % 10], list[i]);//데이터들을 자리수에 따라 큐에 삽입
		
		for (b = i = 0; b < BUCKETS; b++)
			while (!IsEmpty(queues[b]))
				list[i++] = Dequeue(queues[b]); //버킷에서 꺼내서 list로 합친다(큐에 넣은 순서대로 나온다)
		
		factor *= 10; //그 다음 자리수로 간다(작은 자리수에서부터 먼저 정렬해야한다)
	}
}

#define SIZE 10

int main() {
	int list[] = {28, 93, 39, 81, 62, 72, 38, 26};
	int n = sizeof(list) / sizeof(list[0]);
	
	//기수 정렬 호출
	RadixSort(list, n);

	for (int i = 0; i < n; i++)
		printf("%d ", list[i]);
	printf("\n");

	return 0;
}
