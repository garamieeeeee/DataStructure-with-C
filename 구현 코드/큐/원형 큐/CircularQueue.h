#ifndef CIRCULARQUEUE_H
#define CIRCULARQUEUE_H

#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 5

typedef int element;

typedef struct {
	int front;
	int rear;
	element data[MAX_QUEUE_SIZE];
}QueueType;

void Error(char* message);
void InitQueue(QueueType* q);
int IsFull(QueueType* q);
int IsEmpty(QueueType* q);
void PrintQueue(QueueType* q);
void Enqueue(QueueType* q, element data);
element Dequeue(QueueType* q);
element Peek(QueueType* q);

#endif
