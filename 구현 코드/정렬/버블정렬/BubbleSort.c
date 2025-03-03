#include <stdio.h>
#include <stdlib.h>
#define SWAP(x,y,t) ((t) = (x), (x)=(y), (y)=(t))

void BubbleSort(int list[], int n) {
	int i, j, temp;
	for (i = n - 1; i > 0; i--) {//무조건 n-1번의 스캔을 한다. 한번 스캔을 돌고나면 가장 큰 자료가 맨 뒤로 이동하고 맨 뒤의 자료는 정렬에서 제외된다.
		for (j = 0; j < i; j++) {//한번 스캔을 돌때마다 정렬해야할 자료의 크기가 1씩 줄어든다
			if (list[j] > list[j + 1]) //인접한 두 요소를 비교하여 크기 순서대로 되어있지 않으면 서로 교환한다.
				SWAP(list[j], list[j + 1], temp);
		}
	}
}

int main() {
	int list[] = { 5,3,8,1,2,7 };
	int n = sizeof(list) / sizeof(list[0]);

	//버블 정렬 호출
	BubbleSort(list, n);

	for (int i = 0; i < n; i++)
		printf("%d ", list[i]);
	printf("\n");

	return 0;
}
