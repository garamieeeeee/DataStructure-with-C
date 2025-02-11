//이진트리의 순회-preorder, inorder, postorder
//반복적인 방식 사용
//명시적인 스택 구현하여 사용함

#include <stdio.h>
#include <stdlib.h>

#define STACK_SIZE 100

typedef char ElementType;

typedef struct BinTreeNode {
	ElementType data;
	struct BinTreeNode* leftChild;
	struct BinTreeNode* rightChild;
}BinTreeNode;

typedef struct {
	int top;
	BinTreeNode* stack[STACK_SIZE];
}StackType;

StackType* CreateStack();
int IsEmptyStack(StackType* s);
int IsFullStack(StackType* s);
void Push(StackType* s, BinTreeNode* p);
BinTreeNode* Pop(StackType* s);
void FreeStack(StackType** s);
void InOrder_iterative(BinTreeNode* root);
void PreOrder_iterative(BinTreeNode* root);
void PostOrder_iterative(BinTreeNode* root);

BinTreeNode n1 = { 'D', NULL, NULL };
BinTreeNode n2 = { 'E', NULL, NULL };
BinTreeNode n3 = { 'B', &n1, &n2 };
BinTreeNode n4 = { 'F', NULL, NULL };
BinTreeNode n5 = { 'G', NULL, NULL };
BinTreeNode n6 = { 'C', &n4, &n5 };
BinTreeNode n7 = { 'A', &n3, &n6 };
BinTreeNode* root = &n7;

//		  A
//	   /    \
// 	  B       C
//  /   \    /  \
// D     E  F    G 

int main() {
	printf("전위순회(반복적): "); PreOrder_iterative(root); printf("\n");//A B D E C F G
	printf("중위순회(반복적): "); InOrder_iterative(root); printf("\n");//D B E A F C G
	printf("후위순회(반복적): "); PostOrder_iterative(root); printf("\n");//D E B F G C A

	return 0;
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

void InOrder_iterative(BinTreeNode* root) {
	//노드를 담을 스택 생성
	StackType* s = CreateStack();
	BinTreeNode* ptr = root;

	while (ptr != NULL || !IsEmptyStack(s)) { //스택에 요소가 있는 동안에 반복
		//왼쪽 끝까지 이동하며 스택에 Push
		while (ptr) {
			Push(s, ptr);
			ptr = ptr->leftChild;
		}

		//스택에서 하나 Pop한 후 출력
		ptr = Pop(s);
		printf("%c ", ptr->data);

		//오른쪽 서브트리로 이동
		ptr = ptr->rightChild;
	}

	//스택 메모리 해제
	FreeStack(&s);
}

void PreOrder_iterative(BinTreeNode* root) {
	//예외 처리(트리가 비어있는 경우)
	if (root == NULL) return;

	//노드를 담을 스택 생성
	StackType* s = CreateStack();

	//루트노드를 스택에 삽입합다.
	Push(s, root);

	while (!IsEmptyStack(s)) { //스택에 요소가 있는 동안에 반복
		//스택에서 하나 꺼내서 출력
		BinTreeNode* temp = Pop(s);
		printf("%c ", temp->data);

		//왼쪽 자식이 먼저 나와야 하니까, 오른쪽 자식을 먼저 삽입한다
		//노드의 오른쪽 자식이 있으면 스택에 삽입한다.
		if (temp->rightChild) Push(s, temp->rightChild);
		//노드의 왼쪽 자식이 있으면 스택에 삽입한다.
		if (temp->leftChild) Push(s, temp->leftChild);
	}

	//스택 메모리 해제
	FreeStack(&s);
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
		printf("%c ", temp->data);
	}

	//스택 메모리 해제
	FreeStack(&stack);
	FreeStack(&resultStack);
}
