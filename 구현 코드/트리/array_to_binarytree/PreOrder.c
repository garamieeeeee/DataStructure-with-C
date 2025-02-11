//complete binary tree의 일차원 배열 표현방식으로 표현된 이진트리를, explicit with link 방식으로 동적할당을 사용하여 구현하는 문제
//PreOrder tree traversal의 recursive version을 이용하여 구성
//즉 V->L->R 순으로 노드를 생성하여 재귀적으로 트리를 구성함
//레벨 순회를 위해 BinaryTreeTraversal_level.h 헤더파일을 추가함

#include "BinaryTreeTraversal_level.h"

typedef struct {
	BinTreeNode* rootNode;
}BinTree;

ElementType array[] = { 0, '+', '*', 'E', '*', 'D',0,0,'/', 'C', 0, 0, 0, 0, 0, 0, 'A', 'B' };

void Error(char* message);
BinTreeNode* CreateNode(ElementType data);
BinTree* Create_BinTree();
void DeleteNode(BinTreeNode* node);
void Delete_BinTree(BinTree** tree);
void PreOrder(BinTreeNode* root);
void InOrder(BinTreeNode* root);
void PostOrder(BinTreeNode* root);
BinTreeNode* BuildTree(int index);

int main() {

	//array에 저장한 노드 정보를 읽고 트리 생성
	BinTree* tree = Create_BinTree();
	tree->rootNode = BuildTree(1);

	//순회
	printf("inorder traversal: "); InOrder(tree->rootNode); printf("\n");
	printf("preorder traversal: "); PreOrder(tree->rootNode); printf("\n");
	printf("postorder traversal: "); PostOrder(tree->rootNode); printf("\n");
	printf("level order traversal: "); LevelOrder(tree->rootNode); printf("\n");

	//트리삭제
	Delete_BinTree(&tree);

	return 0;
}

void Error(char* message) {
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

void DeleteNode(BinTreeNode* node) { //node의 서브트리를 포함하여 모두 삭제
	if (node == NULL) return;
	//L->R->V순으로 메모리 해제
	DeleteNode(node->leftChild);
	DeleteNode(node->rightChild);
	free(node);
}

void Delete_BinTree(BinTree** tree) { //tree의 모든 노드 삭제 후 트리의 메모리도 해제
	if (*tree == NULL) return;
	//루트노드부터 모든 노드 삭제
	DeleteNode((*tree)->rootNode);
	free(*tree);
	*tree = NULL;
}

void PreOrder(BinTreeNode* root) {
	if (root) {
		if (root->data != 0) printf("%c ", root->data);
		PreOrder(root->leftChild);
		PreOrder(root->rightChild);
	}
}

void InOrder(BinTreeNode* root) {
	if (root) {
		InOrder(root->leftChild);
		if (root->data != 0) printf("%c ", root->data);
		InOrder(root->rightChild);
	}
}

void PostOrder(BinTreeNode* root) {
	if (root) {
		PostOrder(root->leftChild);
		PostOrder(root->rightChild);
		if (root->data != 0) printf("%c ", root->data);
	}
}

BinTreeNode* BuildTree(int index) { //index: 루트노드의 노드번호
	//array[]에 담긴 노드 정보를 사용
	// 부모노드-자식노드 간 인덱스 관계 사용
	//(V->L->R) Preorder tree traversal의 recursive version 이용

	int n = sizeof(array) / sizeof(ElementType);//n:배열 array의 크기
	int last = n - 1; //last: 마지막 노드의 노드번호

	//종료조건 1
	if (index > last || array[index] == 0) return NULL;

	//array[]의 index번의 데이터를 가지고 부모노드 node 생성
	BinTreeNode* node = CreateNode(array[index]);
	//array[]의 (2*index)번의 데이터를 가지고 다시 BuildTree() 순환 호출, node의 왼쪽 자식 달기
	node->leftChild = BuildTree(2 * index);
	//array[]의 (2*index+1)번의 데이터를 가지고 다시 BuildTree() 순환 호출, node의 오른쪽 자식 달기
	node->rightChild = BuildTree(2 * index + 1);

	return node; //생성한 노드를 반환 (종료 조건2)*/
}

