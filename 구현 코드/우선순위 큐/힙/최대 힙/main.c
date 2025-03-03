#include "maxHeap.h"

void test() {
	ElementType list[8] = { 23, 56, 11, 9, 56, 99, 27, 34 };
	HeapSort(list, 8);
	for (int i = 0; i < 8; i++) {
		printf("%d ", list[i].key);
	}
	printf("\n");
}

int main() {
	test();
	return 0;
}
