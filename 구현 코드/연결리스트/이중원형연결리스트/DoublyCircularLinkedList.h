#ifndef DOUBLYCIRCULARLINKEDLIST_H
#define DOUBLYCIRCULARLINKEDLIST_H

#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct DListNode {
	ElementType data;
	struct DListNode* Llink;
	struct DListNode* Rlink;
}DListNode;

void Error(char* message);
void Init(DListNode** head);
int GetPos(DListNode* head, ElementType data);
int GetSize(DListNode* head);
DListNode* CreateNode(ElementType data);
DListNode* GetNode(DListNode* head, int index);
void InsertFirst(DListNode* head, ElementType data);
void InsertLast(DListNode* head, ElementType data);
void InsertAfter(DListNode* pre, ElementType data);
void InsertBefore(DListNode* pre, ElementType data);
void InsertAt(DListNode* head, int index, ElementType data);
ElementType DeleteFirst(DListNode* head);
ElementType DeleteLast(DListNode* head);
ElementType DeleteThis(DListNode* head, ElementType data);
ElementType DeleteAt(DListNode* head, int index);
void ConcatTwo(DListNode* head1, DListNode* head2, DListNode* head3);
void Reverse(DListNode* head);
void Clear(DListNode* head);
void PrintList(DListNode* head);

#endif
