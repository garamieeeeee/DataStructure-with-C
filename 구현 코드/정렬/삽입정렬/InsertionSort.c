#include <stdio.h>
#include <stdlib.h>

void InsertionSort(int list[], int n) {
	int i, j, key; //key: (정렬된 리스트에) 삽입할 값을 복사해 두는 용도
	for (i = 1; i < n; i++) {//list[0]은 이미 정렬된 부분으로 보고, list[1]부터 정렬을 시작함
		key = list[i];
		//정렬된 리스트 안에서, key를 삽입할 위치를 찾는다.
		//i-1번째 ~ 0까지 역순으로 조사한다(i번째 요소와 비교)
		for (j = i - 1; j >= 0 && key < list[j]; j--)
			list[j + 1] = list[j]; //j번째 요소를 j+1번째에 복사(오른쪽으로 한칸 이동)
		list[j + 1] = key; //최종 위치에 key 삽입
	}
}

int main() {
	int list[] = { 3,5,8,2,7 };
	int n = sizeof(list) / sizeof(list[0]);

	//삽입정렬 호출
	InsertionSort(list, n);

	for (int i = 0; i < n; i++)
		printf("%d ", list[i]);
	printf("\n");

	return 0;
}
