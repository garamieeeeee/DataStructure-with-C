#ifndef LINKEDBINARYTREE_H
#define LINKEDBINARYTREE_H

#include <stdio.h>
#include <stdlib.h>

typedef char ElementType;

typedef struct BinTreeNode {
	ElementType data;
	struct BinTreeNode* leftChild;
	struct BinTreeNode* rightChild;
}BinTreeNode;

typedef struct {
	BinTreeNode* rootNode;
}BinTree;

void Error(char* message);
BinTree* Create_BinTree();
BinTreeNode* CreateNode(ElementType data);
void Insert_RootNode(BinTree* tree, ElementType data);
void Insert_LeftChild(BinTreeNode* node, ElementType data);
void Insert_RightChild(BinTreeNode* node, ElementType data);
BinTreeNode* Get_RootNode(BinTree* tree);
BinTreeNode* Get_LeftChild(BinTreeNode* node);
BinTreeNode* Get_RightChild(BinTreeNode* node);
void DeleteNode(BinTreeNode* node);
void Delete_BinTree(BinTree** tree);
int Get_NodeCount(BinTreeNode* node);
int Get_LeafCount(BinTreeNode* node);
int Get_Height(BinTreeNode* node);
BinTreeNode* Copy_BinTree(BinTreeNode* origin_root);
int IsEqual(BinTreeNode* t1_root, BinTreeNode* t2_root);
void PreOrder(BinTreeNode* root);
void InOrder(BinTreeNode* root);
void PostOrder(BinTreeNode* root);

#endif
