//arrayStack

#include "ArrayStack.h"

void CreateStack(StackType** s, int capacity) {

	//create Stack
	(*s) = (StackType*)malloc(sizeof(StackType));
	if ((*s) == NULL) {
		fprintf(stderr, "Memory allocation failed\n");
		exit(1);
	}

	//allocate memory for Nodes
	(*s)->nodes = (Node*)malloc(capacity * sizeof(Node));
	if ((*s)->nodes == NULL) {
		fprintf(stderr, "Memory allocation failed\n");
		exit(1);
	}

	//initialize
	(*s)->capacity = capacity;
	(*s)->top = -1;
}

void DestroyStack(StackType** s) {

	//free allocated nodes
	free((*s)->nodes);
	(*s)->nodes = NULL; //메모리를 해제한 후 포인터를 NULL로 설정하는 습관을 들이면, 이후 이중 해제(Bug)를 방지할 수 있다.

	//free allocated stack
	free(*s);
	(*s) = NULL;

	return;
}

int IsEmpty(StackType* s) {
	return (s->top == -1);
}

int IsFull(StackType* s) {
	return (s->top == s->capacity-1);
}

void Push(StackType* s, ElementType data) {
	if (IsFull(s)) {
		s->capacity *= 2;
		s->nodes = (Node*)realloc(s->nodes, s->capacity * sizeof(Node));
		if (s->nodes == NULL) {
			fprintf(stderr, "Memory reallocation failed\n");
			exit(1);
		}
	}

	s->nodes[++(s->top)].data = data;
}

ElementType Pop(StackType* s) {
	if (IsEmpty(s)) {
		fprintf(stderr, "Stack is empty\n");
		exit(1);
	}

	return s->nodes[(s->top)--].data;
}

ElementType Peek(StackType* s) {
	if (IsEmpty(s)) {
		fprintf(stderr, "Stack is empty\n");
		exit(1);
	}

	return s->nodes[s->top].data;
}

int GetSize(StackType* s) {
	return (s->top + 1);
}

void ShowStack(StackType* s) {
	printf("Stack: \n");
	for (int i = s->top; i >= 0 ; i--) {
		printf("[%d]: %d\n", i, s->nodes[i].data);
	}

	return;
}
 

main.c(ArrayStack.c test)

#include "ArrayStack.h"

int main() {
	StackType* s = NULL;

	CreateStack(&s, 5);

	Push(s, 10);
	Push(s, 20);
	Push(s, 30);
	Push(s, 40);
	Push(s, 50);
	Push(s, 60);

	printf("Capacity: %d, Size: %d, Top: %d\n\n", s->capacity, GetSize(s), Peek(s));

	printf("Show Stack..\n");
	ShowStack(s);

	while (1) {
		if (IsEmpty(s)) {
			break;
		}

		printf("Popped: %d\n", Pop(s));

		if (!IsEmpty(s)) {
			printf("Current Top: %d\n", Peek(s));
		}
		else {
			printf("Stack is Empty.\n");
		}
	}

	DestroyStack(&s);

	printf("스택 삭제 확인: %d\n", s);


	return 0;
}
