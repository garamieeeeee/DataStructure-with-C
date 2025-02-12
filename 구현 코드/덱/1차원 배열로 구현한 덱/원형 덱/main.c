#include "ArrayCircularDeque.h"

void test() {
	DequeType* dq = CreateDeque();

	for (int i = 0; i < 3; i++) {
		AddFront(dq, i);
		printf("<<맨 앞에 %d 삽입 >>\n", i);
		PrintDequeue(dq);
		printf("\n");
	}

	for (int i = 0; i < 3; i++) {
		DeleteRear(dq);
		printf("<< 맨 뒤의 데이터 삭제 >>\n");
		PrintDequeue(dq);
		printf("\n");
	}

	printf("덱 삭제\n"); DestroyDeque(&dq);
	if (dq) printf("덱이 삭제되지 않았습니다.\n");
}

int main() {
	test();
	return 0;
}
