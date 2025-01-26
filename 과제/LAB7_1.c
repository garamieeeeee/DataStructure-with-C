#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;

typedef struct ListNode {
	ElementType data;
	struct ListNode* link;
}ListNode;

void ReadFile(const char* fileName, ListNode** head);
void Error(char* message);
int IsEmpty(ListNode* head);
int GetSize(ListNode* head);
ListNode* CreateNode(ElementType data);
ListNode* GetNode(ListNode* head, int index);
void InsertLast(ListNode** head, ElementType data);
void InsertAfter(ListNode* pre, ElementType data);
ElementType DeleteAt(ListNode** head, int index);
void PrintList(ListNode* head);
void PrintMenu();

int main(int argc, char* argv[]) {

	//인자 검사
	if (argc < 2) { //argv[0]:파일 경로, argv[1]: input.txt
		fprintf(stderr, "[Usage] %s <input.txt>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	ListNode* head = NULL;
	ReadFile(argv[1], &head);
	printf("chain: ");
	PrintList(head);

	PrintMenu();
	int c, index, data;
	while (1) {
		printf("Menu: ");
		scanf("%d", &c);

		switch (c) {
		case 1: printf("insert(n번째 노드 다음 m을 삽입):");
			scanf("%d %d", &index, &data); //n번째 노드: index [n-1]의 노드
			ListNode* nth = GetNode(head, index - 1); //n번째 노드 가져오기
			InsertAfter(nth, data); //n번째 노드 뒤에 m 삽입
			printf("result: ");
			PrintList(head);
			break;
		case 2: printf("delete(n번째 노드를 삭제): ");
			scanf("%d", &index); //n번째 노드: index[n-1]의 노드
			DeleteAt(&head, index - 1); //n번째 노드 삭제
			printf("result: ");
			PrintList(head);
			break;
		case 3: printf("length: %d\n\n", GetSize(head)); break;
		case 4: printf("exit"); exit(0);
		default: printf("잘못된 번호입니다. 다시 입력하세요.\n\n"); break;
		}
	}

	return 0;
}

void ReadFile(const char* fileName, ListNode** head) {//파일을 읽고 초기 리스트 생성
	FILE* file = fopen(fileName, "r");
	if (!file) {
		Error("file open failed\n");
	}

	int c;
	while (fscanf(file, "%d", &c) != EOF) {
		InsertLast(head, c);
	}

	fclose(file);

	return;
}

void Error(char* message) {
	fprintf(stderr, "%s\n", message);
	exit(EXIT_FAILURE);
}

int IsEmpty(ListNode* head) {
	return (head == NULL);
}

int GetSize(ListNode* head) {

	if (IsEmpty(head)) {
		printf("리스트가 비었습니다.\n");
		return 0;
	}

	ListNode* ptr;
	ptr = head;
	int i = 0;

	while (ptr != NULL) {
		ptr = ptr->link;
		i++;
	}

	return i;
}


ListNode* CreateNode(ElementType data) {
	ListNode* newNode;
	newNode = (ListNode*)malloc(sizeof(ListNode));
	if (!newNode) {
		Error("memory allocation failed");
	}
	newNode->data = data;
	newNode->link = NULL;

	return newNode;
}

ListNode* GetNode(ListNode* head, int index) {

	//리스트가 비어있는지 확인
	if (IsEmpty(head)) {
		Error("List is Empty");
	}

	//인덱스 범위 검사
	int size = GetSize(head);
	if (index < 0 || index >= size) {
		Error("인덱스가 리스트의 범위를 초과했습니다.");
	}

	ListNode* ptr;
	ptr = head;
	int i = 0;
	while (ptr != NULL) {
		if (i == index) {
			break;
		}
		ptr = ptr->link;
		i++;
	}

	return ptr;
}

void InsertLast(ListNode** head, ElementType data) {

	ListNode* newNode = CreateNode(data);

	if (IsEmpty(*head)) {//리스트가 비었으면
		*head = newNode;
		return;
	}
	else {
		ListNode* ptr;
		ptr = *head;
		while (ptr->link != NULL) {
			ptr = ptr->link;
		}
		//ptr이 마지막 노드를 가리키게 됨
		ptr->link = newNode;
		return;
	}
}

void InsertAfter(ListNode* pre, ElementType data) { //선행노드 pre가 무조건 있다(리스트에 노드가 하나는 있다)고 전제
	ListNode* newNode = CreateNode(data);
	newNode->link = pre->link;
	pre->link = newNode;
}

ElementType DeleteAt(ListNode** head, int index) {
	//index의 범위 검사
	int size = GetSize(*head);
	if (index < 0 || index >= size) {
		Error("인덱스가 리스트의 범위를 초과했습니다.");
	}

	//리스트가 비어있는지 검사
	if (IsEmpty(*head)) {
		Error("리스트가 비었습니다. 삭제할 수 없습니다.");
	}

	ElementType removedData;
	ListNode* removed;
	removed = *head; //removed는 맨 첫 노드를 가리킴

	////리스트가 비어있지 않고, 맨 첫 노드를 삭제하는 경우
	if (index == 0) {
		removedData = removed->data;
		*head = (*head)->link;
		free(removed);

		return removedData;
	}

	////리스트가 비어있지 않고, 중간이나 끝 노드를 삭제하는 경우
	ListNode* pre;
	pre = *head;
	int i = 0;
	while (pre != NULL) { //삭제할 노드의 선행노드 알아내기
		if (i == index - 1) {
			break;
		}
		pre = pre->link;
		i++;
	}
	removed = pre->link;

	//pre는 삭제할 i번째 노드의 선행 노드를 가리킴
	//removed는 삭제할 i번째 노드를 가리킴
	removedData = removed->data;
	pre->link = removed->link; //삭제할 노드의 앞노드와 뒤노드를 연결
	free(removed); //i번째 노드 삭제

	return removedData;
}

void PrintList(ListNode* head) {

	ListNode* ptr;
	ptr = head;

	int i = 0;
	while (ptr != NULL) {
		printf("%d   ", ptr->data);
		ptr = ptr->link;
		i++;
	}
	printf("\n\n");
}

void PrintMenu() {
	printf("\n");
	printf(" +----------------+\n");
	printf("   1. insert\n\n");
	printf("   2. delete\n\n");
	printf("   3. length\n\n");
	printf("   4. exit\n");
	printf(" +----------------+\n");
}
