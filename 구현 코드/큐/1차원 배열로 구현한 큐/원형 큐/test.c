#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
#include "CircularQueue.h"

int main() {
	QueueType q;
	InitQueue(&q);
	int data;

	printf("---데이터 추가 단계---\n");
	while (!IsFull(&q)) {
		printf("정수를 입력하세요: ");
		scanf("%d", &data);
		Enqueue(&q, data);
		PrintQueue(&q);
	}
	printf("큐는 포화상태 입니다.\n\n");

	printf("---데이터 삭제 단계---\n");
	while (!IsEmpty(&q)) {
		data = Dequeue(&q);
		printf("꺼내진 정수: %d\n", data);
		PrintQueue(&q);
	}
	printf("큐는 공백상태 입니다.\n\n");

	return 0;
}
