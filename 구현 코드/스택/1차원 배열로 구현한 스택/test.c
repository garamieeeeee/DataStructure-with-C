#include "ArrayStack.h"

void test() {
	StackType* s = CreateStack();

	printf("10 삽입\n"); Push(s, 10);
	printf("20 삽입\n"); Push(s, 20);
	printf("30 삽입\n"); Push(s, 30);
	printf("40 삽입\n"); Push(s, 40);
	printf("50 삽입\n"); Push(s, 50);
	printf("60 삽입\n"); Push(s, 60);
	printf("\n");

	printf("print stack: \n"); PrintStack(s);
	printf("stack size: %d\n", GetSize(s)); printf("\n");

	while (!IsEmpty(s)) {
		ElementType data = Pop(s);
		printf("Popped: %d\n", data);
	}
	printf("Stack is Empty.\n");

	printf("스택 삭제\n");
	DestroyStack(&s);
	if (s) printf("스택이 삭제되지 않았습니다.\n");
}

int main() {
	test();
	return 0;
}
