#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 10

void Merge(int list[], int left, int mid, int right) { //합병 과정에서 쓰는 함수
	int i, j, k;//i: 정렬된 왼쪽 리스트에 대한 인덱스, j: 정렬된 오른쪽 리스트에 대한 인덱스, k: 합병될 리스트(sorted)에 대한 인덱스
	int sorted[MAX_SIZE];//합병된 리스트를 임시저장할 배열이 필요함
	i = left, j = mid + 1, k = 0; //list의 left~mid까지가 정렬된 왼쪽 리스트, list의 mid+1~right까지가 오른쪽 리스트

	//두개의 리스트를 처음부터 끝까지 한칸씩 비교하여 둘중에 더 작은 요소를 sorted에 저장한다.
	while (i <= mid && j <= right) {
		if (list[i] <= list[j])
			sorted[k++] = list[i++];
		else
			sorted[k++] = list[j++];
	}

	while (i <= mid) { //오른쪽 리스트가 먼저 끝난 경우: 나머지 왼쪽 리스트를 sorted에 복사
		sorted[k++] = list[i++];
	}
	while (j <= right) {//왼쪽 리스트가 먼저 끝난 경우: 나머지 오른쪽 리스트를 sorted에 복사
		sorted[k++] = list[j++];
	}

	k = 0;
	//sorted에 합병된 리스트를 전체 복사하여 원래의 리스트에 저장한다.
	for (int l = left; l <= right; l++)
		list[l] = sorted[k++];
}

void MergeSort(int list[], int left, int right) {
	int mid = (left + right) / 2; //리스트의 균등 분할

	//더 쪼갤 수 없을때까지 계속 절반크기로 나눈다. 크기가 1이될때까지, 즉 left == right가 될때까지
	if (left < right) {
		MergeSort(list, left, mid); //부분 리스트(first~mid)에 대하여 다시 합병정렬(순환호출)
		MergeSort(list, mid + 1, right); //부분 리스트(mid+1~last)에 대하여 다시 합병정렬(순환호출)
		//정렬된 두개의 리스트(왼쪽 리스트/오른쪽 리스트)에 대하여 합병 작업
		Merge(list, left, mid, right);
	}
}

int main() {
	int list[] = { 27, 10, 12, 20, 25, 13, 15, 22 };
	int n = sizeof(list) / sizeof(list[0]);

	//합병 정렬 호출
	MergeSort(list, 0, n - 1);

	for (int i = 0; i < n; i++)
		printf("%d ", list[i]);
	printf("\n");

	return 0;
}
