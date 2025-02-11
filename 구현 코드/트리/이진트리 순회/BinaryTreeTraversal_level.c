//이진트리의 순회-level order
//원형큐를 구현하여 레벨 순회

#include <stdio.h>
#include <stdlib.h>

//원형 큐
#define QUEUE_SIZE 100

typedef char ElementType;

typedef struct BinTreeNode {
	ElementType data;
	struct BinTreeNode* leftChild;
	struct BinTreeNode* rightChild;
}BinTreeNode;

typedef struct {
	int front, rear;
	BinTreeNode* Queue[QUEUE_SIZE];
}QueueType;

QueueType* CreateQueue();
int IsEmptyQueue(QueueType* q);
int IsFullQueue(QueueType* q);
void Enqueue(QueueType* q, BinTreeNode* p);
BinTreeNode* Dequeue(QueueType* q);
void FreeQueue(QueueType** q);
void LevelOrder(BinTreeNode* root);

BinTreeNode n1 = { 'D', NULL, NULL };
BinTreeNode n2 = { 'E', NULL, NULL };
BinTreeNode n3 = { 'B', &n1, &n2 };
BinTreeNode n4 = { 'F', NULL, NULL };
BinTreeNode n5 = { 'G', NULL, NULL };
BinTreeNode n6 = { 'C', &n4, &n5 };
BinTreeNode n7 = { 'A', &n3, &n6 };
BinTreeNode* root = &n7;

//		  A
//	   /    \
// 	  B       C
//  /   \    /  \
// D     E  F    G 

int main() {
	printf("레벨 순회: "); LevelOrder(root); printf("\n"); //A B C D E F G

	return 0;
}

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
		printf("%c ", ptr->data);
		if (ptr->leftChild) Enqueue(q, ptr->leftChild);
		if (ptr->rightChild) Enqueue(q, ptr->rightChild);
	}

	//큐 메모리 해제
	FreeQueue(&q);
}
