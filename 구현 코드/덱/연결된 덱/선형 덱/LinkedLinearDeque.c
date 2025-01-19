#include "LinkedLinearDeque.h"

void Init(LinkedDequeType* dq) {
	dq->currentNodeCount = 0;
	dq->front = NULL;
	dq->rear = NULL;
}

int IsEmpty(LinkedDequeType* dq) {
	return (dq->currentNodeCount == 0);
}

int GetSize(LinkedDequeType* dq) {
	return (dq->currentNodeCount);
}

DequeNode* CreateDequeNode(ElementType data) {
	DequeNode* newNode = (DequeNode*)malloc(sizeof(DequeNode));
	if (!newNode) {
		fprintf(stderr, "memory allocation failed.\n");
		exit(EXIT_FAILURE);
	}

	newNode->data = data;
	newNode->Llink = NULL;
	newNode->Rlink = NULL;

	return newNode;
}

void AddFront(LinkedDequeType* dq, ElementType data) { //리스트의 맨 앞에 삽입
	DequeNode* newNode = CreateDequeNode(data);
	if (IsEmpty(dq)) { //리스트가 비어있는 경우, front와 rear는 둘다 newNode를 가리킴
		dq->front = newNode;
		dq->rear = newNode;
	}
	else { //리스트에 노드가 하나라도 있는 경우 -> front를 변경해주어야 함
		newNode->Rlink = dq->front;
		dq->front->Llink = newNode;
		dq->front = newNode; //front 갱신
	}

	dq->currentNodeCount++; //리스트 사이즈 +1
	return;
}

void AddRear(LinkedDequeType* dq, ElementType data) { //리스트의 맨 뒤에 삽입
	DequeNode* newNode = CreateDequeNode(data);
	if (IsEmpty(dq)) { //리스트가 비어있는 경우, front와 rear는 둘다 newNode를 가리킴
		dq->front = newNode;
		dq->rear = newNode;
	}
	else {  //리스트에 노드가 하나라도 있는 경우 -> rear를 변경해주어야 함
		newNode->Llink = dq->rear;
		dq->rear->Rlink = newNode;
		dq->rear = newNode; //rear 갱신
	}
	dq->currentNodeCount++; //리스트 사이즈 +1
	return;
}

ElementType DeleteFront(LinkedDequeType* dq) {//리스트의 맨 첫번째 노드를 삭제
	if (IsEmpty(dq)) { //리스트가 비어있으면 삭제할 수 없음
		fprintf(stderr, "deque is empty.\n");
		exit(EXIT_FAILURE);
	}

	DequeNode* temp = dq->front;
	ElementType data = temp->data;
	if (dq->front == dq->rear) { //리스트에 노드가 하나밖에 없는 경우 -> front와 rear 모두 NULL을 가리켜야 함
		dq->front = NULL;
		dq->rear = NULL;
	}
	else { //노드가 두개 이상인 경우 -> front를 변경해줘야 함
		dq->front = dq->front->Rlink; //front 갱신
		dq->front->Llink = NULL; //새로운 front의 Llink를 NULL로 만들어줌
	}
	free(temp);
	dq->currentNodeCount--; //리스트 사이즈 -1

	return data;
}

ElementType DeleteRear(LinkedDequeType* dq) {//리스트의 마지막 노드를 삭제
	if (IsEmpty(dq)) { //리스트가 비어있으면 삭제할 수 없음
		fprintf(stderr, "deque is empty.\n");
		exit(EXIT_FAILURE);
	}

	DequeNode* temp = dq->rear;
	ElementType data = temp->data;
	if (dq->front == dq->rear) { //리스트에 노드가 하나밖에 없는 경우 -> front와 rear 모두 NULL을 가리켜야 함
		dq->front = NULL;
		dq->rear = NULL;
	}
	else { //노드가 두개 이상인 경우 -> rear를 변경해줘야 함
		dq->rear = dq->rear->Llink; //rear 갱신
		dq->rear->Rlink = NULL;//새로운 rear의 Rlink를 NULL로 만들어줌
	}
	free(temp);
	dq->currentNodeCount--; //리스트 사이즈 -1

	return data;
}

ElementType GetRear(LinkedDequeType* dq) {//리스트의 맨 앞 노드를 삭제하지않고 데이터 값 반환
	if (IsEmpty(dq)) { //리스트가 비어있으면 데이터를 꺼낼 수 없음
		fprintf(stderr, "deque is empty.\n");
		exit(EXIT_FAILURE);
	}

	return (dq->front->data);
}

ElementType GetFront(LinkedDequeType* dq) {//리스트의 마지막 노드를 삭제하지않고 데이터 값 반환
	if (IsEmpty(dq)) { //리스트가 비어있으면 데이터를 꺼낼 수 없음
		fprintf(stderr, "deque is empty.\n");
		exit(EXIT_FAILURE);
	}

	return (dq->rear->data);
}

void PrintDeque(LinkedDequeType* dq) {
	printf("front -> | ");
	DequeNode* ptr = dq->front;
	while (ptr != NULL) {
		printf("%d -> ", ptr->data);
		ptr = ptr->Rlink;
	}
	printf("| <- rear\n\n");
}
