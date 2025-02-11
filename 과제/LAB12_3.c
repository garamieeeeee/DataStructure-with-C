#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE 20
#define STACK_SIZE 100

typedef char ElementType;

typedef struct BinTreeNode {
	ElementType data;
	struct BinTreeNode* leftChild;
	struct BinTreeNode* rightChild;
}BinTreeNode;

typedef struct BinTree {
	BinTreeNode* rootNode;
}BinTree;

typedef struct {
	int top;
	BinTreeNode* stack[STACK_SIZE];
}StackType;

void Error(char* message) { //에러 메시지 출력 후 종료
	fprintf(stderr, "%s\n", message);
	exit(EXIT_FAILURE);
}

BinTreeNode* CreateNode(ElementType data) {
	BinTreeNode* newNode = (BinTreeNode*)malloc(sizeof(BinTreeNode));
	if (!newNode) Error("memory allocation failed.");
	newNode->data = data;
	newNode->leftChild = newNode->rightChild = NULL;

	return newNode;
}

BinTree* Create_BinTree() {
	BinTree* tree = (BinTree*)malloc(sizeof(BinTree));
	if (!tree) Error("memory allocation failed.");
	tree->rootNode = NULL;

	return tree;
}

int ReadFile(const char* fileName, ElementType array[]) { //input 파일을 읽어 배열에 저장
	FILE* file = fopen(fileName, "r");
	if (!file) Error("file open failed.");

	int validNodeCount; //유효한 노드 개수 ('N'이 아닌)
	fscanf(file, "%d", &validNodeCount);

	ElementType data;
	int count = 0;
	int i = 1;
	while (fscanf(file, " %c", &data) != EOF) { //파일의 끝까지 읽는다
		if (data != 'N') array[i] = data;
		i++;
		count++;
	}

	if (validNodeCount > count) Error("valid node count is incorrect.");

	fclose(file);

	return count;
}

BinTreeNode* BuildTree(ElementType array[], int index, int n) {
	// array[] 배열 기반으로 트리 구성
	// index: 루트 노드의 번호
	if (index > n || array[index] == 0) return NULL;

	// 왼쪽 자식 생성
	BinTreeNode* leftChild = BuildTree(array, 2 * index, n);
	// 오른쪽 자식 생성
	BinTreeNode* rightChild = BuildTree(array, 2 * index + 1, n);
	// 부모 노드 생성
	BinTreeNode* node = CreateNode(array[index]);
	node->leftChild = leftChild;
	node->rightChild = rightChild;

	return node;
}

void DeleteNode(BinTreeNode* node) {
	if (node == NULL) return;

	DeleteNode(node->leftChild);
	DeleteNode(node->rightChild);
	free(node);
}

void Delete_BinTree(BinTree** tree) {
	if (*tree == NULL) return;

	DeleteNode((*tree)->rootNode);
	free(*tree);
	*tree = NULL;
}

StackType* CreateStack() { //스택 구조체 생성(&초기화)하여 포인터 전달
	StackType* s = (StackType*)malloc(sizeof(StackType));
	if (!s) {
		fprintf(stderr, "memory allocation failed.\n");
		exit(EXIT_FAILURE);
	}
	s->top = -1;
	return s;
}

int IsEmptyStack(StackType* s) {
	return (s->top == -1);
}

int IsFullStack(StackType* s) {
	return (s->top == STACK_SIZE - 1);
}

void Push(StackType* s, BinTreeNode* p) {
	if (IsFullStack(s)) {
		fprintf(stderr, "Stack is Full.\n");
		exit(EXIT_FAILURE);
	}

	s->stack[++(s->top)] = p;
}

BinTreeNode* Pop(StackType* s) {
	if (IsEmptyStack(s)) {
		fprintf(stderr, "Stack is Empty.\n");
		exit(EXIT_FAILURE);
	}

	return (s->stack[(s->top)--]);
}

void FreeStack(StackType** s) { //스택 구조체의 메모리 해제
	free(*s);
	*s = NULL;
}

void PostOrder_iterative(BinTreeNode* root) {
	//예외 처리(트리가 비어있는 경우)
	if (root == NULL) return;

	//노드를 담을 스택 생성
	StackType* stack = CreateStack();
	StackType* resultStack = CreateStack();

	//루트노드부터 시작(루트노드가 마지막에 나오도록, 스택에 가장 먼저 삽입)
	Push(stack, root);

	while (!IsEmptyStack(stack)) {
		//stack에서 pop해서 resultStack에 삽입한다.
		BinTreeNode* temp = Pop(stack);
		Push(resultStack, temp);

		//왼쪽 자식을 먼저 Push
		if (temp->leftChild) Push(stack, temp->leftChild);
		//오른쪽 자식을 Push
		if (temp->rightChild) Push(stack, temp->rightChild);
	}

	//후위순회 출력
	while (!IsEmptyStack(resultStack)) {
		BinTreeNode* temp = Pop(resultStack);
		if (temp->data != 0) printf("%c ", temp->data);
	}

	//스택 메모리 해제
	FreeStack(&stack);
	FreeStack(&resultStack);
}

int main(int argc, char* argv[]) {

	//input파일을 읽어 저장할 1차원 배열 생성. 0(null)으로 초기화. 1~19번에 데이터가 들어감
	ElementType array[ARRAY_SIZE];
	for (int i = 0; i < ARRAY_SIZE; i++) {
		array[i] = 0;
	}

	//input파일 읽어 배열에 저장
	int count = ReadFile(argv[1], array);

	//배열에 노드가 제대로 들어갔는지 확인
	/*for (int i = 1; i < ARRAY_SIZE; i++) {
		printf("[%d]%c ", i, array[i]);
	}
	printf("\n");*/

	BinTree* tree = Create_BinTree();
	tree->rootNode = BuildTree(array, 1, count);

	printf("iterative implementation of postorder traversal :");
	PostOrder_iterative(tree->rootNode); printf("\n");

	//트리 삭제
	Delete_BinTree(&tree);

	return 0;
}
