#include "LinearQueue.h"

int main() {
	QueueType q;
	InitQueue(&q);
	int data;

	Enqueue(&q, 10);
	printf("<< Enqueue 10 >>\n");
	PrintQueue(&q);
	printf("\n");

	Enqueue(&q, 20);
	printf("<< Enqueue 20 >>\n");
	PrintQueue(&q);
	printf("\n");

	Enqueue(&q, 30);
	printf("<< Enqueue 30 >>\n");
	PrintQueue(&q);
	printf("\n");

	data = Dequeue(&q);
	printf("<< Dequeue >>\n");
	PrintQueue(&q);
	printf("\n");

	data = Dequeue(&q);
	printf("<< Dequeue >>\n");
	PrintQueue(&q);
	printf("\n");

	data = Dequeue(&q);
	printf("<< Dequeue >>\n");
	PrintQueue(&q);
	printf("\n");

	return 0;
}
