#include "BinaryTreeTraversal_level.h"

QueueType* CreateQueue() {
	QueueType* q = (QueueType*)malloc(sizeof(QueueType));
	if (!q) {
		fprintf(stderr, "memory allocation failed.\n");
		exit(EXIT_FAILURE);
	}
	q->front = q->rear = 0;

	return q;
}

int IsEmptyQueue(QueueType* q) {
	return (q->front == q->rear);
}

int IsFullQueue(QueueType* q) {
	return ((q->rear + 1) % QUEUE_SIZE == q->front);
}

void Enqueue(QueueType* q, BinTreeNode* p) {
	if (IsFullQueue(q)) {
		fprintf(stderr, "Queue is Full.\n");
		exit(EXIT_FAILURE);
	}

	q->rear = (q->rear + 1) % QUEUE_SIZE;
	q->Queue[q->rear] = p;
}

BinTreeNode* Dequeue(QueueType* q) {
	if (IsEmptyQueue(q)) {
		fprintf(stderr, "Queue is Empty.\n");
		exit(EXIT_FAILURE);
	}

	q->front = (q->front + 1) % QUEUE_SIZE;
	return q->Queue[q->front];
}

void FreeQueue(QueueType** q) {
	free(*q);
	*q = NULL;
}

void LevelOrder(BinTreeNode* root) {
	//예외 처리(트리가 비어있는 경우)
	if (root == NULL) return;

	//노드를 담을 큐 생성
	QueueType* q = CreateQueue();

	//루트노드부터 시작
	BinTreeNode* ptr = root;

	Enqueue(q, ptr);
	while (!IsEmptyQueue(q)) {
		ptr = Dequeue(q);
		if(ptr->data != 0) printf("%c ", ptr->data); //null값이 아닐때만 출력
		if (ptr->leftChild) Enqueue(q, ptr->leftChild);
		if (ptr->rightChild) Enqueue(q, ptr->rightChild);
	}

	//큐 메모리 해제
	FreeQueue(&q);
}
