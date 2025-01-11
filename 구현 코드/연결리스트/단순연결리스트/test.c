#include "SinglyLinkedList.h"

int main() {
	printf("----------1번 리스트----------\n");
	ListNode* head1;
	Init(&head1);//1번 리스트 생성

	printf("<< 리스트의 맨 앞에 10 삽입 >>\n");
	InsertFirst(&head1, 10);
	PrintList(head1);

	printf("<< 리스트의 맨 앞에 20 삽입 >>\n");
	InsertFirst(&head1, 20);
	PrintList(head1);

	printf("<< 리스트의 맨 앞에 30 삽입 >>\n");
	InsertFirst(&head1, 30);
	PrintList(head1);

	printf("<< 리스트의 맨 뒤에 40 삽입 >>\n");
	InsertLast(&head1, 40);
	PrintList(head1);

	printf("<< 리스트의 맨 뒤에 50 삽입 >>\n");
	InsertLast(&head1, 50);
	PrintList(head1);

	printf("리스트의 2번째 데이터: \n");
	ListNode* temp = GetNode(head1, 2);
	printf("%d\n\n", temp->data);

	printf("30의 위치: \n");
	int pos = GetPos(head1, 30);
	printf("%d\n\n", pos);

	printf("40의 위치: \n");
	pos = GetPos(head1, 40);
	printf("%d\n\n", pos);

	printf("<< 리스트의 10 뒤에 66 삽입 >>\n");
	pos = GetPos(head1, 10); //10의 위치 찾기
	temp = GetNode(head1, pos);
	InsertAfter(temp, 66);
	PrintList(head1);

	printf("<< 리스트의 4번째에 99 삽입 >>\n");
	InsertAt(&head1, 4, 99);
	PrintList(head1);

	printf("리스트의 크기: %d\n\n", GetSize(head1));

	printf("<< 리스트의 맨 앞의 데이터 삭제 >>\n");
	ElementType data = DeleteFirst(&head1);
	printf("삭제된 데이터: %d\n", data);
	PrintList(head1);

	printf("<< 리스트의 맨 뒤의 데이터 삭제 >>\n");
	data = DeleteLast(&head1);
	printf("삭제된 데이터: %d\n", data);
	PrintList(head1);

	printf("<< 리스트의 2번째 데이터 삭제 >>\n");
	data = DeleteAt(&head1, 2);
	printf("삭제된 데이터: %d\n", data);
	PrintList(head1);

	printf("<< 리스트의 데이터 '99' 삭제 >>\n");
	data = DeleteThis(&head1, 99);
	printf("삭제된 데이터: %d\n", data);
	PrintList(head1);

	printf("----------2번 리스트----------\n");
	ListNode* head2;
	Init(&head2);//2번 리스트 생성

	printf("<< 리스트의 맨 뒤에 11 삽입 >>\n");
	InsertLast(&head2, 11);
	PrintList(head2);

	printf("<< 리스트의 맨 뒤에 22 삽입 >>\n");
	InsertLast(&head2, 22);
	PrintList(head2);

	printf("<< 리스트의 맨 뒤에 33 삽입 >>\n");
	InsertLast(&head2, 33);
	PrintList(head2);

	printf("----------3번 리스트----------\n");
	ListNode* head3;
	Init(&head3);//3번 리스트 생성

	printf("<< 1번 리스트와 2번 리스트를 합쳐서 3번 리스트를 만듭니다. >>\n");
	ConcatTwo(&head1, &head2, &head3);
	PrintList(head3);

	printf("<< 3번 리스트를 역순으로 바꿉니다. >>\n");
	Reverse(&head3);
	PrintList(head3);

	printf("--------최종 1번 리스트--------\n");
	PrintList(head1);

	printf("--------최종 2번 리스트--------\n");
	PrintList(head2);

	printf("--------최종 3번 리스트--------\n");
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
