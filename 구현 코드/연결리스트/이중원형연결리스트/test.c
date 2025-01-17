#include "DoublyCircularLinkedList.h"

int main() {
	printf("----------1번 리스트----------\n");
	DListNode* head1 = NULL; //head1: 더미헤드
	Init(&head1);

	printf("<< 리스트에 33 삽입 >>\n");
	InsertAt(head1, 0, 33);
	PrintList(head1);

	printf("<< 리스트의 맨 앞에 10 삽입 >>\n");
	InsertFirst(head1, 10);
	PrintList(head1);

	printf("<< 리스트의 맨 앞에 20 삽입 >>\n");
	InsertFirst(head1, 20);
	PrintList(head1);

	printf("<< 리스트의 맨 뒤에 40 삽입 >>\n");
	InsertLast(head1, 40);
	PrintList(head1);

	printf("<< 리스트의 맨 뒤에 50 삽입 >>\n");
	InsertLast(head1, 50);
	PrintList(head1);

	printf("20의 위치: \n");
	int pos = GetPos(head1, 20);
	printf("%d\n\n", pos);
	printf("50의 위치: \n");
	pos = GetPos(head1, 50);
	printf("%d\n\n", pos);

	printf("리스트의 0번째 데이터: \n");
	DListNode* temp = GetNode(head1, 0);
	printf("%d\n\n", temp->data);

	printf("리스트의 3번째 데이터: \n");
	temp = GetNode(head1, 3);
	printf("%d\n\n", temp->data);

	printf("리스트의 4번째 데이터: \n");
	temp = GetNode(head1, 4);
	printf("%d\n\n", temp->data);

	printf("리스트의 크기: %d\n\n", GetSize(head1));

	printf("<< 리스트의 33 뒤에 66 삽입 >>\n");
	pos = GetPos(head1, 33); //33의 위치 찾기
	temp = GetNode(head1, pos);
	InsertAfter(temp, 66);
	PrintList(head1);

	printf("<< 리스트의 10 앞에 11 삽입 >>\n");
	pos = GetPos(head1, 10); //10의 위치 찾기
	temp = GetNode(head1, pos);
	InsertBefore(temp, 11);
	PrintList(head1);

	printf("<< 리스트의 3번째에 99 삽입 >>\n");
	InsertAt(head1, 3, 99);
	PrintList(head1);


	printf("<< 리스트의 7번째에 77 삽입 >>\n");
	InsertAt(head1, 7, 77);
	PrintList(head1);

	printf("<< 리스트의 9번째에 999 삽입 >>\n");
	InsertAt(head1, 9, 999);
	PrintList(head1);

	printf("<< 리스트의 맨 앞의 데이터 삭제 >>\n");
	ElementType data = DeleteFirst(head1);
	printf("삭제된 데이터: %d\n", data);
	PrintList(head1);

	printf("<< 리스트의 맨 뒤의 데이터 삭제 >>\n");
	data = DeleteLast(head1);
	printf("삭제된 데이터: %d\n", data);
	PrintList(head1);

	printf("<< 리스트의 0번째 데이터 삭제 >>\n");
	data = DeleteAt(head1, 0);
	printf("삭제된 데이터: %d\n", data);
	PrintList(head1);

	printf("<< 리스트의 2번째 데이터 삭제 >>\n");
	data = DeleteAt(head1, 2);
	printf("삭제된 데이터: %d\n", data);
	PrintList(head1);

	printf("<< 리스트의 5번째 데이터 삭제 >>\n");
	data = DeleteAt(head1, 5);
	printf("삭제된 데이터: %d\n", data);
	PrintList(head1);

	printf("<< 리스트의 데이터 '99' 삭제 >>\n");
	data = DeleteThis(head1, 99);
	printf("삭제된 데이터: %d\n", data);
	PrintList(head1);

	printf("----------2번 리스트----------\n");
	DListNode* head2 = NULL; //head2: 더미헤드
	Init(&head2);

	printf("<< 리스트의 맨 뒤에 100 삽입 >>\n");
	InsertLast(head2, 100);
	PrintList(head2);

	printf("<< 리스트의 맨 뒤에 200 삽입 >>\n");
	InsertLast(head2, 200);
	PrintList(head2);

	printf("<< 리스트의 맨 뒤에 300 삽입 >>\n");
	InsertLast(head2, 300);
	PrintList(head2);

	printf("--------최종 1번 리스트--------\n");
	PrintList(head1);

	printf("--------최종 2번 리스트--------\n");
	PrintList(head2);

	printf("----------3번 리스트----------\n");
	DListNode* head3 = NULL; //head3: 더미헤드
	Init(&head3);

	printf("<< 1번 리스트와 2번 리스트를 합쳐서 3번 리스트를 만듭니다. >>\n");
	ConcatTwo(head1, head2, head3);
	PrintList(head3);

	printf("<< 리스트3을 역순으로 바꿉니다. >>\n");
	Reverse(head3);
	PrintList(head3);


	printf("<< 1번 리스트를 삭제합니다. >>\n");
	Clear(head1);
	PrintList(head1);

	printf("<< 2번 리스트를 삭제합니다. >>\n");
	Clear(head2);
	PrintList(head2);

	printf("<< 3번 리스트를 삭제합니다. >>\n");
	Clear(head3);
	PrintList(head3);

	return 0;
}
