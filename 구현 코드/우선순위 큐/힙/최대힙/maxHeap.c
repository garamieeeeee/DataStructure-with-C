//max heap의 삽입,삭제 연산 & 최대힙을 이용해 자료를 오름차순으로 정렬하는 연산

//최대 힙
#include "maxHeap.h"

HeapType* CreateHeap() { //힙 구조체를 생성하고 초기화하여 포인터를 반환함
	HeapType* h = (HeapType*)malloc(sizeof(HeapType));
	if (!h) {
		fprintf(stderr, "memory allocation failed.\n");
		exit(EXIT_FAILURE);
	}
	//힙 초기화
	h->heapSize = 0;
	return h;
}

void Insert_maxHeap(HeapType* h, ElementType newNode) { //최대 힙 h에 새로운 노드 new를 삽입 
	//힙 크기를 하나 증가시키고, 힙의 맨 마지막 요소로 new가 들어간다고 생각
	h->heapSize++;
	int i = h->heapSize; //i번에 new 노드가 있다고 생각

	//i번의 new 노드를 부모노드인 i/2번 노드와 비교한다. 이런식으로 i /= 2되면서 위로 올라가며 new가 들어갈 자리를 찾는다.
	//도중에 (i번)new의 key가 (i/2번) 부모노드의 키보다 작거나 같아지면 더 이상 올라가지 않고 멈춘다. 그자리에 new를 삽입한다.
	// i==1, 즉 루트노드 위치까지 오면 비교를 멈추고 그 자리에 new를 삽입한다.
	while ((i != 1) && (newNode.key > h->heap[i / 2].key)) {
		h->heap[i] = h->heap[i / 2]; //만약 i번 키가 부모노드인 i/2번 노드의 키보다 크다면, i/2번 노드가 밑으로 내려와야한다. 부모노드를 자식노드의 위치로 끌어내린다.
		i /= 2; //이제 new노드는 i/2번의 위치에 있는 것이므로 i를 갱신해준다.
	}

	//while문이 끝나면, i번이 최종적으로 new가 들어갈 자리이다.
	h->heap[i] = newNode; //new 삽입
}

ElementType Delete_maxHeap(HeapType* h) { //루트노드(=최댓값)을 삭제하여 그 값을 반환
	ElementType removed = h->heap[1]; //removed: 삭제될 루트노드
	ElementType temp = h->heap[h->heapSize]; //temp: 힙의 마지막 노드
	//루트노드가 삭제되었으므로 힙 사이즈를 한칸 줄인다.
	h->heapSize--;

	//temp가 삭제된 루트노드의 자리에 올라갔다고 생각
	//루트노드의 위치(1번)에서부터 자식노드(2번...)와 비교하면서, temp가 들어갈 위치를 찾으며 내려온다.
	int parent = 1; //루트노드의 번호
	int child = 2; //루트노드의 왼쪽 자식의 번호

	while (child <= h->heapSize) { //child가 heapSize보다 커지면, 즉 트리의 마지막 노드까지 비교했는데 temp가 더 작다면 그 위치에 temp가 들어가야한다.
		//현재 노드의 자식노드(왼쪽/오른쪽) 중에서 더 큰 값을 찾는다. 둘 중에 더 큰 노드와 temp가 교환된다.
		if ((child < h->heapSize) && h->heap[child].key < h->heap[child + 1].key) { //만약 오른쪽 자식이 더 크다면
			child++; //오른쪽 노드와 temp를 비교해야 함. 만약 왼쪽 자식이 더 크다면 ++하지 않는다
		}
		if (temp.key >= h->heap[child].key) break; //temp의 키가 자식노드보다 커졌다면 알맞은 위치를 찾은 것이므로 이제 더 내려갈 필요 없다.
		//temp의 키가 자식노드보다 작은 것이므로, 자식노드가 위로 올라와야 함
		h->heap[parent] = h->heap[child]; //자식노드를 부모노드의 위치로 끌어올린다.

		parent = child; //이제 temp는 자식노드의 위치에 있는 것이므로 parent를 child 위치로 내려준다.

		child *= 2; //내려온 후 또 다시 자식노드와 비교해야하므로 인덱스*2해서 왼쪽자식으로 내려온다
	}

	//이제 parent는 temp가 들어갈 위치의 번호임
	h->heap[parent] = temp; //temp 위치 갱신

	return removed; //삭제한 루트노드 반환
}

void PrintHeap(HeapType* h) {//완전이진트리의 노드 번호 순서대로 출력하는 함수
	for (int i = 1; i <= h->heapSize; i++) {
		printf("[%d] %d\n", i, h->heap[i].key);
	}
}

void HeapSort(ElementType e[], int n) { //최대 히프를 이용해 오름차순으로 정렬하는 함수(n: 배열의 크기)
	HeapType* h = CreateHeap();
	for (int i = 0; i < n; i++) { //힙에 요소 차례로 삽입
		Insert_maxHeap(h, e[i]);
	}
	for (int i = n - 1; i >= 0; i--) { //힙에서 하나씩 삭제하면서 배열의 뒤쪽부터 저장
		e[i] = Delete_maxHeap(h);
	}
	//힙 사용이 끝났으니 메모리 해제
	free(h);
}
