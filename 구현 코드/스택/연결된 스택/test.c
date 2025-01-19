#include "LinkedStack.h"

int main() {
	LinkedStackType s;
	Init(&s);

	printf("<< 30 삽입 >>\n");
	Push(&s, 30);
	PrintStack(&s);

	printf("<< 40 삽입 >>\n");
	Push(&s, 40);
	PrintStack(&s);

	printf("<< 50 삽입 >>\n");
	Push(&s, 50);
	PrintStack(&s);

	ElementType data = Pop(&s);
	printf("<< 삭제 : %d >>\n", data);
	PrintStack(&s);

	data = Pop(&s);
	printf("<< 삭제 : %d >>\n", data);
	PrintStack(&s);

	data = Pop(&s);
	printf("<< 삭제 : %d >>\n", data);
	PrintStack(&s);

	return 0;
}
