#ifndef CIRCULARLINKEDLIST_H
#define CIRCULARLINKEDLIST_H

#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;

typedef struct CListNode { //C List: 원형 리스트
	ElementType data;
	struct CListNode* link;
}CListNode;

void Error(char* message);
void Init(CListNode** head);
int IsEmpty(CListNode* head);
int GetPos(CListNode* head, ElementType data);
int GetSize(CListNode* head);
CListNode* CreateNode(ElementType data);
CListNode* GetNode(CListNode* head, int index);
void InsertFirst(CListNode** head, ElementType data);
void InsertLast(CListNode** head, ElementType data);
void InsertAfter(CListNode** head, CListNode* pre, ElementType data);
void InsertAt(CListNode** head, int index, ElementType data);
ElementType DeleteFirst(CListNode** head);
ElementType DeleteLast(CListNode** head);
ElementType DeleteThis(CListNode** head, ElementType data);
ElementType DeleteAt(CListNode** head, int index);
void ConcatTwo(CListNode** head1, CListNode** head2, CListNode** head3);
void Reverse(CListNode** head);
void Clear(CListNode** head); void PrintList(CListNode* head);
void PrintList(CListNode* head);

#endif
