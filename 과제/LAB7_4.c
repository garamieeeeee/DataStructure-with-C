#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;

typedef struct StackNode {
	ElementType data;
	struct StackNode* link;
}StackNode;

typedef struct {
	StackNode* top;//연결리스트의 헤드 포인터 역할
}LinkedStackType;

void ReadFile(const char* fileName, LinkedStackType* s);
void Init(LinkedStackType* s);
int IsEmpty(LinkedStackType* s);
void Push(LinkedStackType* s, ElementType data);
ElementType Pop(LinkedStackType* s);

int main(int argc, char* argv[]) {

	// 인자 검사
	if (argc < 3) { //argv[0]:파일 경로, argv[1]: input.txt, argv[2]: output.txt
		fprintf(stderr, "[Usage] %s <input.txt> <output.txt> \n", argv[0]);
		exit(EXIT_FAILURE);
	}

	//input파일 읽고 스택 생성
	LinkedStackType s;
	Init(&s);
	ReadFile(argv[1], &s); //input.txt를 처음부터 차례로 읽고 push

	//output파일 열고 쓰기
	FILE* file = fopen(argv[2], "w");
	if (!file) {
		fprintf(stderr, "file open failed\n");
	}

	int data;
	while (!IsEmpty(&s)) {//스택 전체를 하나씩 pop하면 스택에 쌓인 역순으로 나옴
		data = Pop(&s);
		printf("%d   ", data);
		fprintf(file, "%d   ", data);
	}
	printf("\n\n");

	fclose(file);

	return 0;
}

void ReadFile(const char* fileName, LinkedStackType* s) {//파일을 읽고 리스트 스택 생성
	FILE* file = fopen(fileName, "r");
	if (!file) {
		fprintf(stderr, "file open failed\n");
	}

	int c;
	while (fscanf(file, "%d", &c) != EOF) {
		Push(s, c);
	}

	fclose(file);

	return;
}

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
