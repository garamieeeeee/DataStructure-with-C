#include "ArrayCircularQueue.h"

void test() {
	QueueType* q = CreateQueue();
	ElementType data;

	Enqueue(q, 10);
	printf("<< Enqueue 10 >>\n");
	PrintQueue(q);
	printf("\n");

	Enqueue(q, 20);
	printf("<< Enqueue 20 >>\n");
	PrintQueue(q);
	printf("\n");

	Enqueue(q, 30);
	printf("<< Enqueue 30 >>\n");
	PrintQueue(q);
	printf("\n");

	Enqueue(q, 40);
	printf("<< Enqueue 40 >>\n");
	PrintQueue(q);
	printf("\n");

	printf("50 삽입 시도: \n");
	if (!IsFull(q)) {
		Enqueue(q, 30);
		printf("<< Enqueue 30 >>\n");
		PrintQueue(q);
		printf("\n");
	}
	else {
		printf("큐가 포화상태여서 삽입할 수 없습니다.\n");
	}
	//원형큐이기 때문에 큐 사이즈가 5여도 4칸밖에 못쓴다. 한칸은 비워둬야함

	data = Dequeue(q);
	printf("<< Dequeue >>\n");
	PrintQueue(q);
	printf("\n");

	data = Dequeue(q);
	printf("<< Dequeue >>\n");
	PrintQueue(q);
	printf("\n");

	data = Dequeue(q);
	printf("<< Dequeue >>\n");
	PrintQueue(q);
	printf("\n");

	printf("큐 삭제\n"); DestroyQueue(&q);
	if (q) printf("큐가 삭제되지 않았습니다.\n");
}

int main() {
	test();
	return 0;
}
