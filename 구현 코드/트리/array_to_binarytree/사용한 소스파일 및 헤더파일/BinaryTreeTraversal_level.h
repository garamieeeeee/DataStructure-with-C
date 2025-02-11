#ifndef BINARYTREETRAVERSAL_LEVEL_H
#define BINARYTREETRAVERSAL_LEVEL_H

#include <stdio.h>
#include <stdlib.h>

//원형 큐
#define QUEUE_SIZE 100

typedef char ElementType;

typedef struct BinTreeNode {
	ElementType data;
	struct BinTreeNode* leftChild;
	struct BinTreeNode* rightChild;
}BinTreeNode;

typedef struct {
	int front, rear;
	BinTreeNode* Queue[QUEUE_SIZE];
}QueueType;

QueueType* CreateQueue();
int IsEmptyQueue(QueueType* q);
int IsFullQueue(QueueType* q);
void Enqueue(QueueType* q, BinTreeNode* p);
BinTreeNode* Dequeue(QueueType* q);
void FreeQueue(QueueType** q);
void LevelOrder(BinTreeNode* root);

#endif
