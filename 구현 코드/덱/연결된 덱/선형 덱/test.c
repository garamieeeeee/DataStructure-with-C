#include "LinkedLinearDeque.h"

int main() {
	LinkedDequeType dq;
	Init(&dq);
	printf("초기 덱: \n");
	PrintDeque(&dq);

	for (int i = 1; i <= 3; i++) { //리스트의 맨 앞에 1,2,3 차례로 추가
		printf("<< 맨 앞에 %d 추가 >>\n", i);
		AddFront(&dq, i);
		PrintDeque(&dq);
	}

	for (int i = 4; i <= 6; i++) { //리스트의 맨 뒤에 4,5,6 차례로 추가
		printf("<< 맨 뒤에 %d 추가 >>\n", i);
		AddRear(&dq, i);
		PrintDeque(&dq);
	}

	ElementType data = DeleteFront(&dq);
	printf("<< 맨 앞의 데이터 %d 삭제 >>\n", data);
	PrintDeque(&dq);

	data = DeleteRear(&dq);
	printf("<< 맨 뒤의 데이터 %d 삭제 >>\n", data);
	PrintDeque(&dq);

	printf("덱의 현재 사이즈: %d\n", GetSize(&dq));

	return 0;
}
