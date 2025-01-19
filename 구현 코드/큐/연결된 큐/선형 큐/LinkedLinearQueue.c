#include "LinkedLinearQueue.h"

void Init(LinkedQueueType* q) {
	q->front = NULL;
	q->rear = NULL;
}

int IsEmpty(LinkedQueueType* q) {
	return (q->front == NULL);
}

void Enqueue(LinkedQueueType* q, ElementType data) {//연결리스트의 마지막에 노드 추가
	QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
	if (!newNode) {
		fprintf(stderr, "memory allocation failed\n");
		exit(EXIT_FAILURE);
	}
	newNode->data = data;
	newNode->link = NULL;

	if (IsEmpty(q)) { //큐가 공백상태일때 -> front와 rear 모두 새로운 노드를 가리켜야함
		q->front = newNode;
		q->rear = newNode;
	}
	else { //큐가 공백이 아니면 -> rear를 변경해줘야함
		q->rear->link = newNode;
		q->rear = newNode;
	}
}

ElementType Dequeue(LinkedQueueType* q) { //연결리스트의 맨 앞 노드를 삭제
	if (IsEmpty(q)) { //큐가 공백상태이면 삭제할 수 없다.
		fprintf(stderr, "queue is empty.\n");
		exit(EXIT_FAILURE);
	}

	QueueNode* temp = q->front;
	ElementType data = temp->data; //데이터를 꺼낸 뒤
	q->front = q->front->link; //front를 한칸 옮겨 주고
	if (q->front == NULL) {//만약 큐가 공백상태가 되면(원래 노드가 하나밖에 없었다면)
		q->rear = NULL; //rear도 NULL로 변경해준다.
	}
	free(temp); //첫번째 노드 삭제(메모리 할당해제)

	return data;
}

ElementType Peek(LinkedQueueType* q) { //연결리스트의 맨 앞 노드를 삭제하지않고 데이터 값만 반환
	if (IsEmpty(q)) { //큐가 공백상태이면 데이터 값을 꺼낼 수 없다.
		fprintf(stderr, "queue is empty.\n");
		exit(EXIT_FAILURE);
	}

	return (q->front->data);
}

void PrintQueue(LinkedQueueType* q) {
	QueueNode* ptr;
	printf("front -> |");
	for (ptr = q->front; ptr != NULL; ptr = ptr->link) {
		printf("%d -> ", ptr->data);
	}
	printf("| <- rear\n\n");
}
