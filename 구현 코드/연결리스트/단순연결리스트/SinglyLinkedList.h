#ifndef SINGLYLINKEDLIST_H
#define SINGLYLINKEDLIST_H

#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;

typedef struct ListNode {
	ElementType data;
	struct ListNode* link;
}ListNode;

void Error(char* message); //에러 메시지 출력 후 종료
void Init(ListNode** head); //헤드포인터 초기화
int IsEmpty(ListNode* head); //리스트가 비었는지 여부 리턴
int GetPos(ListNode* head, ElementType data); //리스트 안의 특정 데이터 위치 리턴
int GetSize(ListNode* head); //리스트의 현재 크기 리턴
ListNode* CreateNode(ElementType data); //데이터를 담은 노드 생성하여 반환
ListNode* GetNode(ListNode* head, int index); //리스트의 index번 노드 반환
void InsertFirst(ListNode** head, ElementType data); //리스트의 맨 앞에 노드 삽입
void InsertLast(ListNode** head, ElementType data); //리스트의 맨 뒤에 노드 삽입
void InsertAfter(ListNode* pre, ElementType data); //pre노드 뒤에 노드 삽입
void InsertAt(ListNode** head, int index, ElementType data); //리스트의 index번에 노드 삽입
ElementType DeleteFirst(ListNode** head); //리스트의 맨 앞의 노드 삭제하여 데이터 반환
ElementType DeleteLast(ListNode** head); //리스트의 맨 뒤의 노드 삭제하여 데이터 반환
ElementType DeleteThis(ListNode** head, ElementType data); //리스트 안에서 특정 데이터를 삭제하여 데이터 반환
ElementType DeleteAt(ListNode** head, int index); //리스트의 index번 노드 삭제하여 데이터 반환
void ConcatTwo(ListNode** head1, ListNode** head2, ListNode** head3); //리스트1, 리스트2를 이어붙인 리스트3 생성하는 함수
void Reverse(ListNode** head); //리스트를 역순으로 만드는 함수
void Clear(ListNode** head); //리스트의 모든 노드를 삭제하는 함수
void PrintList(ListNode* head); //리스트의 처음부터 끝까지 차례대로 데이터 출력

#endif
