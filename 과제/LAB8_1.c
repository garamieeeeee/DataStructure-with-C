//헤드노드를 갖는 원형연결리스트
//다항식을 연결리스트로 표현

#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;

typedef struct ListNode { //노드: 항
	int coef; //계수
	int expon; //지수
	struct ListNode* link;
}ListNode;

typedef struct ListType { //리스트 타입(하나의 리스트는 하나의 헤더노드에 의하여 표현됨)
	int size;
	ListNode* head;
	ListNode* tail;
}ListType; //연결리스트 헤더

void ReadFile(const char* fileName, ListType* plist1, ListType* plist2);
void WriteFile(const char* fileName, ListType* plist);
void Error(char* message);
ListType* CreateList();
ListNode* CreateNode(int coef, int expon);
void InsertLast(ListType* plist, int coef, int expon);
void AddPoly(ListType* plist1, ListType* plist2, ListType* plist3);
void PrintPoly(ListType* plist);
void Erase(ListType** plist);

int main(int argc, char* argv[]) {
	// 인자 검사
	if (argc < 3) { //argv[0]:파일 경로, argv[1]: input.txt, argv[2]: output.txt
		fprintf(stderr, "[Usage] %s <input.txt> <output.txt> \n", argv[0]);
		exit(EXIT_FAILURE);
	}

	//세개의 다항식 리스트 생성& 초기화
	ListType* plist1 = CreateList();
	ListType* plist2 = CreateList();
	ListType* plist3 = CreateList();

	//input파일을 읽어 리스트1, 리스트2 구성
	ReadFile(argv[1], plist1, plist2);

	//리스트1과 리스트2를 덧셈한 결과를 list3에 출력
	AddPoly(plist1, plist2, plist3);

	printf("다항식1: "); PrintPoly(plist1);
	printf("다항식2: "); PrintPoly(plist2);
	printf("다항식1 + 다항식2 = "); PrintPoly(plist3);

	//결과 다항식을 output파일에 쓰기
	WriteFile(argv[2], plist3);

	//다항식 리스트1 삭제
	Erase(&plist1);
	//다항식 리스트1 삭제
	Erase(&plist2);
	//다항식 리스트1 삭제
	Erase(&plist3);

	return 0;
}

void ReadFile(const char* fileName, ListType* plist1, ListType* plist2) {//input 파일을 읽어 두개의 다항식 연결리스트 생성
	FILE* file = fopen(fileName, "r");
	if (file == NULL) {
		Error("file open failed.");
	}

	int n, m; //n: 리스트1의 항 개수, m: 리스트2의 항 개수
	fscanf(file, "%d %d", &n, &m);

	for (int i = 0; i < n; i++) { //리스트1 생성
		int coef, expon;
		fscanf(file, "%d %d", &coef, &expon);
		InsertLast(plist1, coef, expon);
	}
	for (int i = 0; i < m; i++) { //리스트2 생성
		int coef, expon;
		fscanf(file, "%d %d", &coef, &expon);
		InsertLast(plist2, coef, expon);
	}

	fclose(file);
}

void WriteFile(const char* fileName, ListType* plist) { //결과 다항식을 output파일에 출력
	FILE* file = fopen(fileName, "w");
	if (file == NULL) {
		Error("file open failed.");
	}

	if (plist->size == 0) {
		return;
	}

	ListNode* ptr = plist->head;
	do {
		fprintf(file, "%dx^%d ", ptr->coef, ptr->expon);
		if (ptr->link != plist->head) {
			fprintf(file, "+ ");
		}
		ptr = ptr->link;
	} while (ptr != plist->head);

	fclose(file);
}

void Error(char* message) {
	fprintf(stderr, "%s\n", message);
	exit(EXIT_FAILURE);
}

ListType* CreateList() { //리스트의 헤드노드를 동적으로 생성하고, 초기화하여 포인터를 반환
	ListType* plist = (ListType*)malloc(sizeof(ListType)); //하나의 리스트는 하나의 헤더노드에 의하여 표현됨(plist: 연결리스트로 표현된 다항식)
	if (plist == NULL) {
		Error("memory allocation failed.");
	}

	//초기화
	plist->size = 0;
	plist->head = plist->tail = NULL;

	return plist;
}

ListNode* CreateNode(int coef, int expon) {
	ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
	if (newNode == NULL) {
		Error("memory allocation failed.");
	}

	newNode->coef = coef;
	newNode->expon = expon;
	newNode->link = NULL;

	return newNode;
}

void InsertLast(ListType* plist, int coef, int expon) { //각 항(계수+지수)을 읽고 리스트에 차례로 뒤에 삽입
	ListNode* newNode = CreateNode(coef, expon);

	if (plist->head == NULL) { //리스트가 비어있으면: 첫 노드가 됨
		plist->head = plist->tail = newNode;
		newNode->link = plist->head;
	}
	else {
		plist->tail->link = newNode;
		plist->tail = newNode;
		newNode->link = plist->head;
	}
	plist->size++;
}

void AddPoly(ListType* plist1, ListType* plist2, ListType* plist3) { //두 개의 다항식 plist1과 plist를 더한 결과인 plist3을 생성

	ListNode* p1, * p2; //각 연결리스트(다항식)을 순회할 포인터
	p1 = plist1->head;
	p2 = plist2->head;
	
	int size1 = plist1->size;
	int size2 = plist2->size;

	int i = 0, j = 0;
	while (1) {
		if (i == plist1->size || j == plist2->size) {
			break;
		}
		if (p1->expon == p2->expon) {//두 계수의 합이 0이 아니면, plist3에 새로운 항으로 추가
			if ((p1->coef + p2->coef) != 0) {
				InsertLast(plist3, p1->coef + p2->coef, p1->expon);
			}
			i++;
			j++;
			p1 = p1->link;
			p2 = p2->link;
		}
		else if (p1->expon > p2->expon) {// : p1이 가리키는 항만 복사하여 list3에 추가, p1만 다음항으로 넘어감 
			InsertLast(plist3, p1->coef, p1->expon);
			i++;
			p1 = p1->link;
		}
		else {//p1->exopon < p2->expon: p2이 가리키는 항만 복사하여 list3에 추가, p2만 다음항으로 넘어감 
			InsertLast(plist3, p2->coef, p2->expon);
			j++;
			p2 = p2->link;
		}
	}

	while (p1 != plist1->head) { //plist1이 남아있는 경우
		InsertLast(plist3, p1->coef, p1->expon);
		p1 = p1->link;
	}

	while (p2 != plist2->head) { //plist2이 남아있는 경우
		InsertLast(plist3, p2->coef, p2->expon);
		p2 = p2->link;
	}

	//plist1, plist2가 둘다 남아있는 경우는 없고(무조건 둘중에 하나는 끝나야 while문이 끝남)
	//plist1, plist2가 동시에 순회가 끝난 경우에는 아무런 처리 없이 끝남
}

void PrintPoly(ListType* plist) {
	if (plist == NULL) {
		printf("다항식 리스트가 존재하지 않거나, 메모리가 해제되었습니다.\n");
		return;
	}
	if (plist->size == 0) {
		printf("다항식 리스트가 비어있습니다.\n");
		return;
	}

	ListNode* ptr = plist->head;
	do {
		printf("%dx^%d ", ptr->coef, ptr->expon);
		if (ptr->link != plist->head) {
			printf("+ ");
		}
		ptr = ptr->link;
	} while (ptr != plist->head);

	printf("\n\n");
}

void Erase(ListType** plist) {

	if ((*plist)->size == 0) {
		free(*plist);
		*plist = NULL;
		return;
	}

	ListNode* ptr = (*plist)->head;
	ListNode* temp;

	do {
		temp = ptr;
		ptr = ptr->link;
		free(temp);
	} while (ptr != (*plist)->head);

	free(*plist);
	*plist = NULL;
}
