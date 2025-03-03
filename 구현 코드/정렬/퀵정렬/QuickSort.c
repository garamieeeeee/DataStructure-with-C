#include <stdio.h>
#include <stdlib.h>
#define SWAP(x,y,t) ((t)=(x), (x) = (y), (y) = (t))

//left부터 right까지의 리스트에서 피봇을 선택해 피봇을 기준으로 두개의 리스트를 분할하고, 피봇의 위치를 반환한다
int Partition(int list[], int left, int right) {
	int pivot, temp;
	int low, high;

	low = left;
	high = right + 1;
	pivot = list[left];//리스트의 맨 왼쪽 값을 pivot으로 사용한다
	do {
		do
			low++;
		while (list[low] < pivot); //인덱스 변수 low는 pivot보다 큰 값을 만나면 멈춘다.
		do
			high--;
		while (list[high] > pivot); //인덱스 변수 high는 pivot보다 작은 값을 만나면 멈춘다.
		if (low < high) SWAP(list[low], list[high], temp); //low와 high의 값의 위치를 바꾼다.
	} while (low < high); //low와 high가 엇갈리게 되면 바로 멈춘다

	SWAP(list[left], list[high], temp); //그 상태에서 high이 가리키는 값과 피봇의 위치를 바꾸면, pivot이 분할된 두 리스트의 중앙에 오게 된다.(실제 배열이 변한다)
	//이제 pivot을 기준으로 왼쪽은 pivot보다 작은 값, pivot을 기준으로 오른쪽은 pivot보다 큰 값이 위치함 

	return high; //high은 피봇의 위치를 가리킴. 피봇의 위치를 리턴
}

void QuickSort(int list[], int left, int right) {
	if (left < right) {//더이상 분할 할 수 없을때까지, 즉 부분리스트 크기가 1이 될때까지
		int p = Partition(list, left, right); //partiotion 함수 호출: 피봇을 기준으로 리스트가 두개로 불균등하게 분할된다. p:피봇값의 위치
		QuickSort(list, left, p - 1); //left~p-1까지의 부분리스트에 대하여 다시 퀵정렬
		QuickSort(list, p + 1, right); //p+1~right까지의 부분리스트에 대하여 다시 퀵정렬
	}
	//계속해서 피봇을 뽑아서 리스트를 분할해가다보면 자동으로 리스트가 정렬되어있다.
}

int main() {
	int list[] = { 5,3,8,4,9,1,6,2,7 };
	int n = sizeof(list) / sizeof(list[0]);

	//퀵 정렬 호출
	QuickSort(list, 0, n - 1);
	
	for (int i = 0; i < n; i++)
		printf("%d ", list[i]);
	printf("\n");

	return 0;
}
