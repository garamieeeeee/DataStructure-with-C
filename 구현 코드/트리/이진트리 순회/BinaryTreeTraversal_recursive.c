//이진트리의 순회-preorder, inorder, postorder
//재귀적인 방식 사용
#include <stdio.h>
#include <stdlib.h>

typedef char ElementType;

typedef struct BinTreeNode {
	ElementType data;
	struct BinTreeNode* leftChild;
	struct BinTreeNode* rightChild;
}BinTreeNode;

void PreOrder(BinTreeNode* root);
void InOrder(BinTreeNode* root);
void PostOrder(BinTreeNode* root);

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
	printf("전위 순회(순환적): "); PreOrder(root); printf("\n"); //A B D E C F G
	printf("중위 순회(순환적): "); InOrder(root); printf("\n"); // D B E A F C G
	printf("후위 순회(순환적): "); PostOrder(root); printf("\n"); // D E B F G C A

	return 0;
}

void PreOrder(BinTreeNode* root) {
	if (root != NULL) {
		printf("%c ", root->data);
		PreOrder(root->leftChild);
		PreOrder(root->rightChild);
	}
}

void InOrder(BinTreeNode* root) {
	if (root != NULL) {
		InOrder(root->leftChild);
		printf("%c ", root->data);
		InOrder(root->rightChild);
	}
}

void PostOrder(BinTreeNode* root) {
	if (root != NULL) {
		PostOrder(root->leftChild);
		PostOrder(root->rightChild);
		printf("%c ", root->data);
	}
}
