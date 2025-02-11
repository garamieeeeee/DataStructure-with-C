#ifndef THREADEDBINARYTREE_H
#define THREADEDBINARYTREE_H

#include <stdio.h>
#include <stdlib.h>

#define FALSE 0
#define TRUE 1

typedef char ElementType;

typedef struct thrBTNode {
	ElementType data;
	struct thrBTNode* leftChild;
	struct thrBTNode* rightChild;
	short int leftThread;
	short int rightThread;
}thrBTNode;

typedef struct {
	thrBTNode* headNode;
}thrBT;

void Error(char* message);
thrBTNode* CreateNode(ElementType data);
thrBT* Create_thrBT();
thrBTNode* Find_InOrder_Predecessor(thrBTNode* node);
thrBTNode* Find_InOrder_Successor(thrBTNode* node);
void Insert_LeftChild(thrBTNode* node, ElementType data);
void Insert_RightChild(thrBTNode* node, ElementType data);
thrBTNode* Get_LeftChild(thrBTNode* node);
thrBTNode* Get_rightChild(thrBTNode* node);
void thrBT_InOrder_Traversal(thrBT* tree);

#endif
