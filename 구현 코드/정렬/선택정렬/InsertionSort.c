#include <stdio.h>
#include <stdlib.h>
#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))

void SelectionSort(int list[], int n) {
	int i, j, least, temp; //least: 최솟값의 위치를 가리킴
	for (i = 0; i < n - 1; i++) {//요소가 n개면 list[0]부터 list[n-2]까지만 정렬하면 된다.
		least = i;
		for (j = i + 1; j < n; j++) {//아직 정렬되지 않은 부분에 대하여
			if (list[j] < list[least]) least = j; //최솟값 탐색
		}
		if (i != least) { //최솟값이 자기 자신이면 교환하지 않는다.
			SWAP(list[i], list[least], temp); //i번째 요소와 최솟값을 교환
		}
	}
}

int main() {
	int list[] = { 5,3,8,1,2,7 };
	int n = sizeof(list) / sizeof(list[0]);

	//선택 정렬 호출
	SelectionSort(list, n);

	for (int i = 0; i < n; i++)
		printf("%d ", list[i]);
	printf("\n");

	return 0;
}
