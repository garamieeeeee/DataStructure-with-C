#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include <stdio.h>
#include <stdlib.h>

#define MAX_LIST_SIZE 100

typedef int ElementType;
typedef struct {
	int size;
	ElementType array[MAX_LIST_SIZE];
}ArrayListType;

void Error(char* message);
void Init(ArrayListType* l);
int IsEmpty(ArrayListType* l);
int IsFull(ArrayListType* l);
ElementType GetEntry(ArrayListType* l, int pos);
void PrintList(ArrayListType* l);
void InsertLast(ArrayListType* l, ElementType data);
void Insert(ArrayListType* l, int pos, ElementType data);
ElementType Delete(ArrayListType* l, int pos);
void Clear(ArrayListType* l);
int GetLength(ArrayListType* l);
void Replace(ArrayListType* l, int pos, ElementType data);

#endif
