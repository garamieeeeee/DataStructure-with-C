#include "BinarySearchTree_ver1.h"

void test() {
	BST* tree = CreateBST();
	printf("<< 삽입 >>\n");

	//8, 9, 3, 1, 6, 4, 7, 5 순으로 삽입
	InsertNode(&(tree->rootNode), 8); //8 삽입
	BSTNode* rootNode = tree->rootNode; //루트노드: 8
	InsertNode(&rootNode, 9);
	InsertNode(&rootNode, 3);
	InsertNode(&rootNode, 1);
	InsertNode(&rootNode, 6);
	InsertNode(&rootNode, 4);
	InsertNode(&rootNode, 7);
	InsertNode(&rootNode, 5);
	printf("\n");

	printf("전위순회: "); PreOrder(rootNode); printf("\n");
	printf("중위순회: "); InOrder(rootNode); printf("\n");
	printf("후위순회: "); PostOrder(rootNode); printf("\n");
	printf("\n");

	InsertNode(&rootNode, 6); printf("\n");

	BSTNode* node;
	printf("<< 탐색 >>\n");
	node = SearchNode(rootNode, 4);
	if (node) printf("키 [%d]는 트리에 있습니다.\n", node->key);

	node = SearchNode(rootNode, 12);
	if (node) printf("키 [%d]는 트리에 있습니다.\n", node->key);
	printf("\n");

	printf("<< 삭제 >>\n");
	DeleteNode(&rootNode, 30);
	DeleteNode(&rootNode, 3);
	printf("\n");

	printf("전위순회: "); PreOrder(rootNode); printf("\n");
	printf("중위순회: "); InOrder(rootNode); printf("\n");
	printf("후위순회: "); PostOrder(rootNode); printf("\n");

	//트리의 모든 노드 삭제 후 트리의 메모리도 해제
	FreeBST(tree->rootNode);
	free(tree);
	tree = NULL;
}

int main() {
	test();
	return 0;
}
