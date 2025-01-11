#include "GenericArrayStack.h"

int main() {

	//스택 생성
	StackType* s_i = NULL; //int형 스택 포인터 s_i
	StackType* s_c = NULL; //char형 스택 포인터 s_c
	StackType* s_f = NULL; //float형 스택 포인터 s_f

	CreateStack(&s_i, sizeof(int));
	CreateStack(&s_c, sizeof(char));
	CreateStack(&s_f, sizeof(float));

	int value_i;
	char value_c;
	float value_f;

	//삽입(Push)
	for (int i = 0; i < 5; i++) {
		value_i = i * 2;
		Push(s_i, &value_i);
	}

	for (int i = 0; i < 5; i++) {
		value_c = 'a' + i;
		Push(s_c, &value_c);
	}

	for (int i = 0; i < 5; i++) {
		value_f = i * (0.2);
		Push(s_f, &value_f);
	}

	//출력(Pop)
	printf("int형 스택 출력: \n");
	for (int i = s_i->top; i >= 0; i--) {
		value_i = *(int*)Pop(s_i);
		printf("%2d [%d]\n", value_i, i);
	}
	printf("\n");

	printf("char형 스택 출력: \n");
	for (int i = s_c->top; i >= 0; i--) {
		value_c = *(char*)Pop(s_c);
		printf("%c [%d]\n", value_c, i);
	}
	printf("\n");

	printf("float형 스택 출력: \n");
	for (int i = s_f->top; i >= 0; i--) {
		value_f = *(float*)Pop(s_f);
		printf("%f [%d]\n", value_f, i);
	}
	printf("\n");

	//스택 메모리 해제
	DestroyStack(&s_i);
	DestroyStack(&s_c);
	DestroyStack(&s_f);

	return 0;
}
