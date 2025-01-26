#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int ElementType;

typedef struct ListNode {
	ElementType data;
	struct ListNode* link;
}ListNode;

void ReadFile(const char* fileName, ListNode** head1, ListNode** head2);
void WriteFile(const char* fileName, ListNode* head);
void Error(char* message);
int IsEmpty(ListNode* head);
int GetSize(ListNode* head);
ListNode* CreateNode(ElementType data);
ListNode* GetNode(ListNode* head, int index);
void InsertLast(ListNode** head, ElementType data);
void ConcatTwo(ListNode** head1, ListNode** head2, ListNode** head3);
void PrintList(ListNode* head);

int main(int argc, char* argv[]) {
	
	//인자 검사
	if (argc < 3) { //argv[0]:파일 경로, argv[1]: input.txt, argv[2]: output.txt
		fprintf(stderr, "[Usage] %s <input.txt> <output.txt> \n", argv[0]);
		exit(EXIT_FAILURE);
	}

	//리스트1, 리스트2 생성
	ListNode* head1 = NULL;
	ListNode *head2 = NULL;
	ReadFile(argv[1], &head1, &head2);

	//리스트1에 리스트2를 이어붙인 리스트 3 생성
	ListNode* head3 = NULL;
	ConcatTwo(&head1, &head2, &head3);
	
	//리스트1, 리스트2, 리스트3
	printf("리스트1: "); PrintList(head1);
	printf("리스트2: "); PrintList(head2);
	printf("리스트3: "); PrintList(head3);

	//output.txt에 리스트3 출력
	WriteFile(argv[2], head3);

	return 0;
}

void ReadFile(const char* fileName, ListNode** head1, ListNode** head2) {//파일을 읽고 2개의 리스트 생성
	FILE* file = fopen(fileName, "r");
	if (!file) {
		Error("file open failed\n");
	}

	char buffer[256]; //한줄씩 읽기 위한 버퍼

	//첫번째 줄 읽기
	if (fgets(buffer, sizeof(buffer), file) != NULL) { //fgets: 한줄씩 읽기
		char* token = strtok(buffer, " ");//공백을 기준으로 토큰화
		while (token != NULL) {
			int value = atoi(token); ///문자열을 정수로 변환
			InsertLast(head1, value); //정수값을 노드에 삽입
			token = strtok(NULL, " "); //다음 토큰 읽기
		}
	}

	//두번째 줄 읽기
	if (fgets(buffer, sizeof(buffer), file) != NULL) { //fgets: 한줄씩 읽기
		char* token = strtok(buffer, " ");//공백을 기준으로 토큰화
		while (token != NULL) {
			int value = atoi(token); ///문자열을 정수로 변환
			InsertLast(head2, value); //정수값을 노드에 삽입
			token = strtok(NULL, " "); //다음 토큰 읽기
		}
	}
	
	fclose(file);

	return;
}

void WriteFile(const char* fileName, ListNode* head) { //리스트 3을 output파일에 출력
	
	FILE* file = fopen(fileName, "w");
	if (!file) {
		Error("file open failed\n");
	}

	ListNode* ptr = head;
	while (ptr != NULL) {
		fprintf(file, "%d   ", ptr->data);
		ptr = ptr->link;
	}

	fclose(file);
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

void ConcatTwo(ListNode** head1, ListNode** head2, ListNode** head3) {

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
