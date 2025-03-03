#include <stdio.h>
#include <stdlib.h>

//gap만큼 떨어진 요소들을 삽입정렬
void Gapped_InsertionSort(int list[], int first, int last, int gap) {
	//삽입정렬과 똑같이 한다(정렬의 범위:first에서 last까지)
	//요소들의 간격이 1이 아닌 gap
	int i, j, key; //key:삽입할 값을 복사해두는 용도
	for (i = first + gap; i <= last; i += gap) {
		//첫번째 요소(first)는 이미 정렬된 것으로 보고, first+gap부터 정렬을 시작함
		key = list[i];
		//정렬된 리스트 안에서, key를 삽입할 위치를 찾는다.
		//i-gap번째 ~ first까지 역순으로 조사한다(i번째 요소와 비교)
		for (j = i - gap; j >= first && key < list[j]; j -= gap)
			list[j + gap] = list[j]; //j번째 요소를 j+gap번째에 복사(오른쪽으로 한칸 이동)
		list[j + gap] = key; //최종 위치에 key 삽입
	}
}

void ShellSort(int list[], int n) {
	int i, gap;
	for (gap = n / 2; gap > 0; gap /= 2) {
		//처음 간격은 n/2에서부터 시작해서 절반씩 줄어든다. 간격 크기 1이 될때까지
		//gap만큼 떨어진 요소들(부분리스트)을 각각 삽입정렬
		if (gap % 2 == 0) gap++; //gap이 짝수이면 +1 해주는 것이 좋다
		for (i = 0; i < gap; i++) //부분 리스트의 개수는 gap
			Gapped_InsertionSort(list, i, n - 1, gap);
	}
}

int main() {
	int list[] = { 10, 8, 6, 20, 4, 3, 22, 1, 0, 15, 16 };
	int n = sizeof(list) / sizeof(list[0]);

	//쉘 정렬 호출
	ShellSort(list, n);

	for (int i = 0; i < n; i++)
		printf("%d ", list[i]);
	printf("\n");

	return 0;
}
