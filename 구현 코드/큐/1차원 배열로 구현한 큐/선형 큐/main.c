#include "ArrayLinearQueue.h"

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
