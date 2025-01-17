#include "ArrayList.h"

int main() {
	ArrayListType list;
	Init(&list);

	printf("<< 0번째 위치에 10 추가 >>\n");
	Insert(&list, 0, 10);
	PrintList(&list);

	printf("<< 0번째 위치에 20 추가 >>\n");
	Insert(&list, 0, 20);
	PrintList(&list);

	printf("<< 0번째 위치에 30 추가 >>\n");
	Insert(&list, 0, 30);
	PrintList(&list);

	printf("<< 맨 끝에 40 추가 >>\n");
	InsertLast(&list, 40);
	PrintList(&list);

	printf("<< 맨 끝에 50 추가 >>\n");
	InsertLast(&list, 50);
	PrintList(&list);

	printf("<< 맨 끝에 60 추가 >>\n");
	InsertLast(&list, 60);
	PrintList(&list);

	printf("<< 3번째 위치에 33 추가 >>\n");
	Insert(&list, 3, 33);
	PrintList(&list);

	printf("<< 5번째 위치에 55 추가 >>\n");
	Insert(&list, 5, 55);
	PrintList(&list);

	printf("<< 0번째 항목 삭제 >>\n");
	Delete(&list, 0);
	PrintList(&list);

	printf("<< 3번째 항목 삭제 >>\n");
	Delete(&list, 3);
	PrintList(&list);

	printf("<< 5번째 항목 삭제 >>\n");
	Delete(&list, 5);
	PrintList(&list);

	printf("3번째 항목: %d\n\n", GetEntry(&list, 3));

	printf("<< 3번째 항목을 9로 교체 >>\n");
	Replace(&list, 3, 9);
	PrintList(&list);

	printf("ArrayList 크기: %d\n\n", GetLength(&list));

	printf("<< ArrayList 삭제 >>\n");
	Clear(&list);
	PrintList(&list);

	return 0;
}
