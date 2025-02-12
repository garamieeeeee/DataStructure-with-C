//스택 구조체를 생성할때, 스택의 초기 용량을 설정한다.
//만약 스택이 꽉 찼는데 삽입할 경우, 용량을 2배로 늘리고 realloc한 후 삽입한다.
#include "DynamicArrayStack.h"

void Error(char* message) {
	fprintf(stderr, "%s\n", message);
	exit(EXIT_FAILURE);
}

StackType* CreateStack(int capacity) { //스택 구조체 생성하고 초기화하여 반환함, 초기 용량을 전달해야함
	//create Stack
	StackType* s = (StackType*)malloc(sizeof(StackType));
	if (!s) Error("memory allocation failed.");

	//allocate memory for stack nodes.
	s->stack = (ElementType*)malloc(capacity * sizeof(ElementType));
	if (!s->stack) Error("memory allocation failed.");

	//initialize
	s->capacity = capacity;
	s->top = -1;

	return s;
}

int IsEmpty(StackType* s) {
	return (s->top == -1);
}

int IsFull(StackType* s) {
	return (s->top == s->capacity - 1);
}

void Push(StackType* s, ElementType data) {
	if (IsFull(s)) {
		s->capacity *= 2;
		s->stack = (ElementType*)realloc(s->stack, s->capacity * sizeof(ElementType));
		if (!s->stack) Error("memory allocation failed.");
	}

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

	free((*s)->stack);
	(*s)->stack = NULL;

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
