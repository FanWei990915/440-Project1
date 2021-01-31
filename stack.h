#ifndef STACK_H
#define STACK_H
#include "global.h"

typedef struct Stack{
	Node *head;
	int size;
}Stack;

Stack* pushstack(Stack* stack, int x1, int y1){
	Node *temp = (Node*)malloc(sizeof(Node));
	temp->x = x1;
	temp->y = y1;
	temp->next = NULL;
	if(stack == NULL){
		stack = (Stack*)malloc(sizeof(Stack));
		stack->size = 1;
		stack->head = temp;
		return stack;		
	}else{
		temp->next = stack->head;
		stack->size += 1;
		stack->head = temp;
		return stack;	
	}
}

Stack* popstack(Stack* stack){
	if(stack == NULL || stack->size == 1) return NULL;
	stack->size -= 1;
	stack->head = stack->head->next;
	return stack;
}



#endif