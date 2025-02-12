//큐 구조체를 생성할때, 큐의 초기 용량을 설정한다.
//만약 큐가 꽉 찼는데 삽입할 경우, 현재 용량의 2배인 큐를 새로 만들어 기존 큐의 요소들을 재배치한다

#include"DynamicArrayCircularQueue.h"

void Error(char* message) {
	fprintf(stderr, "%s\n", message);
	exit(EXIT_FAILURE);
}

QueueType* CreateQueue(int capacity) { //큐 구조체를 생성하고 초기화하여 반환. 초기 용량을 전달해야함
	QueueType* q = (QueueType*)malloc(sizeof(QueueType));
	if (!q) Error("memory allocation failed.");

	q->queue = (ElementType*)malloc(capacity * sizeof(ElementType));
	if (!q->queue) Error("memory allocation failed.");

	//initialize;
	q->capacity = capacity;
	q->front = q->rear = 0;

	return q;
}

int IsEmpty(QueueType* q) {
	return (q->front == q->rear);
}

int IsFull(QueueType* q) {
	return ((q->rear + 1) % q->capacity == q->front);
}

void resizeQueue(QueueType* q) {
	int newCapacity = 2 * (q->capacity);
	ElementType* newQueue = (ElementType*)malloc(newCapacity * sizeof(ElementType));

	//큐에 현재 저장된 요소의 개수를 구한다
	//rear가 front보다 큰 경우: size == rear-front
	//rear < front인 경우: size == capacity - front + rear;
	int size = (q->rear >= q->front) ? (q->rear - q->front) : (q->capacity - q->front + q->rear);

	//큐의 용량을 확장하고 나서도 원형 구조를 유지해야하기 때문에
	//모든 요소를 다시 배치해야한다.
	//i: 기존 큐의 front 다음 요소부터 시작
	//j: 새로운 배열에서 0부터 시작
	int i = (q->front + 1) % q->capacity;
	for (int j = 0; j < size; j++) {
		newQueue[j] = q->queue[i];
		i = (i + 1) % q->capacity;
	}

	//기존 메모리 해제 후 새 배열 적용
	free(q->queue);
	q->queue = newQueue;

	//새 front, rear 설정
	q->front = newCapacity - 1; //front는 마지막 요소의 한칸 앞을 가리킴
	q->rear = size - 1; //rear는 마지막 요소를가리킴
	q->capacity = newCapacity;
}

void Enqueue(QueueType* q, ElementType data) {
	if (IsFull(q)) resizeQueue(q);
	q->rear = (q->rear + 1) % q->capacity;
	q->queue[q->rear] = data;
}

ElementType Dequeue(QueueType* q) {
	if (IsEmpty(q)) Error("Queue is empty.");
	q->front = (q->front + 1) % q->capacity;
	return q->queue[q->front];
}

ElementType Peek(QueueType* q) {
	if (IsEmpty(q)) Error("Queue is empty.");
	return q->queue[(q->front + 1) % q->capacity];
}

void DestroyQueue(QueueType** q) {
	if (*q == NULL) return;
	free(*q);
	*q = NULL;
}

void PrintQueue(QueueType* q) {
	printf("Front Pos: %d, Rear Pos: %d\n", q->front, q->rear);
	if (!IsEmpty(q)) {
		int i = q->front;
		do {
			i = (i + 1) % q->capacity;
			printf("[%d] %d | ", i, q->queue[i]);
			if (i == q->rear) {
				break;
			}
		} while (i != q->front);
	}
	printf("\n");
}
