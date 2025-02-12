#include "DynamicArrayStack.h"

void test() {
	//초기 용량이 5인 스택을 생성
	StackType* s = CreateStack(5);

	printf("10 삽입\n"); Push(s, 10);
	printf("20 삽입\n"); Push(s, 20);
	printf("30 삽입\n"); Push(s, 30);
	printf("40 삽입\n"); Push(s, 40);
	printf("\n");

	printf("print stack: \n"); PrintStack(s);
	printf("stack size: %d\n", GetSize(s));
	printf("stack capacity: %d\n", s->capacity);
	printf("\n");

	printf("50 삽입\n"); Push(s, 50);
	printf("60 삽입\n"); Push(s, 60);
	printf("\n");
	printf("print stack: \n"); PrintStack(s);
	printf("stack size: %d\n", GetSize(s));
	printf("stack capacity: %d\n", s->capacity);
	printf("\n");
	//스택 용량이 5에서 10으로 두배가 된것을 확인할 수 있음

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
