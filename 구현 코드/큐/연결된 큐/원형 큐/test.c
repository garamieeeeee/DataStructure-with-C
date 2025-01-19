#include "LinkedCircularQueue.h"

int main() {
	LinkedCQueueType cq;
	Init(&cq);

	printf("<< 30 삽입 >>\n");
	Enqueue(&cq, 30);
	PrintQueue(&cq);

	printf("<< 40 삽입 >>\n");
	Enqueue(&cq, 40);
	PrintQueue(&cq);

	printf("<< 50 삽입 >>\n");
	Enqueue(&cq, 50);
	PrintQueue(&cq);

	ElementType data = Dequeue(&cq);
	printf("<< 삭제 : %d >>\n", data);
	PrintQueue(&cq);

	data = Dequeue(&cq);
	printf("<< 삭제 : %d >>\n", data);
	PrintQueue(&cq);

	data = Dequeue(&cq);
	printf("<< 삭제 : %d >>\n", data);
	PrintQueue(&cq);

	return 0;
}
