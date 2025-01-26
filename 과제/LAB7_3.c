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
void WriteFile(const char* fileName, ListNode* head);
void Error(char* message);
int IsEmpty(ListNode* head);
ListNode* CreateNode(ElementType data);
void InsertLast(ListNode** head, ElementType data);
void Reverse(ListNode** head);
void PrintList(ListNode* head);

int main(int argc, char* argv[]) {

	//인자 검사
	if (argc < 3) { //argv[0]:파일 경로, argv[1]: input.txt, argv[2]: output.txt
		fprintf(stderr, "[Usage] %s <input.txt> <output.txt> \n", argv[0]);
		exit(EXIT_FAILURE);
	}

	//리스트 생성
	ListNode* head = NULL;
	ReadFile(argv[1], &head);
	printf("초기 리스트: ");
	PrintList(head);

	//리스트 역순으로 만들기
	printf("역순 리스트: ");
	Reverse(&head);
	PrintList(head);

	//outputt.txt에 최종 리스트 출력
	WriteFile(argv[2], head);

	return 0;
}

void ReadFile(const char* fileName, ListNode** head) {//파일을 읽고 리스트 생성
	FILE* file = fopen(fileName, "r");
	if (!file) {
		Error("file open failed\n");
	}

	int c;
	while (fscanf(file, "%d", &c)!=EOF) {
		InsertLast(head, c);
	}

	fclose(file);

	return;
}

void WriteFile(const char* fileName, ListNode* head) { //리스트를 output파일에 출력

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

void Reverse(ListNode** head) {

	//리스트가 비었는지 확인
	if (IsEmpty(*head)) {
		printf("리스트가 비어있습니다.\n");
		return;
	}

	ListNode* prev = NULL; //prev: 순서를 바꿀 노드의 선행노드를 가리키는 포인터
	ListNode* current = *head; //current: (역순으로 바꿀)현재 노드를 가리키는 포인터
	ListNode* next = NULL; //next: 순서를 바꿀 노드의 다음 노드의 주소를 저장할 포인터

	while (current != NULL) { //current는 리스트의 맨 첫노드부터 마지막 노드까지 차례로 순회함
		next = current->link; //다음에 넘어갈 노드의 주소를 미리 저장해둠
		current->link = prev; //현재 노드의 링크를 이전 노드로 연결(역순으로 바꾼다)
		prev = current; //prev는 current를 따라간다.
		current = next; //current는 다음노드로 이동
	}

	//리스트의 모든 노드가 역순으로 바뀜
	//마지막으로 head 포인터만 바꿔주면 됨
	//이제 head 포인터는 역순으로 바뀐 리스트의 맨 첫 노드(=기존 리스트의 마지막 노드)를 가리켜야 함

	//while문이 끝나고나면, current는 마지막 노드를 지나 NULL을 가리키고
	//prev는 current의 하나 앞, 즉 리스트의 맨 마지막 노드를 가리키는 상태

	*head = prev;

	return;
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
