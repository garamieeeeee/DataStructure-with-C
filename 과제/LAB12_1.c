#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE 20

typedef char ElementType;

typedef struct BinTreeNode {
	ElementType data;
	struct BinTreeNode* leftChild;
	struct BinTreeNode* rightChild;
}BinTreeNode;

typedef struct BinTree {
	BinTreeNode* rootNode;
}BinTree;

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

void InOrder(BinTreeNode* root) {
	if (root) {
		InOrder(root->leftChild);
		if (root->data != 0) printf("%c ", root->data);
		InOrder(root->rightChild);
	}
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

	printf("recursive implementation of inorder traversal :"); InOrder(tree->rootNode); printf("\n");

	//트리 삭제
	Delete_BinTree(&tree);

	return 0;
}
