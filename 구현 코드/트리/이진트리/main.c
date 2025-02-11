#include "LinkedBinaryTree.h"

void test() {
	//트리 생성: t1
	BinTree* t1 = Create_BinTree();
	BinTreeNode* left, * right;

	//루트노드 삽입
	Insert_RootNode(t1, 'A');

	//A의 왼쪽 자식, 오른쪽 자식 삽입
	Insert_LeftChild(Get_RootNode(t1), 'B');
	Insert_RightChild(Get_RootNode(t1), 'C');

	//B의 왼쪽 자식 삽입
	left = Get_LeftChild(Get_RootNode(t1));
	Insert_LeftChild(left, 'D');

	//D의 오른쪽 자식 삽입
	left = Get_LeftChild(left);
	Insert_RightChild(left, 'G');

	//C의 왼쪽 자식, 오른쪽 자식 삽입
	right = Get_RightChild(Get_RootNode(t1));
	Insert_LeftChild(right, 'E');
	Insert_RightChild(right, 'F');

	//	    A
	//    /   \
	//   B     C
	//  /     /  \
	// D     E    F
	//  \
	//   G

	printf("---------이진트리 t1---------\n");
	printf("전위 순회: "); PreOrder(Get_RootNode(t1)); printf("\n");
	printf("중위 순회: "); InOrder(Get_RootNode(t1)); printf("\n");
	printf("후위 순회: "); PostOrder(Get_RootNode(t1)); printf("\n");

	printf("트리의 노드 개수: %d\n", Get_NodeCount(Get_RootNode(t1)));
	printf("트리의 단말노드 개수: %d\n", Get_LeafCount(Get_RootNode(t1)));
	printf("트리의 높이: %d\n", Get_Height(Get_RootNode(t1)));
	printf("-----------------------------\n\n");

	//트리 생성: t2
	//t2는 트리 t1의 복사본
	BinTree* t2 = Create_BinTree();
	t2->rootNode = Copy_BinTree(Get_RootNode(t1));
	printf("이진트리 t1을 t2에 복사\n");
	printf("---------이진트리 t2---------\n");
	printf("전위 순회: "); PreOrder(Get_RootNode(t2)); printf("\n");
	printf("중위 순회: "); InOrder(Get_RootNode(t2)); printf("\n");
	printf("후위 순회: "); PostOrder(Get_RootNode(t2)); printf("\n");
	printf("-----------------------------\n\n");

	//t1과 t2가 동일한지 검사
	printf("이진트리 t1과 t2의 동일성 검사 결과: ");
	if (IsEqual(Get_RootNode(t1), Get_RootNode(t2)))
		printf("TRUE\n");
	else
		printf("FALSE\n");
	printf("\n");

	//t1의 노드 'B' 삭제
	printf("------t1의 노드 'B' 삭제------\n");
	DeleteNode(Get_LeftChild(Get_RootNode(t1)));
	//삭제한 노드 'B'의 부모노드인 노드'A'의 왼쪽 링크를 NULL로 변경
	Get_RootNode(t1)->leftChild = NULL;
	printf("---------이진트리 t1---------\n");
	printf("전위 순회: "); PreOrder(Get_RootNode(t1)); printf("\n");
	printf("중위 순회: "); InOrder(Get_RootNode(t1)); printf("\n");
	printf("후위 순회: "); PostOrder(Get_RootNode(t1)); printf("\n");
	printf("-----------------------------\n\n");

	//t1의 노드 'B 삭제 후, t1과 t2가 동일한지 다시 검사
	printf("이진트리 t1과 t2의 동일성 검사 결과: ");
	if (IsEqual(Get_RootNode(t1), Get_RootNode(t2)))
		printf("TRUE\n");
	else
		printf("FALSE\n");
	printf("\n");

	//트리 삭제
	printf("----------t1 삭제----------\n");
	Delete_BinTree(&t1); if (t1) printf("t1이 삭제되지 않았습니다.\n");
	printf("----------t2 삭제----------\n");
	Delete_BinTree(&t2); if (t2) printf("t2이 삭제되지 않았습니다.\n");
}

int main() {
	test();
	return 0;
}
