#include "ArrayStack.h"

void Error(char* message) {
	fprintf(stderr, "%s\n", message);
	exit(EXIT_FAILURE);
}

StackType* CreateStack() { //스택 구조체 생성하고 초기화하여 반환함
	StackType* s = (StackType*)malloc(sizeof(StackType));
	if (!s) Error("memory allocation failed.");
	s->top = -1;

	return s;
}

int IsEmpty(StackType* s) {
	return (s->top == -1);
}

int IsFull(StackType* s) {
	return (s->top == MAX_STACK_SIZE - 1);
}

void Push(StackType* s, ElementType data) {
	if (IsFull(s)) Error("Stack is full.");
	s->stack[++(s->top)] = data;
}

ElementType Pop(StackType* s) {
	if (IsEmpty(s)) Error("Stack is empty.");
	return s->stack[(s->top)--];
}

ElementType Peek(StackType* s) {
	if (IsEmpty(s)) Error("Stack is empty.");
	return s->stack[s->top];
}

void DestroyStack(StackType** s) {
	if (*s == NULL) return;
	free(*s);
	*s = NULL;
}

int GetSize(StackType* s) {
	return (s->top + 1);
}

void PrintStack(StackType* s) {
	for (int i = s->top; i >= 0; i--) {
		printf("[%d] %d\n", i, s->stack[i]);
	}
	printf("\n");
}
