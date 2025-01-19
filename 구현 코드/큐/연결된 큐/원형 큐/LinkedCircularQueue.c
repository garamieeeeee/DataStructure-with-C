#include "LinkedCircularQueue.h"

void Init(LinkedCQueueType* cq) {
	cq->front = NULL;
	cq->rear = NULL;
}

int IsEmpty(LinkedCQueueType* cq) {
	return (cq->front == NULL);
}

void Enqueue(LinkedCQueueType* cq, ElementType data) {//원형 연결리스트의 마지막에 삽입
	CQueueNode* newNode = (CQueueNode*)malloc(sizeof(CQueueNode));
	if (!newNode) {
		fprintf(stderr, "memory allocation failed.\n");
		exit(EXIT_FAILURE);
	}
	newNode->data = data;
	
	if (IsEmpty(cq)) {//원형 큐가 비어있으면 -> front와 rear가 모두 newNode를 가리켜야 함
		cq->front = newNode;
		cq->rear = newNode;
	}
	else { //원형큐가 공백상태가 아니면 -> rear에 삽입하고 난 후 rear를 변경해줘야함
		cq->rear->link = newNode;
		cq->rear = newNode;
	}
	//마지막으로 새로운 rear인 newNode의 링크를 front로 연결해준다.
	newNode->link = cq->front;
}

ElementType Dequeue(LinkedCQueueType* cq) { //원형 연결리스트의 맨 앞의 노드를 삭제
	if (IsEmpty(cq)) {//큐가 비어있으면 삭제할 수 없다.
		fprintf(stderr, "queue is empty.\n");
		exit(EXIT_FAILURE);
	}

	CQueueNode* temp = cq->front; //temp가 리스트의 맨 첫 노드를 가리키도록 해놓고
	ElementType data = temp->data; //데이터를 꺼내고

	if (cq->front == cq->rear) { //만약 리스트의 노드가 하나뿐이라면 -> front와 rear가 모두 NULL값을 가지도록 변경
		cq->front = NULL;
		cq->rear = NULL;
	}
	else{ //리스트에 노드가 두개 이상이면 -> front를 변경시키고 첫 노드를 삭제해야함
		cq->front = cq->front->link; //front가 하나 다음노드를 가리키도록 변경
		cq->rear->link = cq->front;  //front가 변경됐으니 rear의 링크가 새로운 front를 가리키도록 갱신
	}

	free(temp); //맨 첫 노드 삭제(메모리 할당 해제)

	return data;
}

ElementType Peek(LinkedCQueueType* cq) { //리스트의 맨 첫번째 노드를 삭제하지 않고 데이터 값만 반환한다
	if (IsEmpty(cq)) {//큐가 비어있으면 데이터 값을 반환할 수 없다.
		fprintf(stderr, "queue is empty.\n");
		exit(EXIT_FAILURE);
	}

	return cq->front->data;
}

void PrintQueue(LinkedCQueueType* cq) {
	CQueueNode* ptr = cq->front;

	if (IsEmpty(cq)) {
		printf("front -> | | <- rear\n\n");
	}
	else {
		printf("front -> | ");
		do {
			printf("%d -> ", ptr->data);
			ptr = ptr->link;
		} while (ptr != cq->front);
		printf("| <- rear\n\n");
	}
	return;
}
