#ifndef BINARYSEARCHTREE_VER2_H
#define BINARYSEARCHTREE_VER2_H

#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;

typedef struct BSTNode {
	ElementType key;
	struct BSTNode* leftChild;
	struct BSTNode* rightChild;
}BSTNode;

typedef struct {
	BSTNode* rootNode;
}BST;

void Error(char* message);
BSTNode* CreateNode(ElementType key);
BST* CreateBST();
BSTNode* SearchNode(BSTNode* root, ElementType key);
BSTNode* InsertNode(BSTNode* root, ElementType key);
BSTNode* DeleteNode(BSTNode* root, ElementType key);
void PreOrder(BSTNode* root);
void InOrder(BSTNode* root);
void PostOrder(BSTNode* root);
void FreeBST(BSTNode* root);

#endif
