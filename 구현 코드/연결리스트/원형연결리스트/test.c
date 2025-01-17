#include "CircularLinkedList.h"

int main() {
	printf("----------1번 리스트----------\n");
	CListNode* head1;
	Init(&head1);

	printf("<< 리스트의 맨 앞에 10 삽입 >>\n");
	InsertFirst(&head1, 10);
	PrintList(head1);

	printf("<< 리스트의 맨 앞에 20 삽입 >>\n");
	InsertFirst(&head1, 20);
	PrintList(head1);

	printf("<< 리스트의 맨 앞에 30 삽입 >>\n");
	InsertFirst(&head1, 30);
	PrintList(head1);

	printf("<< 리스트의 맨 뒤에 11 삽입 >>\n");
	InsertLast(&head1, 11);
	PrintList(head1);

	printf("<< 리스트의 맨 뒤에 22 삽입 >>\n");
	InsertLast(&head1, 22);
	PrintList(head1);

	printf("<< 리스트의 맨 뒤에 33 삽입 >>\n");
	InsertLast(&head1, 33);
	PrintList(head1);

	printf("리스트의 크기: %d\n\n", GetSize(head1));

	printf("30의 위치: \n");
	int pos = GetPos(head1, 30);
	printf("%d\n\n", pos);

	printf("11의 위치: \n");
	pos = GetPos(head1, 11);
	printf("%d\n\n", pos);

	printf("33의 위치: \n");
	pos = GetPos(head1, 33);
	printf("%d\n\n", pos);

	printf("리스트의 0번째 데이터: \n");
	CListNode* temp = GetNode(head1, 0);
	printf("%d\n\n", temp->data);

	printf("리스트의 3번째 데이터: \n");
	temp = GetNode(head1, 3);
	printf("%d\n\n", temp->data);

	printf("리스트의 5번째 데이터: \n");
	temp = GetNode(head1, 5);
	printf("%d\n\n", temp->data);

	printf("<< 리스트의 맨 앞의 데이터 삭제 >>\n");
	ElementType data = DeleteFirst(&head1);
	printf("삭제된 데이터: %d\n", data);
	PrintList(head1);

	printf("<< 리스트의 맨 앞의 데이터 삭제 >>\n");
	data = DeleteFirst(&head1);
	printf("삭제된 데이터: %d\n", data);
	PrintList(head1);

	printf("<< 리스트의 맨 뒤의 데이터 삭제 >>\n");
	data = DeleteLast(&head1);
	printf("삭제된 데이터: %d\n", data);
	PrintList(head1);

	printf("<< 리스트의 맨 뒤의 데이터 삭제 >>\n");
	data = DeleteLast(&head1);
	printf("삭제된 데이터: %d\n", data);
	PrintList(head1);

	printf("리스트의 크기: %d\n\n", GetSize(head1));

	printf("----------2번 리스트----------\n");
	CListNode* head2;
	Init(&head2);

	printf("<< 리스트의 맨 뒤에 10 삽입 >>\n");
	InsertLast(&head2, 10);
	PrintList(head2);

	printf("<< 리스트의 맨 뒤에 20 삽입 >>\n");
	InsertLast(&head2, 20);
	PrintList(head2);

	printf("<< 리스트의 맨 뒤에 30 삽입 >>\n");
	InsertLast(&head2, 30);
	PrintList(head2);

	printf("<< 리스트의 맨 뒤에 40 삽입 >>\n");
	InsertLast(&head2, 40);
	PrintList(head2);

	printf("<< 리스트의 30 뒤에 7 삽입 >>\n");
	pos = GetPos(head2, 30); //30의 위치 찾기
	temp = GetNode(head2, pos); //선행노드(30) 찾기
	InsertAfter(&head2, temp, 7);
	PrintList(head2);

	printf("<< 리스트의 40 뒤에 9 삽입 >>\n");
	pos = GetPos(head2, 40); //30의 위치 찾기
	temp = GetNode(head2, pos); //선행노드(30) 찾기
	InsertAfter(&head2, temp, 9);
	PrintList(head2);

	printf("<< 리스트의 0번째에 100 삽입 >>\n");
	InsertAt(&head2, 0, 100);
	PrintList(head2);

	printf("<< 리스트의 2번째에 200 삽입 >>\n");
	InsertAt(&head2, 2, 200);
	PrintList(head2);

	printf("<< 리스트의 7번째에 300 삽입 >>\n");
	InsertAt(&head2, 7, 300);
	PrintList(head2);

	printf("<< 리스트의 9번째에 400 삽입 >>\n");
	InsertAt(&head2, 9, 400);
	PrintList(head2);

	printf("<< 리스트의 0번째 데이터 삭제 >>\n");
	data = DeleteAt(&head2, 0);
	printf("삭제된 데이터: %d\n", data);
	PrintList(head2);

	printf("<< 리스트의 3번째 데이터 삭제 >>\n");
	data = DeleteAt(&head2, 3);
	printf("삭제된 데이터: %d\n", data);
	PrintList(head2);

	printf("<< 리스트의 7번째 데이터 삭제 >>\n");
	data = DeleteAt(&head2, 7);
	printf("삭제된 데이터: %d\n", data);
	PrintList(head2);

	printf("<< 리스트의 데이터 '10' 삭제 >>\n");
	data = DeleteThis(&head2, 10);
	printf("삭제된 데이터: %d\n", data);
	PrintList(head2);

	printf("<< 리스트의 데이터 '40' 삭제 >>\n");
	data = DeleteThis(&head2, 40);
	printf("삭제된 데이터: %d\n", data);
	PrintList(head2);

	printf("<< 리스트의 데이터 '9' 삭제 >>\n");
	data = DeleteThis(&head2, 9);
	printf("삭제된 데이터: %d\n", data);
	PrintList(head2);

	printf("<< 최종 리스트 1 >>\n");
	PrintList(head1);

	printf("<< 최종 리스트 2 >>\n");
	PrintList(head2);

	printf("<< 리스트2 + 리스트1 = 리스트3 >>\n");
	CListNode* head3;
	Init(&head3);
	ConcatTwo(&head2, &head1, &head3);
	PrintList(head3);

	printf("<< 리스트3을 역순으로 바꿉니다. >>\n");
	Reverse(&head3);
	PrintList(head3);

	printf("<< 최종 리스트 1 >>\n");
	PrintList(head1);

	printf("<< 최종 리스트 2 >>\n");
	PrintList(head2);

	printf("<< 최종 리스트 3 >>\n");
	PrintList(head3);

	printf("<< 1번 리스트를 삭제합니다. >>\n");
	Clear(&head1);
	PrintList(head1);

	printf("<< 2번 리스트를 삭제합니다. >>\n");
	Clear(&head2);
	PrintList(head2);

	printf("<< 3번 리스트를 삭제합니다. >>\n");
	Clear(&head3);
	PrintList(head3);

	return 0;
}
