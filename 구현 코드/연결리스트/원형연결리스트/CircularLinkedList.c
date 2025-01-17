//(단방향) 원형 연결리스트

#include "CircularLinkedList.h"

void Error(char* message) {
	fprintf(stderr, "%s\n", message);
	exit(EXIT_FAILURE);
}

void Init(CListNode** head) {
	*head = NULL;
}

int IsEmpty(CListNode* head) {
	//리스트가 비어있다면 head->link(첫번째 노드) == head(마지막 노드) == NULL일테니
	//head == NULL 인지만 확인하면 됨.
	//만약 노드가 하나라도 있다면 head->link(첫번째 노드) != NULL && head(마지막 노드) != NULL
	return (head == NULL);
}

int GetPos(CListNode* head, ElementType data) {
	//리스트가 비었는지 검사
	if (IsEmpty(head)) {
		Error("List is Empty");
	}

	CListNode* ptr;
	ptr = head->link; //ptr은 맨 첫 노드부터 시작
	int Flag = 0;
	int i = 0;

	do {
		if (ptr->data == data) {
			Flag = 1;
			break;
		}
		ptr = ptr->link;
		i++;
	} while (ptr != head->link); //ptr이 맨 첫 노드로 돌아오면 끝남(마지막 노드까지 확인하고 끝)

	if (Flag) { //index 값을 찾았으면
		return i;
	}
	else {
		printf("해당하는 데이터가 리스트에 없습니다.");
		return -1;
	}
}

int GetSize(CListNode* head) {

	if (IsEmpty(head)) {
		printf("리스트가 비었습니다.\n");
		return 0;
	}

	CListNode* ptr;
	ptr = head->link; //ptr은 맨 첫 노드부터 시작
	int i = 0;

	do {
		ptr = ptr->link;
		i++;
	} while (ptr != head->link); //ptr이 맨 첫 노드로 돌아오면 끝남(마지막 노드까지 세고 끝)

	return i;
}

CListNode* CreateNode(ElementType data) {
	CListNode* newNode;
	newNode = (CListNode*)malloc(sizeof(CListNode));
	if (!newNode) {
		Error("memory allocation failed");
	}
	newNode->data = data;
	newNode->link = NULL;

	return newNode;
}

CListNode* GetNode(CListNode* head, int index) {

	//리스트가 비어있는지 확인
	if (IsEmpty(head)) {
		Error("List is Empty");
	}

	//인덱스 범위 검사
	int size = GetSize(head);
	if (index < 0 || index >= size) {
		Error("인덱스가 리스트의 범위를 초과했습니다.");
	}

	CListNode* ptr;
	ptr = head->link; //ptr은 맨 첫 노드부터 시작
	int i = 0;
	do {
		if (i == index) {
			break;
		}
		ptr = ptr->link;
		i++;
	} while (ptr != head->link); //ptr이 맨 첫 노드로 돌아오면 끝남(마지막 노드까지 세고 끝)

	return ptr;
}

void InsertFirst(CListNode** head, ElementType data) {
	CListNode* newNode = CreateNode(data);

	if (IsEmpty(*head)) { //리스트가 비었으면
		*head = newNode;
		newNode->link = *head;
		return;
	}
	else {//노드가 하나라도 있으면
		newNode->link = (*head)->link;
		(*head)->link = newNode;
		return;
	}
}

void InsertLast(CListNode** head, ElementType data) {
	CListNode* newNode = CreateNode(data);

	if (IsEmpty(*head)) { //리스트가 비었으면
		*head = newNode;
		newNode->link = *head;
		return;
	}
	else {//노드가 하나라도 있으면
		newNode->link = (*head)->link;
		(*head)->link = newNode;
		*head = newNode;
		return;
	}
}

void InsertAfter(CListNode** head, CListNode* pre, ElementType data) { //pre 노드 뒤에 새로운 노드 삽입, 리스트는 비어있지않다(최소 pre 노드 한개는 있음)라고 가정

	int Flag = 0;
	if (pre == *head) { //pre가 마지막 노드인지부터 확인
		Flag = 1;
	}

	//pre 뒤에 새로운 노드를 추가하고 연결하기
	CListNode* newNode = CreateNode(data);
	newNode->link = pre->link;
	pre->link = newNode;

	//만약 pre가 리스트의 마지막 노드라면
	//head 포인터가 pre 뒤에 추가된 새로운 마지막 노드를 가리키도록 갱신해줘야 함
	if (Flag) {
		*head = newNode;
	}
	return;
}

void InsertAt(CListNode** head, int index, ElementType data) {

	//index 범위 검사
	int size = GetSize(*head);
	if (index < 0 || index > size) { //index == size인 경우는, 리스트의 마지막에 삽입하는 경우
		Error("인덱스가 리스트의 범위를 초과했습니다.");
		return;
	}

	CListNode* newNode = CreateNode(data);
	CListNode* ptr = NULL;

	////리스트가 비어있는 경우
	if (IsEmpty(*head)) {
		if (index == 0) {//리스트가 비었고, 0번째에 삽입하는 경우
			*head = newNode;
			newNode->link = *head;
		}
		else {//리스트가 비었는데 index가 0이 아닌 경우
			Error("리스트가 비었습니다. 인덱스 오류");
		}
		return;
	}

	////리스트가 비어있지 않은 경우
	if (index == 0) { //리스트의 맨 처음에 삽입하는 경우
		newNode->link = (*head)->link;
		(*head)->link = newNode;
	}
	else if (index == size) { //리스트의 맨 끝에 삽입하는 경우
		//마지막 노드 뒤에 삽입한 후 head 포인터를 갱신해준다.

		ptr = (*head)->link; //ptr은 맨 첫번째 노드를 가리키도록 해둠
		(*head)->link = newNode; //마지막 노드와 newNode를 연결
		newNode->link = ptr; //새로운 마지막 노드인 newNode와 맨 첫번째 노드를 연결

		(*head) = newNode; //head포인터가 newNode를 가리키도록 갱신
		return;
	}
	else { //리스트의 중간에 삽입하는 경우
		//선행노드를 찾아야 함
		ptr = (*head)->link; //ptr은 맨 첫 노드부터 시작
		int i = 0;
		do {
			if (i == index - 1) {
				break;
			}
			ptr = ptr->link;
			i++;
		} while (ptr != (*head)->link); //리스트를 처음부터 끝까지 한바퀴 돌면서 index-1번째 노드(선행노드)를 찾음

		//ptr이 index-1번 노드를 가리키게 됨
		newNode->link = ptr->link;
		ptr->link = newNode;
		return;
	}
}

ElementType DeleteFirst(CListNode** head) {

	////리스트가 비어있는지 검사
	if (IsEmpty(*head)) { //노드가 0개인 경우
		Error("리스트가 비었습니다. 삭제할 수 없습니다.");
	}

	////빈 리스트가 아닌 경우
	CListNode* temp = (*head)->link; //temp는 첫번째 노드를 가리킴
	ElementType removedData = temp->data;

	temp = (*head)->link; //temp는 첫번째 노드를 가리킴
	if ((*head)->link == *head) { //노드가 1개인 경우
		*head = NULL; //공백 리스트로 변경
	}
	else {//노드가 2개 이상인 경우
		(*head)->link = temp->link; //마지막 노드의 링크를 삭제할 노드의 다음 노드와 연결
	}
	free(temp); //노드 삭제

	return removedData;
}

ElementType DeleteLast(CListNode** head) {

	////리스트가 비어있는지 검사
	if (IsEmpty(*head)) { //노드가 0개인 경우
		Error("리스트가 비었습니다. 삭제할 수 없습니다.");
	}

	CListNode* temp = *head; //temp는 마지막 노드를 가리킴
	ElementType removedData = temp->data;

	////빈 리스트가 아닌 경우
	if (temp->link == *head) { //노드가 1개인 경우
		*head = NULL; //공백 리스트로 변경
	}
	else {//노드가 2개 이상인 경우: 삭제할 노드의 선행 노드를 알아내야한다 & head 포인터를 변경해줘야 한다.
		CListNode* pre; //pre는 삭제할 노드의 선행노드
		pre = temp->link; //첫번째 노드부터 탐색 시작
		while (pre->link != *head) { //pre->link가 마지막 노드가 되면 끝남
			pre = pre->link;
		}
		pre->link = temp->link; //pre의 링크를 첫번째 노드와 연결
		*head = pre; //head를 새로운 마지막 노드인 pre로 갱신
	}
	free(temp); //노드 삭제

	return removedData;
}

ElementType DeleteThis(CListNode** head, ElementType data) {
	//리스트가 비어있는지 검사
	if (IsEmpty(*head)) {
		Error("리스트가 비었습니다. 삭제할 수 없습니다.");
	}

	//데이터가 리스트 안에 있는지 확인
	int pos = GetPos(*head, data);
	ElementType removedData;
	if (pos == -1) { //GetPos의 값이 -1인 경우(리스트 안에 해당 데이터가 없는 경우)
		Error("리스트 안에 있는 값이 아닙니다. 삭제할 수 없습니다.");
	}
	else { //리스트 안에 있다면 pos 위치의 데이터를 삭제
		removedData = DeleteAt(head, pos);
		return removedData;
	}
}

ElementType DeleteAt(CListNode** head, int index) {
	//index의 범위 검사
	int size = GetSize(*head);
	if (index < 0 || index >= size) {
		Error("인덱스가 리스트의 범위를 초과했습니다.");
	}

	//리스트가 비어있는지 검사
	if (IsEmpty(*head)) {
		Error("리스트가 비었습니다. 삭제할 수 없습니다.");
	}

	// removed는 삭제할 노드, pre는 삭제할 노드의 선행노드
	ElementType removedData;
	CListNode* pre = NULL;
	CListNode* removed = NULL;

	//리스트가 비어있지 않은 경우
	if (size == 1) {//노드가 한개만 있음
		removed = *head; //removed는 유일한 맨 첫 노드를 가리킴
		removedData = removed->data;
		*head = NULL; //공백 리스트로 변경
	}
	else if (index == 0) {//노드가 2개 이상, 맨 첫 노드를 삭제
		removed = (*head)->link; //removed는 맨 첫 노드를 가리킴
		removedData = removed->data;
		(*head)->link = removed->link; //삭제할 맨 첫번째 노드 temp 다음 노드를 시작노드로 만듦
	}
	else if (index == size - 1) {//노드가 2개 이상, 맨 마지막 노드를 삭제
		//삭제할 노드의 선행 노드를 알아내야한다
		removed = *head; //removed는 삭제할 맨 마지막 노드를 가리킴
		removedData = removed->data;

		pre = (*head)->link; //pre는 첫번째 노드부터 시작
		while (pre->link != *head) { //pre->link가 마지막 노드가 되면 끝남
			pre = pre->link;
		}
		//pre는 마지막 노드의 선행노드
		pre->link = removed->link; //pre의 링크를 첫번째 노드와 연결
		*head = pre; //head를 새로운 마지막 노드인 pre로 갱신
	}
	else {//노드가 2개 이상, 중간 노드를 삭제
		//삭제할 노드의 선행 노드를 알아내야한다
		pre = (*head)->link; //pre는 맨 첫 노드부터 시작
		int i = 0;
		do {
			if (i == index - 1) {
				break;
			}
			pre = pre->link;
			i++;
		} while (pre != (*head)->link); //리스트를 처음부터 끝까지 한바퀴 돌면서 index-1번째 노드(선행노드)를 찾음

		//pre가 index-1번 노드를 가리키게 됨
		removed = pre->link; //removed는 삭제할 노드
		removedData = removed->data;

		pre->link = removed->link; //pre와 삭제할 노드의 다음 노드를 연결
	}
	free(removed);
	return removedData;
}

void ConcatTwo(CListNode** head1, CListNode** head2, CListNode** head3) {

	////리스트3이 비어있는지 확인
	if (!IsEmpty(*head3)) {
		Error("리스트3이 비어있는 리스트가 아닙니다.");
	}

	////리스트1, 2가 비어있는지 확인
	ElementType copiedData;
	int size = 0;

	//리스트1, 2가 둘 다 비어있는 경우
	if (*head1 == NULL && *head2 == NULL) {
		return;
	}//1번 리스트만 비어있는 경우
	else if (*head1 == NULL) {
		size = GetSize(*head2);
		for (int i = 0; i < size; i++) {
			copiedData = GetNode(*head2, i)->data;
			InsertLast(head3, copiedData);
		}

		return;
	}//2번 리스트만 비어있는 경우
	else if (*head2 == NULL) {
		size = GetSize(*head1);
		for (int i = 0; i < size; i++) {
			copiedData = GetNode(*head1, i)->data;
			InsertLast(head3, copiedData);
		}

		return;
	}
	else {//둘 다 빈 리스트가 아닌 경우
		size = GetSize(*head1);
		for (int i = 0; i < size; i++) {
			copiedData = GetNode(*head1, i)->data;
			InsertLast(head3, copiedData);
		}

		size = GetSize(*head2);
		for (int i = 0; i < size; i++) {
			copiedData = GetNode(*head2, i)->data;
			InsertLast(head3, copiedData);
		}

		return;
	}
}

void Reverse(CListNode** head) {
	////리스트가 비었는지 확인
	if (IsEmpty(*head)) {
		printf("리스트가 비어있습니다.\n");
		return;
	}

	////리스트의 노드가 1개뿐인지 확인
	if (*head == (*head)->link) {
		return;
	}

	////노드가 2개 이상이면 역순으로 바꾼다.

	//first: 기존 리스트의 첫번째 노드(역순 리스트의 마지막 노드)의 주소 저장해둠
	CListNode* first = (*head)->link;

	CListNode* prev = NULL; //prev: current의 하나 앞 노드를 가리킴. 즉 current의 선행노드를 가리킴 
	CListNode* current = *head; //current: 기존 리스트의 마지막 노드부터 하나씩 순회하며, 링크를 역순으로 바꾼다(current의 링크가 선행노드인 prev를 가리키도록)
	CListNode* next = NULL; //next: current가 넘어갈 다음 노드의 주소를 저장해두는 포인터

	do {
		next = current->link;
		current->link = prev;
		prev = current;
		current = next;
	} while (current != *head);
	//current는 기존 리스트의 마지막 노드를 가리키는 상태
	//prev는 기존 리스트의 맨 마지막 노드의 앞 노드를 가리키는 상태

	//while문이 끝나면, 리스트의 모든 노드의 링크가 역순으로 바뀌었으나 cur과 prev 사이에만 링크가 연결되어있지 않음
	//마찬가지로 cur->prev 순서로(역순) 연결해주면 리스트의 모든 노드가 역순으로 연결됨
	current->link = prev;

	//마지막으로 head 포인터를 갱신해줘야함
	//역순으로 바뀐 리스트에서는 head 포인터가 역순 리스트의 마지막 노드를 가리켜야한다.
	//처음에 first에 기존 리스트의 첫번째 노드(=역순으로 바뀐 리스트의 마지막 노드)의 주소를 저장해 두었음
	*head = first;

	return;
}

void Clear(CListNode** head) {
	if (*head == NULL) {
		return; // 리스트가 비어있으면 바로 반환
	}

	CListNode* removed;
	CListNode* ptr;

	ptr = (*head)->link; //ptr에 시작 노드의 주소 저장

	//리스트를 단순 연결리스트로 변경
	(*head)->link = NULL;

	while (ptr != NULL) {
		removed = ptr; //삭제할 노드를 removed에 담아놓고
		ptr = ptr->link; //ptr은 다음 칸으로 넘어간다.
		free(removed); //removed 삭제
	}

	*head = NULL; // 모든 노드가 해제된 후 head를 NULL로 설정
	return;
}

void PrintList(CListNode* head) {

	//리스트가 비어있는지 검사
	if (IsEmpty(head)) {
		printf("[ ]\n\n");
		return;
	}

	CListNode* ptr;
	ptr = head->link; //ptr: 첫번째 노드를 가리킴

	int i = 0;
	printf("[ ");
	do {
		printf("[%d] %d", i, ptr->data);
		if (ptr->link != head->link) {//마지막 노드가 아닌 경우
			printf(" -> ");
		}
		ptr = ptr->link;
		i++;
	} while (ptr != head->link); //첫번째 노드로 돌아오면 끝남
	printf(" ]\n\n");

	return;
}
