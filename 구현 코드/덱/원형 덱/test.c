#include "Deque.h"

int main() {
	DequeType dq;
	InitDeque(&dq);

	for (int i = 0; i < 3; i++) {
		AddFront(&dq, i);
		printf("<<맨 앞에 %d 삽입 >>\n", i);
		PrintDequeue(&dq);
		printf("\n");
	}

	for (int i = 0; i < 3; i++) {
		DeleteRear(&dq);
		printf("<< 맨 뒤의 데이터 삭제 >>\n");
		PrintDequeue(&dq);
		printf("\n");
	}

	return 0;
}
