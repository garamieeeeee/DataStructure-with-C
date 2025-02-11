#include "ThreadedBinaryTree.h"

void test() {
	//트리 생성
	thrBT* tree = Create_thrBT();

	//노드 삽입(n1~n9)
	Insert_LeftChild(tree->headNode, 'A');
	thrBTNode* n1 = Get_LeftChild(tree->headNode);

	Insert_LeftChild(n1, 'B');
	thrBTNode* n2 = Get_LeftChild(n1);

	Insert_RightChild(n1, 'C');
	thrBTNode* n3 = Get_rightChild(n1);

	Insert_LeftChild(n2, 'D');
	thrBTNode* n4 = Get_LeftChild(n2);

	Insert_RightChild(n2, 'E');
	thrBTNode* n5 = Get_rightChild(n2);

	Insert_LeftChild(n3, 'F');
	thrBTNode* n6 = Get_LeftChild(n3);

	Insert_RightChild(n3, 'G');
	thrBTNode* n7 = Get_rightChild(n3);

	Insert_LeftChild(n4, 'H');
	thrBTNode* n8 = Get_LeftChild(n4);

	Insert_RightChild(n4, 'I');
	thrBTNode* n9 = Get_rightChild(n4);

	//        A
	//      /   \
	//     B     C
	//    / \   / \
	//   D   E F   G
	//  / \
	// H   I

	//중위순회(출력)
	printf("중위 순회: "); thrBT_InOrder_Traversal(tree);

	//트리의 모든 노드 삭제 후 트리 구조체도 메모리 해제
	free(n8); free(n9); free(n4); free(n5); free(n2); free(n6); free(n7); free(n3); free(n1);
	free(tree->headNode);
	free(tree);
}

int main() {
	test();
	return 0;
}
