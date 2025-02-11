#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>

#define MAX_NODE_COUNT 20 //노드 개수: 20개 이하

typedef int ElementType;

typedef struct BinTreeNode { //BinTree: binary tree
	ElementType data;
	struct BinTreeNode* leftChild;
	struct BinTreeNode* rightChild;
}BinTreeNode;

typedef struct {
	BinTreeNode nodes[MAX_NODE_COUNT + 1]; //실제 노드는 1~20번에 들어감
}BinTree;

void Error(char* message) { //에러 메시지 출력 후 종료
	fprintf(stderr, "%s\n", message);
	exit(EXIT_FAILURE);
}

BinTreeNode CreateNode(ElementType data) {
	BinTreeNode node;
	node.data = data;
	node.leftChild = NULL;
	node.rightChild = NULL;

	return node;
}

BinTree Create_BinTree() { //비어있는 (배열) 트리를 생성하여 반환
	BinTree tree;
	for (int i = 0; i < MAX_NODE_COUNT + 1; i++) { //초기화
		tree.nodes[i].data = -1; //-1로 초기화(-1: empty node)
		tree.nodes[i].leftChild = tree.nodes[i].rightChild = NULL;
	}

	return tree;
}

int ReadFile(char* fileName, BinTree* tree) {
	FILE* file = fopen(fileName, "r");
	if (!file) Error("file open failed.");

	int validNodeCount; //유효한 노드의 수(null이 아닌)
	fscanf(file, " %d", &validNodeCount);
	if (validNodeCount > MAX_NODE_COUNT) Error("The maximum number of nodes is 20.");

	//배열에 데이터 값 넣기
	int i = 1;
	int count = 0;
	ElementType data;
	while (fscanf(file, " %d", &data) != EOF) {
		if (data != -1) tree->nodes[i] = CreateNode(data);
		i++;
		count++;
	}

	fclose(file);

	//링크 연결(부모노드 - 자식 노드)
	for (int i = 1; i <= count; i++) {
		if (tree->nodes[i].data != -1) {
			if ((2 * i <= count) && (tree->nodes[2 * i].data != -1)) tree->nodes[i].leftChild = &(tree->nodes[2 * i]);
			if ((2 * i + 1 <= count) && (tree->nodes[2 * i + 1].data != -1)) tree->nodes[i].rightChild = &(tree->nodes[2 * i + 1]);
		}
	}

	return count;
}

void PreOrder(BinTreeNode* root) {
	if (root != NULL) {
		if (root->data != -1) printf("%d ", root->data);
		PreOrder(root->leftChild);
		PreOrder(root->rightChild);
	}
}

void InOrder(BinTreeNode* root) {
	if (root != NULL) {
		InOrder(root->leftChild);
		if (root->data != -1) printf("%d ", root->data);
		InOrder(root->rightChild);
	}
}

void PostOrder(BinTreeNode* root) {
	if (root != NULL) {
		PostOrder(root->leftChild);
		PostOrder(root->rightChild);
		if (root->data != -1) printf("%d ", root->data);
	}
}

int main(int argc, char* argv[]) {
	BinTree tree = Create_BinTree();
	int n = ReadFile(argv[1], &tree); //n:마지막 노드의 노드 번호

	//배열에 노드가 제대로 들어갔는지 확인
	/*for (int i = 1; i <= MAX_NODE_COUNT; i++) {
		printf("[%d] %d ", i, tree.nodes[i].data);
	}
	printf("\n");*/

	//링크가 잘 연결되었는지 확인
	/*for (int i = 1; i <= n; i++) {
		if (tree.nodes[i].data != -1) {
			printf("[%d] %d, ", i, tree.nodes[i].data);
			if (tree.nodes[i].leftChild != NULL)
				printf("L: %d, ", tree.nodes[i].leftChild->data);
			if (tree.nodes[i].rightChild != NULL)
				printf("R: %d, ", tree.nodes[i].rightChild->data);
		}
	}
	printf("\n");*/

	printf("inorder traversal: "); InOrder(&tree.nodes[1]); printf("\n");
	printf("preorder traversal: "); PreOrder(&tree.nodes[1]); printf("\n");
	printf("postorder traversal: "); PostOrder(&tree.nodes[1]); printf("\n");

	return 0;
}
