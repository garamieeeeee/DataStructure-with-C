#ifndef BINARYSEARCHTREE_VER1_H
#define BINARYSEARCHTREE_VER1_H

#include <stdio.h>
#include <stdlib.h>

#define FALSE 0
#define TRUE 1

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
int InsertNode(BSTNode** root, ElementType key);
int DeleteNode(BSTNode** root, ElementType key);
void PreOrder(BSTNode* root);
void InOrder(BSTNode* root);
void PostOrder(BSTNode* root);
void FreeBST(BSTNode* root);

#endif
