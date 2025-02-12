#include "DynamicArrayCircularQueue.h"

void test() {
	//초기 용량이 5인 큐 생성
	QueueType* q = CreateQueue(5);
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

	printf("queue capacity: %d\n", q->capacity); printf("\n");

	Enqueue(q, 50);
	printf("<< Enqueue 50 >>\n");
	PrintQueue(q);
	printf("\n");

	Enqueue(q, 60);
	printf("<< Enqueue 60 >>\n");
	PrintQueue(q);
	printf("\n");

	Enqueue(q, 70);
	printf("<< Enqueue 70 >>\n");
	PrintQueue(q);
	printf("\n");
	printf("queue capacity: %d\n", q->capacity); printf("\n");
	//큐의 용량이 2배로 확장됨

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
