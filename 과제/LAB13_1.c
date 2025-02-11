#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE 20

typedef int ElementType;

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
	while (fscanf(file, " %d", &data) != EOF) { //파일의 끝까지 읽는다
		if (data != -1) array[i] = data;
		i++;
		count++;
	}

	if (validNodeCount > count) Error("valid node count is incorrect.");

	fclose(file);

	return count;
}

BinTreeNode* BuildTree(ElementType array[], int index, int n) {
	//array[] 배열 기반으로 트리 구성
	//index: 루트 노드의 번호
	if (index > n || array[index] == -1) return NULL;

	BinTreeNode* node = CreateNode(array[index]);
	node->leftChild = BuildTree(array, 2 * index, n);
	node->rightChild = BuildTree(array, 2 * index + 1, n);
	return node;
}

void PreOrder(BinTreeNode* root) {
	if (root) {
		if (root->data != -1) printf("%d ", root->data);
		PreOrder(root->leftChild);
		PreOrder(root->rightChild);
	}
}

void InOrder(BinTreeNode* root) {
	if (root) {
		InOrder(root->leftChild);
		if (root->data != -1) printf("%d ", root->data);
		InOrder(root->rightChild);
	}
}

void PostOrder(BinTreeNode* root) {
	if (root) {
		PostOrder(root->leftChild);
		PostOrder(root->rightChild);
		if (root->data != -1) printf("%d ", root->data);
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

int IsEqual(BinTreeNode* t1_root, BinTreeNode* t2_root) { //동일성 검사 함수
	if (t1_root == NULL || t2_root == NULL)
		return t1_root == t2_root;

	return (t1_root->data == t2_root->data && IsEqual(t1_root->leftChild, t2_root->leftChild) && IsEqual(t1_root->rightChild, t2_root->rightChild)); //종료조건 2
}

int main(int argc, char* argv[]) {

	////인자 검사
	if (argc < 3) { //argv[0]:파일 경로, argv[1]: input1.txt, argv[2]: input2.txt
		fprintf(stderr, "[Usage] %s <input1.txt> <input2.txt>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	////t1 생성
	//input1 파일을 읽어 저장할 1차원 배열. -1로 초기화(-1: empty node)
	ElementType array_1[ARRAY_SIZE];
	for (int i = 0; i < ARRAY_SIZE; i++) {
		array_1[i] = -1;
	}
	//input1 파일 읽어 배열에 저장
	int count = ReadFile(argv[1], array_1);

	//배열에 노드가 제대로 들어갔는지 확인
	/*for (int i = 1; i < ARRAY_SIZE; i++) {
		printf("[%d]%d ", i, array_1[i]);
	}
	printf("\n");*/

	//트리 생성
	BinTree* t1 = Create_BinTree();
	t1->rootNode = BuildTree(array_1, 1, count);

	////t2 생성
	//input2 파일을 읽어 저장할 1차원 배열. -1로 초기화(-1: empty node)
	ElementType array_2[ARRAY_SIZE];
	for (int i = 0; i < ARRAY_SIZE; i++) {
		array_2[i] = -1;
	}
	//input2 파일 읽어 배열에 저장
	count = ReadFile(argv[2], array_2);

	//배열에 노드가 제대로 들어갔는지 확인
	/*for (int i = 1; i < ARRAY_SIZE; i++) {
		printf("[%d]%d ", i, array_2[i]);
	}
	printf("\n");*/

	//트리 생성
	BinTree* t2 = Create_BinTree();
	t2->rootNode = BuildTree(array_2, 1, count);

	printf("-----------------------t1-----------------------\n");
	printf("inorder traversal: "); InOrder(t1->rootNode); printf("\n");
	printf("preorder traversal: "); PreOrder(t1->rootNode); printf("\n");
	printf("postorder traversal: "); PostOrder(t1->rootNode); printf("\n");
	printf("------------------------------------------------\n\n");

	printf("-----------------------t2-----------------------\n");
	printf("inorder traversal: "); InOrder(t2->rootNode); printf("\n");
	printf("preorder traversal: "); PreOrder(t2->rootNode); printf("\n");
	printf("postorder traversal: "); PostOrder(t2->rootNode); printf("\n");
	printf("------------------------------------------------\n\n");

	printf("t1과 t2의 동일성 검사 결과: ");
	if (IsEqual(t1->rootNode, t2->rootNode))
		printf("TRUE\n");
	else
		printf("FALSE\n");

	//트리 삭제
	Delete_BinTree(&t1);
	Delete_BinTree(&t2);

	return 0;
}
