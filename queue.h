#ifndef HEADER_FILE1
#define HEADER_FILE1
#include<stdio.h>
#include <stdlib.h>
typedef struct Node{
	int x;
	int y;
	struct Node *next;
}Node;

typedef struct Queue{
	Node *front;
	Node *back;
	int size;
}Queue;

Queue* push(Queue *queue, int x1, int y1){
	Node *temp = (Node*)malloc(sizeof(Node));
	temp->x = x1;
	temp->y = y1;
	temp->next = NULL;
	if(queue == NULL){
		queue = (Queue*)malloc(sizeof(Queue));
		queue->front = temp;
		queue->back = temp;
		queue->size = 1;
		return queue;
	}else{
		queue->back->next = temp;
		queue->back = temp;	
		queue->size += 1;
		return queue;
	}


}

Queue* pop(Queue *queue){
	if(queue == NULL)return NULL;
	if(queue->size == 1) return NULL;
	else{
		queue->size -= 1;
		Node *temp = queue->front->next;
	//	free(queue->front);
		queue->front = temp;
		return queue;
	}

}

#endif