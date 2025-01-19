//스택을 단순연결리스트를 이용해서 구현함
#include "LinkedStack.h"

void Init(LinkedStackType* s) {
	s->top = NULL;
}

int IsEmpty(LinkedStackType* s) {
	return (s->top == NULL);
}

void Push(LinkedStackType* s, ElementType data) {
	StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
	if (!newNode) {
		fprintf(stderr, "memory allocation failed\n");
		exit(EXIT_FAILURE);
	}

	newNode->data = data;
	newNode->link = s->top;
	s->top = newNode;
}

ElementType Pop(LinkedStackType* s) {
	if (IsEmpty(s)) {
		fprintf(stderr, "stack is empty\n");
		exit(EXIT_FAILURE);
	}

	StackNode* temp = s->top;
	ElementType data = temp->data;

	s->top = s->top->link;
	free(temp);

	return data;
}

ElementType Peek(LinkedStackType* s) {
	if (IsEmpty(s)) {
		fprintf(stderr, "stack is empty\n");
		exit(EXIT_FAILURE);
	}

	return (s->top->data);
}

void PrintStack(LinkedStackType* s) {
	StackNode* ptr = s->top;
	printf("top -> ");
	while (ptr != NULL) {
		printf("%d -> ", ptr->data);
		ptr = ptr->link;
	}
	printf("NULL\n\n");
}
