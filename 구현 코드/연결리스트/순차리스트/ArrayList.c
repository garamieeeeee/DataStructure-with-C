//1차원 배열로 구현한 순차리스트

#include "ArrayList.h"

void Error(char* message) {
	fprintf(stderr, "%s\n", message);
	exit(EXIT_FAILURE);
}

void Init(ArrayListType* l) {
	l->size = 0;
}

int IsEmpty(ArrayListType* l) {
	return (l->size == 0);
}

int IsFull(ArrayListType* l) {
	return (l->size == MAX_LIST_SIZE);
}

ElementType GetEntry(ArrayListType* l, int pos) {
	if (pos < 0 || pos >= l->size) {
		Error("위치 오류");
	}

	return l->array[pos];
}

void PrintList(ArrayListType* l) {

	if (IsEmpty(l)) {
		printf("List is Empty\n\n");
		return;
	}

	for (int i = 0; i < l->size; i++) {
		printf("[%d]", l->array[i]);
		if (i != l->size - 1) {
			printf(" -> ");
		}
	}
	printf("\n\n");
	return;
}

void InsertLast(ArrayListType* l, ElementType data) {
	if (IsFull(l)) {
		Error("List is FUll");
	}

	l->array[l->size] = data;
	l->size++;
}

void Insert(ArrayListType* l, int pos, ElementType data) {
	if (!IsFull(l) && (pos >= 0) && (pos <= l->size)) { //pos가 l->size와 같은 경우에는, for문이 실행되지않고 바로 pos 위치, 즉 맨끝에 data를 삽입한다.
		for (int i = l->size - 1; i >= pos; i--) {
			l->array[i + 1] = l->array[i];
		}
		l->array[pos] = data;
		l->size++;
	}
}

ElementType Delete(ArrayListType* l, int pos) {
	if (pos < 0 || pos >= l->size) {
		Error("위치 오류");
	}

	ElementType data;
	data = l->array[pos];
	for (int i = pos; i < l->size - 1; i++) {
		l->array[i] = l->array[i + 1];
	}
	l->size--;

	return data;
}

void Clear(ArrayListType* l) {
	l->size = 0;
}

int GetLength(ArrayListType* l) {
	return l->size;
}

void Replace(ArrayListType* l, int pos, ElementType data) {
	if (pos < 0 || pos >= l->size) {
		Error("위치 오류");
	}

	l->array[pos] = data;
}
