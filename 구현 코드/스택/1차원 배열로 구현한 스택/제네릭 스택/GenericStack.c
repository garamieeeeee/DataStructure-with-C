//똑같이 1차원 배열로 구현한 스택
//스택 요소의 데이터 타입에 상관없이 사용할 수 있는 제네릭 스택 구현
#include "GenericStack.h"

void CreateStack(StackType** s, int elementSize) {
	(*s) = (StackType*)malloc(sizeof(StackType));
	if ((*s) == NULL) {
		fprintf(stderr, "Memory allocation failed\n");
		exit(1);
	}

	(*s)->capacity = 10;//스택의 초기 용량은 10으로 설정
	(*s)->top = -1;

	(*s)->nodes = (Node*)malloc((*s)->capacity * sizeof(Node));
	if ((*s)->nodes == NULL) {
		fprintf(stderr, "Memory allocation failed\n");
		exit(1);
	}

	//자료형 크기 저장
	for (int i = 0; i < (*s)->capacity; i++) {
		(*s)->nodes[i].data = malloc(elementSize); //자료형 크기만큼 메모리 할당
		(*s)->nodes[i].elementSize = elementSize;
	}

	return;
}

void DestroyStack(StackType** s) {
	for (int i = 0; i < (*s)->capacity; i++) {
		free((*s)->nodes[i].data);
	}
	free((*s)->nodes);

	free(*s);
	(*s) = NULL;

	return;
}

void Push(StackType* s, void* data) {
	if (IsFull(s)) {
		s->capacity *= 2; //용량을 두배로 늘리고 메모리 재할당
		s->nodes = realloc(s->nodes, s->capacity * sizeof(Node));

		if (s->nodes == NULL) {
			fprintf(stderr, "Memory reallocation failed\n");
			exit(1);
		}

		for (int i = s->top + 1; i < s->capacity; i++) {
			s->nodes[i].data = malloc(s->nodes[0].elementSize);
			if (s->nodes[i].data == NULL) {
				fprintf(stderr, "Memory allocation failed for new node\n");
				exit(1);
			}

			s->nodes[i].elementSize = s->nodes[0].elementSize;
		}
	}

	memcpy(s->nodes[++(s->top)].data, data, s->nodes[s->top].elementSize);//전달된 데이터를 메모리 복사로 저장한다.

	return;
}

void* Pop(StackType* s) {
	if (IsEmpty(s)) {
		fprintf(stderr, "Stack is empty\n");
		exit(1);
	}

	return s->nodes[(s->top)--].data;
}

void* Peek(StackType* s) {
	if (IsEmpty(s)) {
		fprintf(stderr, "Stack is empty\n");
		exit(1);
	}

	return s->nodes[s->top].data;
}

int IsFull(StackType* s) {
	return (s->top == s->capacity - 1);
}

int IsEmpty(StackType* s) {
	return (s->top == -1);
}
