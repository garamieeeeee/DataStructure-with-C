//이진트리 기본연산 구현(link 표현법 사용)
//+이진트리 추가연산(노드 개수/단말노드 개수/트리의 높이 구하는 연산, 트리 복사, 동일성 검사)

#include "LinkedBinaryTree.h"

void Error(char* message) {
	fprintf(stderr, "%s\n", message);
	exit(EXIT_FAILURE);
}

BinTree* Create_BinTree() { //비어있는 이진트리 생성하여 반환
	BinTree* tree = (BinTree*)malloc(sizeof(BinTree));
	if (!tree) Error("memory allocation failed.");
	tree->rootNode = NULL;

	return tree;
}

BinTreeNode* CreateNode(ElementType data) {
	BinTreeNode* newNode = (BinTreeNode*)malloc(sizeof(BinTreeNode));
	if (!newNode) Error("memory allocation failed.");

	newNode->data = data;
	newNode->leftChild = newNode->rightChild = NULL;
	return newNode;
}

void Insert_RootNode(BinTree* tree, ElementType data) {
	//이미 루트노드가 있는 경우: 삽입하지 않고 종료
	if (tree->rootNode) {
		printf("rootNode exists already.");
		return;
	}
	tree->rootNode = CreateNode(data);
}

void Insert_LeftChild(BinTreeNode* node, ElementType data) { //node의 왼쪽 자식 삽입
	//node가 존재하지 않는 경우: 삽입할 수 없다.
	if (node == NULL) Error("parent Node is NULL.");

	//node의 왼쪽 자식이 이미 있는 경우: 삽입하지 않고 종료
	if (node->leftChild) {
		printf("parent Node has leftChild already.\n");
		return;
	}
	node->leftChild = CreateNode(data);
}

void Insert_RightChild(BinTreeNode* node, ElementType data) { //node의 오른쪽 자식 삽입
	//node가 존재하지 않는 경우: 삽입할 수 없다.
	if (node == NULL) Error("parent Node if NULL.");

	//node의 오른쪽 자식이 이미 있는 경우: 삽입하지 않고 종료
	if (node->rightChild) {
		printf("parent Node has rightChild already.\n");
		return;
	}
	node->rightChild = CreateNode(data);
}

BinTreeNode* Get_RootNode(BinTree* tree) { //tree의 루트노드 반환
	return tree->rootNode; //트리가 비어있다면 NULL값 반환
}

BinTreeNode* Get_LeftChild(BinTreeNode* node) {//node의 왼쪽 자식 반환
	//node가 존재하지 않는 경우: 에러
	if (node == NULL) Error("parent Node is NULL.");

	return node->leftChild; //왼쪽 자식노드가 없다면 NULL값 반환
}

BinTreeNode* Get_RightChild(BinTreeNode* node) {//node의 오른쪽 자식 반환
	//node가 존재하지 않는 경우: 에러
	if (node == NULL) Error("parent Node is NULL.");

	return node->rightChild; //오른쪽 자식노드가 없다면 NULL값 반환
}

void DeleteNode(BinTreeNode* node) { //node의 서브트리를 포함하여 모두 삭제
	//node가 존재하지 않는 경우: 바로 종료
	if (node == NULL) return;

	//후위 순회(L->R->V) 순으로 삭제(자식노드부터 삭제한 후 부모노드 삭제)
	DeleteNode(node->leftChild);
	DeleteNode(node->rightChild);
	printf("node [%c] 삭제\n", node->data);
	free(node);
}

void Delete_BinTree(BinTree** tree) { //트리의 루트노드부터 모든 노드를 삭제하고, 트리 구조체의 메모리도 해제
	//이미 트리가 비어있으면 삭제하지 않고 종료
	if (*tree == NULL) return;

	DeleteNode(Get_RootNode(*tree)); //모든 노드 삭제
	free(*tree); //트리의 메모리 해제
	*tree = NULL;
}

int Get_NodeCount(BinTreeNode* node) {
	int count = 0;
	if (node) {
		count = 1 + Get_NodeCount(node->leftChild) + Get_NodeCount(node->rightChild);
	}

	return count;
}

int Get_LeafCount(BinTreeNode* node) {
	int count = 0;
	if (node) {
		if (node->leftChild == NULL && node->rightChild == NULL) {
			return 1;
		}
		else {
			count = Get_LeafCount(node->leftChild) + Get_LeafCount(node->rightChild);
		}
	}

	return count;
}

int Get_Height(BinTreeNode* node) {
	int height = 0;
	if (node) {
		height = 1 + max(Get_Height(node->leftChild), Get_Height(node->rightChild));
	}
	return height;
}

BinTreeNode* Copy_BinTree(BinTreeNode* origin_root) { //주어진 트리를 복사하고 트리의 루트노드를 가리키는 포인터를 리턴함. 후위순회를 이용(L->R->V순으로 복사)
	//트리가 비어있는지 검사: 원본 트리가 비어있다면 NULL 반환 후 종료
	//또는 단말노드를 거쳐 NULL에 도달한 경우: NULL값 반환(종료조건2)
	if (origin_root == NULL) return NULL;

	BinTreeNode* copied_root = CreateNode(origin_root->data);
	copied_root->leftChild = Copy_BinTree(origin_root->leftChild);
	copied_root->rightChild = Copy_BinTree(origin_root->rightChild);

	return copied_root; //종료조건2
}

int IsEqual(BinTreeNode* t1_root, BinTreeNode* t2_root) { //두 개의 트리가 동일하면 TRUE, 그렇지 않으면 FALSE 반환
	//두개의 트리 중에 하나라도 비어있으면
	//또는 단말노드를 거쳐, NULL까지 도달했을 경우
	if (t1_root == NULL || t2_root == NULL)
		return t1_root == t2_root; //둘다 비어있다면 TRUE를 반환, 둘 중 하나만 비어있다면 FALSE 반환(종료조건1)

	//두개의 트리 모두 비어있지 않다면 동일성 검사
	//전위순회 이용: V->L->R순으로 검사(코드의 왼쪽부터 읽으며 세가지 조건검사). 루트노드가 같고 왼쪽 가지와 오른쪽 가지가 같다면 두 트리의 구조가 동일하다는 것
	//차례로 검사하는 세가지 기준이 모두 &&로 묶여있음. 즉 비교하다가 하나라도 다르게 되면 FALSE를 반환하게 되고 함수의 전체 결과도 FALSE, 즉 두 트리가 동일하지 않다는 결과가 나옴
	return (t1_root->data == t2_root->data && IsEqual(t1_root->leftChild, t2_root->leftChild) && IsEqual(t1_root->rightChild, t2_root->rightChild)); //종료조건 2
}

void PreOrder(BinTreeNode* root) {
	if (root) {
		printf("%c ", root->data);
		PreOrder(root->leftChild);
		PreOrder(root->rightChild);
	}
}

void InOrder(BinTreeNode* root) {
	if (root) {
		InOrder(root->leftChild);
		printf("%c ", root->data);
		InOrder(root->rightChild);
	}
}

void PostOrder(BinTreeNode* root) {
	if (root) {
		PostOrder(root->leftChild);
		PostOrder(root->rightChild);
		printf("%c ", root->data);
	}
}
