#include "LinkedLinearQueue.h"

int main() {
	LinkedQueueType q;
	Init(&q);

	printf("<< 30 삽입 >>\n");
	Enqueue(&q, 30);
	PrintQueue(&q);

	printf("<< 40 삽입 >>\n");
	Enqueue(&q, 40);
	PrintQueue(&q);

	printf("<< 50 삽입 >>\n");
	Enqueue(&q, 50);
	PrintQueue(&q);

	ElementType data = Dequeue(&q);
	printf("<< 삭제 : %d >>\n", data);
	PrintQueue(&q);

	data = Dequeue(&q);
	printf("<< 삭제 : %d >>\n", data);
	PrintQueue(&q);

	data = Dequeue(&q);
	printf("<< 삭제 : %d >>\n", data);
	PrintQueue(&q);

	return 0;
}

