//양방향(+원형) 연결리스트

#include "DoublyCircularLinkedList.h"

void Error(char* message) {
	fprintf(stderr, "%s\n", message);
	exit(EXIT_FAILURE);
}

void Init(DListNode** head) { //헤드노드 생성 후 초기화
	*head = (DListNode*)malloc(sizeof(DListNode));
	if (*head == NULL) {
		Error("memory allocation failed");
	}

	(*head)->Llink = *head;
	(*head)->Rlink = *head;

	return;
}

int GetPos(DListNode* head, ElementType data) {
	DListNode* ptr;
	int i = 0;
	int Flag = 0;
	for (ptr = head->Rlink; ptr != head; ptr = ptr->Rlink) {
		if (ptr->data == data) {
			Flag = 1;
			break;
		}
		i++;
	}

	if (Flag) {
		return i;
	}
	else {
		printf("해당하는 데이터가 리스트에 없습니다.");
		return -1;
	}
}

int GetSize(DListNode* head) {
	DListNode* ptr;
	int i = 0;
	for (ptr = head->Rlink; ptr != head; ptr = ptr->Rlink) {
		i++;
	}

	return i;
}

DListNode* CreateNode(ElementType data) {
	DListNode* newNode = (DListNode*)malloc(sizeof(DListNode));
	if (!newNode) {
		Error("memory allocation failed");
	}
	newNode->data = data;
	newNode->Llink = NULL;
	newNode->Rlink = NULL;

	return newNode;
}

DListNode* GetNode(DListNode* head, int index) {

	//리스트가 비어있는지 확인
	if (head->Rlink == head) {
		Error("List is Empty");
	}

	//인덱스 범위 검사
	int size = GetSize(head);
	if (index < 0 || index >= size) {
		Error("인덱스가 리스트의 범위를 초과했습니다.");
	}

	DListNode* ptr;
	int i = 0;
	for (ptr = head->Rlink; ptr != head; ptr = ptr->Rlink) {
		if (i == index) {
			break;
		}
		i++;
	}

	return ptr;
}

void InsertFirst(DListNode* head, ElementType data) { //리스트 맨앞에 삽입(head노드 다음)
	DListNode* newNode = CreateNode(data);
	newNode->Llink = head;
	newNode->Rlink = head->Rlink;
	head->Rlink->Llink = newNode;
	head->Rlink = newNode;

	return;
}

void InsertLast(DListNode* head, ElementType data) {
	DListNode* newNode = CreateNode(data);
	newNode->Llink = head->Llink; //head->Llink: 마지막 노드
	newNode->Rlink = head; //새로운 마지막 노드인 newNode와 head를 연결
	head->Llink->Rlink = newNode;
	head->Llink = newNode;

	return;
}

void InsertAfter(DListNode* pre, ElementType data) { //선행노드 pre 뒤에 새로운 노드 추가
	//리스트가 비어있어도 헤드노드 뒤에 삽입하면 되므로 따로 처리하지않는다.

	DListNode* newNode = CreateNode(data);
	newNode->Llink = pre;
	newNode->Rlink = pre->Rlink;
	pre->Rlink->Llink = newNode;
	pre->Rlink = newNode;

	return;
}

void InsertBefore(DListNode* suc, ElementType data) {//후속노드 suc 앞에 새로운 노드 추가
	//리스트가 비어있으면(선행노드가 head인 경우) head노드 뒤에 삽입
	DListNode* newNode = CreateNode(data);
	newNode->Llink = suc->Llink;
	newNode->Rlink = suc;
	suc->Llink->Rlink = newNode;
	suc->Llink = newNode;

	return;
}

void InsertAt(DListNode* head, int index, ElementType data) {
	//index 범위 검사
	int size = GetSize(head);
	if (index < 0 || index > size) { //index == size인 경우는, 리스트의 마지막에 삽입하는 경우
		Error("인덱스가 리스트의 범위를 초과했습니다.");
		return;
	}

	DListNode* newNode = CreateNode(data);
	////리스트가 비어있는 경우
	if (head->Rlink == head) {
		if (index == 0) {//리스트가 비었고, 0번째에 삽입하는 경우: head 다음에 삽입한다.
			newNode->Llink = head;
			newNode->Rlink = head;
			head->Rlink = newNode;
			head->Llink = newNode;
		}
		else {//리스트가 비었는데 index가 0이 아닌 경우
			Error("리스트가 비었습니다. 인덱스 오류");
		}
		return;
	}

	////리스트가 비어있지 않은 경우
	if (index == size) {//리스트의 맨 끝에 삽입하는 경우
		newNode->Llink = head->Llink;
		newNode->Rlink = head;
		head->Llink->Rlink = newNode;
		head->Llink = newNode;
	}
	else { //리스트의 중간에 삽입하는 경우
		//index번 노드를 찾는다.
		DListNode* Ith = GetNode(head, index);

		//index번에 새로운 노드를 삽입하고 연결한다
		newNode->Llink = Ith->Llink;
		newNode->Rlink = Ith;
		Ith->Llink->Rlink = newNode;
		Ith->Llink = newNode;
	}
	return;
}

ElementType DeleteFirst(DListNode* head) {
	//리스트가 비어있다면 삭제할 수 없다.
	if (head->Rlink == head) {
		Error("리스트가 비었습니다. 삭제할 수 없습니다.");
	}

	ElementType removedData;
	DListNode* temp;
	temp = head->Rlink; //temp에 첫번째 노드의 주소 저장
	removedData = temp->data;
	temp->Rlink->Llink = head;
	head->Rlink = temp->Rlink;
	free(temp);

	return removedData;
}

ElementType DeleteLast(DListNode* head) {
	//리스트가 비어있다면 삭제할 수 없다.
	if (head->Rlink == head) {
		Error("리스트가 비었습니다. 삭제할 수 없습니다.");
	}
	ElementType removedData;
	DListNode* temp;
	temp = head->Llink; //temp에 마지막 노드의 주소 저장
	removedData = temp->data;
	temp->Llink->Rlink = head;
	head->Llink = temp->Llink;
	free(temp);

	return removedData;
}

ElementType DeleteThis(DListNode* head, ElementType data) {
	int pos = GetPos(head, data);

	////데이터가 리스트 안에 없는 경우
	if (pos == -1) {
		Error("삭제할 수 없습니다.");
	}

	////데이터가 리스트 안에 있는 경우
	ElementType removedData = DeleteAt(head, pos);
	return removedData;
}

ElementType DeleteAt(DListNode* head, int index) {
	//index의 범위 검사
	int size = GetSize(head);
	if (index < 0 || index >= size) {
		Error("인덱스가 리스트의 범위를 초과했습니다.");
	}

	//리스트가 비어있는지 검사
	if (head->Rlink == head) {
		Error("리스트가 비었습니다. 삭제할 수 없습니다.");
	}

	ElementType removedData;
	DListNode* removed;

	removed = GetNode(head, index); //삭제할 index번 노드 가져오기
	removedData = removed->data;

	removed->Rlink->Llink = removed->Llink;
	removed->Llink->Rlink = removed->Rlink;
	free(removed);

	return removedData;
}

void ConcatTwo(DListNode* head1, DListNode* head2, DListNode* head3) {
	if (head3->Rlink != head3) { //리스트 3이 비어있지 않으면 에러
		Error("리스트3이 빈 리스트가 아닙니다.");
	}

	DListNode* ptr;
	ElementType copiedData;

	for (ptr = head1->Rlink; ptr != head1; ptr = ptr->Rlink) {
		copiedData = ptr->data;
		InsertLast(head3, copiedData);
	}

	for (ptr = head2->Rlink; ptr != head2; ptr = ptr->Rlink) {
		copiedData = ptr->data;
		InsertLast(head3, copiedData);
	}

	return;
}

void Reverse(DListNode* head) {

	//리스트를 처음부터 끝까지 한바퀴 순회할 포인터 ptr
	DListNode* ptr = head->Rlink; //ptr은 첫 노드부터 시작
	//역순으로 바꾸는 과정에서 임시로 노드의 주소를 저장할 포인터 변수 temp
	DListNode* temp = NULL;

	while (ptr != head) { //ptr은 마지막 노드까지 방문하고 루프가 끝남
		temp = ptr->Rlink; //temp: ptr의 다음 노드의 주소를 저장해둠

		//ptr의 Rlink와 Llink를 서로 교환한다.
		ptr->Rlink = ptr->Llink; //ptr->Llink: ptr의 이전 노드
		ptr->Llink = temp; //temp: ptr의 다음 노드

		ptr = ptr->Llink; //ptr을 다음 노드로 넘긴다. 이미 ptr의 Llink와 Rlink는 서로 바뀌었으므로, 다음노드로 넘어가려면 Llink를 따라가야함
	}

	//리스트의 모든 노드는 역순으로 바뀌었다.
	//마지막으로, head노드의 Rlink와 Llink를 갱신해준다.

	//이제 head의 Rlink는 역순 리스트의 첫번째 노드(기존 리스트의 마지막 노드)를 가리켜야하고,
	//head의 Llink는 역순 리스트의 마지막 노드(기존 리스트의 첫번째 노드)를 가리켜야한다.
	temp = head->Llink; // temp: 기존 리스트의 마지막 노드의 주소를 저장해둠
	head->Llink = head->Rlink; //head->Rlink: 기존 리스트의 첫번째 노드
	head->Rlink = temp; // temp: 기존 리스트의 마지막 노드	

	return;
}

void Clear(DListNode* head) {
	while (head->Rlink != head) { //리스트가 비어있지 않는 동안에
		DeleteLast(head); //항상 마지막 노드를 삭제
	}
	return;
}

void PrintList(DListNode* head) {
	DListNode* ptr;
	printf("[ HEAD ");
	int i = 0;
	for (ptr = head->Rlink; ptr != head; ptr = ptr->Rlink) {
		printf("<- [%d] %d -> ", i, ptr->data);
		i++;
	}
	printf("]\n\n");
	return;
}
