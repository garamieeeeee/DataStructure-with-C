#include "BinarySearchTree_ver2.h"

void test() {
	BST* tree = CreateBST();
	printf("<< 삽입 >>\n");

	//8, 9, 3, 1, 6, 4, 7, 5 순으로 삽입
	BSTNode* rootNode = InsertNode(tree->rootNode, 8); //8 삽입. 루트노드: 8
	ElementType key;
	key = 9; tree->rootNode = InsertNode(rootNode, key); printf("키 [%d] 삽입\n", key);
	key = 3; tree->rootNode = InsertNode(rootNode, key); printf("키 [%d] 삽입\n", key);
	key = 1; tree->rootNode = InsertNode(rootNode, key); printf("키 [%d] 삽입\n", key);
	key = 6; tree->rootNode = InsertNode(rootNode, key); printf("키 [%d] 삽입\n", key);
	key = 4; tree->rootNode = InsertNode(rootNode, key); printf("키 [%d] 삽입\n", key);
	key = 7; tree->rootNode = InsertNode(rootNode, key); printf("키 [%d] 삽입\n", key);
	key = 5; tree->rootNode = InsertNode(rootNode, key); printf("키 [%d] 삽입\n", key);
	printf("\n");

	printf("전위순회: "); PreOrder(rootNode); printf("\n");
	printf("중위순회: "); InOrder(rootNode); printf("\n");
	printf("후위순회: "); PostOrder(rootNode); printf("\n");
	printf("\n");

	key = 6;
	tree->rootNode = InsertNode(rootNode, key);
	printf("키 [%d] 삽입 시도: \n", key);
	printf("전위순회: "); PreOrder(rootNode); printf("\n");
	printf("중위순회: "); InOrder(rootNode); printf("\n");
	printf("후위순회: "); PostOrder(rootNode); printf("\n");
	printf("중복된 키 [%d] 삽입 실패\n\n", key);

	key = 4;
	BSTNode* node;
	printf("<< 탐색 >>\n");
	node = SearchNode(rootNode, key);
	if (node) printf("키 [%d]는 트리에 있습니다.\n", node->key);
	else printf("키 [%d]가 트리에 없습니다.\n", key);

	key = 12;
	node = SearchNode(rootNode, key);
	if (node) printf("키 [%d]는 트리에 있습니다.\n", node->key);
	else printf("키 [%d]가 트리에 없습니다.\n", key);
	printf("\n");

	key = 30;
	printf("<< 삭제 >>\n");
	printf("키 [%d] 삭제 시도: \n", key);
	tree->rootNode = DeleteNode(rootNode, key);
	printf("전위순회: "); PreOrder(rootNode); printf("\n");
	printf("중위순회: "); InOrder(rootNode); printf("\n");
	printf("후위순회: "); PostOrder(rootNode); printf("\n");
	printf("키 [%d]가 트리에 없어 삭제할 수 없습니다.\n\n", key);

	key = 3;
	printf("키 [%d] 삭제 시도: \n", key);
	tree->rootNode = DeleteNode(rootNode, key);
	printf("전위순회: "); PreOrder(rootNode); printf("\n");
	printf("중위순회: "); InOrder(rootNode); printf("\n");
	printf("후위순회: "); PostOrder(rootNode); printf("\n");
	printf("키 [%d] 삭제 성공.\n\n", key);

	//트리의 모든 노드 삭제 후 트리의 메모리도 해제
	FreeBST(rootNode);
	free(tree);
	tree = NULL;
}

int main() {
	test();
	return 0;
}
