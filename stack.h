#ifndef STACK_H
#define STACK_H
#include "global.h"

typedef struct Stack{
	Node *head;
	int size;
}Stack;

Stack* push(Stack* stack, int x, int y){
	Node *temp = (Node*)malloc(sizeof(Node));
	temp->x = x1;
	temp->y = y1;
	if(stack == NULL){
		temp->next = NULL;
		stack = (Stack*)malloc(sizeof(stack));
		stack->size == 1;
		stack->head = temp;
		return stack;		
	}else{
		temp->next = stack->head;
		stack->size += 1;
		stack->head = temp;
		return stack;	
	}
}

Stack* pop(Stack* stack, int x, int y){
	if(stack == NULL || stack->size == 1) return NULL;
	stack -= 1;
	stack->head = stack->head->next;
	return stack;
}



#endif